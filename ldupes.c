#include "aux.h"
#include "ld_duplicates_tree.h"
#include "ld_ranked_list.h"
#include "ldupes.h"

#include <assert.h>
#include <dirent.h> // opendir
#include <fcntl.h>  // openat, fstatat
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> // malloc
#include <string.h> // strcmp
#include <sys/stat.h>
#include <unistd.h> // close

bool should_skip(char const *dirname) {
    return (strcmp(dirname, ".") == 0) || (strcmp(dirname, "..") == 0);
}

char *concat_path(char const *dir_path, char const *child_name) {
    size_t dir_path_len = strlen(dir_path);
    size_t child_len    = strlen(child_name);
    char *new_path      = malloc(dir_path_len + child_len + 2);
    if (new_path == NULL) {
        return NULL;
    }

    memcpy(new_path, dir_path, dir_path_len);
    new_path[dir_path_len] = '/';
    memcpy(new_path + dir_path_len + 1, child_name, child_len);
    new_path[dir_path_len + child_len + 1] = '\0';
    return new_path;
}

struct ld_error gather_files(struct ld_context *context, struct file_list *file_list, int dir_fd, char const *dir_path) {
    if (context->cancelled && *context->cancelled) {
        return CANCEL;
    }

    DIR *dir_stream;
    if ((dir_stream = fdopendir(dir_fd)) == NULL) {
        return (struct ld_error){.type = ld_ERR_CANT_ACCESS, .message = strdup(dir_path)};
    }

    struct dirent *child;
    while ((child = readdir(dir_stream)) != NULL) {
        if (should_skip(child->d_name)) {
            continue;
        }

        struct stat child_stbuf;
        fstatat(dir_fd, child->d_name, &child_stbuf, AT_SYMLINK_NOFOLLOW);
        // TODO maybe add flag for folowing symlinks ^^^

        if (S_ISREG(child_stbuf.st_mode)) {
            if ((size_t)child_stbuf.st_size < context->min_file_size) {
                continue;
            }
            char *new_path = concat_path(dir_path, child->d_name);
            if (!new_path) {
                closedir(dir_stream);
                return OOM;
            }
            struct file_list_entry *entry = malloc(sizeof(struct file_list_entry));
            entry->file                   = (struct ld_file){.path = new_path, .has_hash = false}; // takes ownership of new_path
            entry->file_size              = (size_t)child_stbuf.st_size;
            SLIST_INSERT_HEAD(file_list, entry, entries); // takes ownership of entry
        } else if (S_ISDIR(child_stbuf.st_mode)) {
            int child_fd   = openat(dir_fd, child->d_name, O_RDONLY | O_DIRECTORY);
            char *new_path = concat_path(dir_path, child->d_name);
            if (!new_path) {
                close(child_fd);
                closedir(dir_stream);
                return OOM;
            }
            struct ld_error err = gather_files(context, file_list, child_fd, new_path);
            free(new_path);
            close(child_fd);
            if (err.type == ld_ERR_OUT_OF_MEMORY || err.type == ld_ERR_CANCELLED) {
                closedir(dir_stream);
                return err;
            }
        }
    }
    closedir(dir_stream);
    return OK;
}

bool is_small(struct rb_node *it) {
    assert(it);
    struct ld_duplicates_tree_node *container = container_of(it, struct ld_duplicates_tree_node, node);
    return LD_RANKED_LIST_SMALL(container);
}

struct ld_error process_node(struct ld_duplicates_tree_node **node, struct ld_ranked_list *dups, atomic_bool const *cancelled) {
    assert(*node);
    struct rb_node *nontrivial_node = &(*node)->node;
    while (nontrivial_node && is_small(nontrivial_node)) {
        nontrivial_node = rb_next(nontrivial_node);
    }
    if (!nontrivial_node) {
        return EOI;
    }

    *node                           = container_of(nontrivial_node, struct ld_duplicates_tree_node, node);
    struct ld_ranked_list_entry *it = SLIST_FIRST(*node);
    dups->file_size                 = (*node)->file_size;
    SLIST_REMOVE_HEAD(*node, entries);
    SLIST_INSERT_HEAD(dups, it, entries); // takes ownership
    it = SLIST_FIRST(*node);
    while (it) {
        struct ld_ranked_list_entry *next = SLIST_NEXT(it, entries);
        bool are_duplicates;
        struct ld_error err = check_if_duplicates(&it->file, &SLIST_FIRST(dups)->file, cancelled, &are_duplicates);
        if (err.type == ld_ERR_CANT_ACCESS) {
            // TODO put errors to sink
            it = next;
            continue;
        }
        if (err.type != ld_ERR_OK) {
            return err;
        }
        if (are_duplicates) {
            SLIST_REMOVE(*node, it, ld_ranked_list_entry, entries);
            SLIST_INSERT_HEAD(dups, it, entries); // takes ownership
        }
        it = next;
    }
    if (LD_RANKED_LIST_SMALL(dups)) {
        LD_RANKED_LIST_CLEAR(dups);
        return process_node(node, dups, cancelled);
    }
    return OK;
}

/**
 * @brief ld_next_duplicate
 * @param context
 * @return ld_ERR_OK if next duplicate group is successfully found;
 * ld_ERR_END_OF_ITERATION if there are no more duplicates;
 * ld_ERR_CANCELLED if file gathering was cancelled from another thread;
 * ld_ERR_NULL if context is null;
 * ld_ERR_CANT_ACCESS if some error occurred when working with files, in this case ld_error.message is set to the name of the said file;
 * ld_ERR_NOT_DIRECTORY if context.dirname is not in fact a directory;
 * ld_ERR_OUT_OF_MEMORY;
 * ld_ERR_HASHING_ERROR;
 */
struct ld_error ld_next_duplicate(struct ld_context *context) {
    if (!context) {
        return (struct ld_error){.type = ld_ERR_NULL };
    }

    if (RB_EMPTY_ROOT(&context->duplicates_tree.root)) {
        int fd = open(context->dirname, O_RDONLY);

        struct stat stbuf;
        if (fstat(fd, &stbuf) == -1) {
            close(fd);
            return (struct ld_error){.type = ld_ERR_CANT_ACCESS, .message = strdup(context->dirname)};
        }

        if (!S_ISDIR(stbuf.st_mode)) {
            close(fd);
            return (struct ld_error){.type = ld_ERR_NOT_DIRECTORY};
        }

        struct file_list file_list = SLIST_HEAD_INITIALIZER(file_list);

        char const *dirname = context->dirname;
        struct ld_error err = gather_files(context, &file_list, fd, dirname);
        close(fd);
        if (err.type != ld_ERR_OK) {
            file_list_clear(&file_list);
            return err;
        }

        while (!SLIST_EMPTY(&file_list)) {
            if (context->cancelled && *context->cancelled) {
                file_list_clear(&file_list);
                return CANCEL;
            }
            struct file_list_entry *first = SLIST_FIRST(&file_list);
            SLIST_REMOVE_HEAD(&file_list, entries);
            err = add_to_tree(&context->duplicates_tree, &first->file, first->file_size);
            free(first);
            if (err.type != ld_ERR_OK) {
                file_list_clear(&file_list);
                return err;
            }
        }
        context->current_node = find_first_node(&context->duplicates_tree);
    }

    if (!context->current_node) {
        return EOI;
    }

    struct ld_error err = process_node(&context->current_node, &context->dups_list, context->cancelled);
    return err;
}
