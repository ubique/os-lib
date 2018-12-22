#pragma once

#include "ld_duplicates_tree.h"
#include "ld_error.h"
#include "ld_ranked_list.h"

#include "atomics.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ld_context {
    char *dirname;                                // owns
    struct ld_duplicates_tree duplicates_tree;    // owns
    struct ld_duplicates_tree_node *current_node; // owned by duplicates_tree
    struct ld_ranked_list dups_list;              // doesn't own
    atomic_bool const *cancelled;                 // doesn't own

    // options
    size_t min_file_size; // in bytes
};

struct ld_error ld_context_init(struct ld_context *, char const *dirname);

void ld_context_clear(struct ld_context *);

#ifdef __cplusplus
}
#endif
