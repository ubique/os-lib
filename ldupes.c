#include "ldupes.h"
#include "aux.h"
#include "duplicates_tree.h"
#include "ldupes_list.h"

#include <assert.h>
#include <dirent.h> // opendir
#include <fcntl.h>  // openat, fstatat
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> // malloc
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> // close

void ldupes_context_init(struct ldupes_context *context) { assert(context); }

bool is_dir(struct stat stbuf) { return (stbuf.st_mode & S_IFMT) == S_IFDIR; }

bool is_symlink(struct stat stbuf) { return (stbuf.st_mode & S_IFMT) == S_IFLNK; }

bool should_skip(char const *dirname) {
    return (strcmp(dirname, ".") == 0) || (strcmp(dirname, "..") == 0);
}

struct ldupes_error find_files(struct ldupes_list *file_list, int dir_fd, char const *dir_path) {
    DIR *dir_stream;
    if ((dir_stream = fdopendir(dir_fd)) == NULL) {
        return (struct ldupes_error){.type = ldupes_ERR_CANT_ACCESS, .message = NULL};
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
            closedir(dir_stream);
            return OOM;
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
            ldupes_list_add(file_list, new_path, (size_t)child_stbuf.st_size);
        }
        free(new_path);
    }
    closedir(dir_stream);
    return OK;
}

struct ldupes_error ldupes_find_duplicates(struct ldupes_context *context, char const *dirname) {
    assert(context && "Context is NULL"); // TODO return error
    int fd = open(dirname, O_RDONLY);

    struct stat stbuf;
    if (fstat(fd, &stbuf) == -1) {
        close(fd);
        return (struct ldupes_error){.type = ldupes_ERR_CANT_ACCESS, .message = dirname};
    }

    if (!is_dir(stbuf)) {
        close(fd);
        return (struct ldupes_error){.type = ldupes_ERR_NOT_DIRECTORY, .message = dirname};
    }

    struct ldupes_list file_list = {0};
    struct ldupes_error err      = find_files(&file_list, fd, dirname);
    if (err.type != ldupes_ERR_OK) {
        close(fd);
        return err;
    }

    struct duplicates_tree duplicates_tree = {0};
    for (struct ldupes_list_node *it = file_list.node; it; it = it->next) {
        err = duplicates_tree_add(&duplicates_tree, &it->file);
        if (err.type != ldupes_ERR_OK) {
            close(fd);
            return err;
        }
    }

    close(fd);
    return OK;
}
