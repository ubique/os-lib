#pragma once

#include "ld_duplicates_tree.h"
#include "ld_error.h"
#include "ld_file.h"
#include "atomics.h"

#include <stdbool.h>

static struct ld_error const OK  = {.type = ld_ERR_OK};
static struct ld_error const OOM = {.type = ld_ERR_OUT_OF_MEMORY};
static struct ld_error const EOI = {.type = ld_ERR_END_OF_ITERATION};
static struct ld_error const CANCEL = {.type = ld_ERR_CANCELLED};

struct ld_error check_if_duplicates(struct ld_file *file1, struct ld_file *file2,
        atomic_bool const *cancelled, bool *result);

static inline struct ld_duplicates_tree_node *find_first_node(struct ld_duplicates_tree *tree) {
    struct rb_node *first_rb_node = rb_first(&tree->root);
    return container_of(first_rb_node, struct ld_duplicates_tree_node, node);
}

struct ld_error add_to_tree(struct ld_duplicates_tree *tree, struct ld_file *file, size_t file_size);

struct file_list_entry {
    SLIST_ENTRY(file_list_entry)
    entries;
    struct ld_file file;
    size_t file_size;
};

struct file_list {
    struct file_list_entry *slh_first; // don't change the name, macros depend on it
};

void file_list_clear(struct file_list *this);
