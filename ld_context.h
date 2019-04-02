#pragma once

#include "ld_duplicates_tree.h"
#include "ld_error.h"
#include "ld_ranked_list.h"

#include "atomics.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \brief Stores search progress, lookup options and atomic flag to interrupt
 *  search.
 *
 *  Must have fields `dups_list`, `cancelled`, `min_file_size`. All field must
 *  be accessed only after initialisation via `ld_context_init`.
 *
 *  \var struct ld_ranked_list dups_list \brief List of duplicates found at the
 *  previous call of `ld_next_duplicate`. Undefined, if `ld_next_duplicate`
 *  hasn't been called or was unsuccessful. If defined, ownership should be
 *  taken by someone, `ld_context_clear` won't free the list.
 *
 *  \var atomic_bool const *cancelled
 *  \brief Flag to indicate if search should interrupt
 *
 *  \var size_t min_file_size
 *  \brief Files with size in bytes less than this will * be ignored. Default: 16
 *
 */
struct ld_context {
    char *dirname;                                // owns
    struct ld_duplicates_tree duplicates_tree;    // owns
    struct ld_duplicates_tree_node *current_node; // owned by duplicates_tree
    struct ld_ranked_list dups_list;              // doesn't own

    atomic_bool const *cancelled;

    // options
    size_t min_file_size;
};

/**
 *  \brief initialises `ld_context`
 *
 *  Sets default option values and directory to search for duplicates in. Must
 *  be accompanied by `ld_context_free`.
 *
 *  \param dirname directory to search for duplicates in
 *  \return `ld_ERR_OK` if succeeded. Otherwise, proper error code.
 */
struct ld_error ld_context_init(struct ld_context *, char const *dirname);

/**
 * \brief cleans up resources owned by `ld_context`.
 */
void ld_context_clear(struct ld_context *);

#ifdef __cplusplus
}
#endif
