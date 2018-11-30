#pragma once

#include "rbtree.h" // rb_root

struct ldupes_error {
    enum {
        ldupes_ERR_OK,
        ldupes_ERR_CANT_ACCESS,
        ldupes_ERR_NOT_DIRECTORY,
        ldupes_ERR_OUT_OF_MEMORY
    } type;
    char const *message;
};

struct ldupes_context {
    struct rb_root cluster_tree;
};

void ldupes_context_init(struct ldupes_context *context);

struct ldupes_error ldupes_find_duplicates(struct ldupes_context *, char const *dirname);
