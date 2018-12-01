#pragma once

#include "ldupes_error.h"
#include "ldupes_list.h"
#include "aux.h"

#include <stddef.h> // size_t
#include <stdlib.h> // malloc
#include <assert.h>

struct duplicates_tree {
    struct duplicates_tree_node {
        struct ldupes_list duplicates;
        struct duplicates_tree_node *lesser, *greater;
    } *node;
};

struct ldupes_error duplicates_tree_add(struct duplicates_tree *this, struct ldupes_file *file);
