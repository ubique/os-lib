#pragma once

#include "file_list.h"
#include "rbtree.h" // rb_node rb_root

#include <stddef.h> // size_t

struct cluster_node {
    struct rb_node node;
    size_t file_size;
    struct file_list file_list;
};

struct cluster_node *cluster_node_create(size_t file_size, char const *file_path);

struct cluster_node *cluster_node_search(struct rb_root *root, size_t file_size);

void cluster_node_insert(struct rb_root *root, struct cluster_node *data);

