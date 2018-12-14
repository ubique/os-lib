#pragma once

#ifdef __cplusplus
extern "C" {
#endif


#include "ld_error.h"
#include "ld_ranked_list.h"
#include "rbtree.h"

#include <stddef.h> // size_t

struct ld_duplicates_tree {
    struct rb_root root;
};

struct ld_duplicates_tree_node {
    struct rb_node node;
    struct ld_ranked_list_entry *slh_first; // owns; don't change the name, macros depend on it
    size_t file_size;
};

void ld_duplicates_tree_clear(struct ld_duplicates_tree *);


#ifdef __cplusplus
}
#endif
