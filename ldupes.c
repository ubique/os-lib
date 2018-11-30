#include "ldupes.h"
#include "cluster_node.h"
#include "file_list.h"

#include "rbtree.h"
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void ldupes_context_init(struct ldupes_context *context) { context->cluster_tree = RB_ROOT; }

bool is_dir(struct stat stbuf) { return (stbuf.st_mode & S_IFMT) == S_IFDIR; }

bool is_symlink(struct stat stbuf) { return (stbuf.st_mode & S_IFMT) == S_IFLNK; }

bool should_skip(char const *dirname) {
    return (strcmp(dirname, ".") == 0) || (strcmp(dirname, "..") == 0);
}

void distribute_to_cluster(struct ldupes_context *context, size_t file_size,
                           char const *file_path) {
    struct rb_root root       = context->cluster_tree;
    struct cluster_node *node = cluster_node_search(&root, file_size);
    if (node) {
        file_list_add(&node->file_list, file_path);
    } else {
        node = cluster_node_create(file_size, file_path);
        cluster_node_insert(&context->cluster_tree, node);
    }
}

struct ldupes_error find_files(struct file_list *file_list, int dir_fd, char const *dir_path) {
    /* fprintf(stderr, "%s\n", dir_path); */
    DIR *dir_stream;
    if ((dir_stream = fdopendir(dir_fd)) == NULL) {
        closedir(dir_stream);
        struct ldupes_error err = {.type = ldupes_ERR_CANT_ACCESS, .message = NULL};
        return err;
    }

    struct dirent *child;
    while ((child = readdir(dir_stream)) != NULL) {
        if (should_skip(child->d_name)) {
            continue;
        }

        size_t dir_path_len = strlen(dir_path);
        size_t child_len    = strlen(child->d_name);
        char *new_path      = malloc(dir_path_len + child_len + 2);
        if (new_path == NULL) {
            struct ldupes_error err = {.type = ldupes_ERR_OUT_OF_MEMORY};
            closedir(dir_stream);
            return err;
        }

        memcpy(new_path, dir_path, dir_path_len);
        new_path[dir_path_len] = '/';
        memcpy(new_path + dir_path_len + 1, child->d_name, child_len);
        new_path[dir_path_len + child_len + 1] = '\0';

        struct stat child_stbuf;
        fstatat(dir_fd, child->d_name, &child_stbuf, AT_SYMLINK_NOFOLLOW);
        // TODO maybe add flag for folowing symlinks ^^^

        if (is_dir(child_stbuf)) {
            int child_fd = openat(dir_fd, child->d_name, O_RDONLY | O_DIRECTORY);
            find_files(file_list, child_fd, new_path);
            close(child_fd);
        } else if (is_symlink(child_stbuf)) {
            // ignore for now, TODO maybe add flag for later
        } else {
            file_list_add(file_list, new_path);
        }
        free(new_path);
    }
    closedir(dir_stream);
    struct ldupes_error err = {.type = ldupes_ERR_OK};
    return err;
}

struct ldupes_error ldupes_find_duplicates(struct ldupes_context *context, char const *dirname) {
    assert(context && "Context is NULL");
    int fd = open(dirname, O_RDONLY);

    struct stat stbuf;
    if (fstat(fd, &stbuf) == -1) {
        close(fd);
        struct ldupes_error err = {.type = ldupes_ERR_CANT_ACCESS, .message = dirname};
        return err;
    }

    if (!is_dir(stbuf)) {
        close(fd);
        struct ldupes_error err = {.type = ldupes_ERR_NOT_DIRECTORY, .message = dirname};
        return err;
    }

    struct file_list file_list;
    struct ldupes_error err = find_files(&file_list, fd, dirname);
    close(fd);
    return err;
}
