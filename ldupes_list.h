#pragma once

#include "ldupes_error.h"

#include <stddef.h> // size_t

struct ldupes_file {
    char const *path;
    size_t size;
};

struct ldupes_list {
    struct ldupes_list_node {
        struct ldupes_file file;
        struct ldupes_list_node *next;
    } *node;
};

struct ldupes_error ldupes_list_add(struct ldupes_list *file_list, char const *file_path, size_t file_size);
