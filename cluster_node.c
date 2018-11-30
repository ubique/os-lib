#include "cluster_node.h"
#include "rbtree.h" // rb_node rb_root
#include "file_list.h"

#include "assert.h"
#include "stdbool.h"
#include "stddef.h" // size_t
#include "stdlib.h" // malloc

struct cluster_node *cluster_node_create(size_t file_size, char const *file_path) {
    struct cluster_node *new = malloc(sizeof(struct cluster_node));
    new->file_size = file_size;
    new->file_list.node = NULL;
    file_list_add(&new->file_list, file_path);
    return new;
};

struct cluster_node *cluster_node_search(struct rb_root *root, size_t file_size) {
    struct rb_node *node = root->rb_node;

    while (node) {
        struct cluster_node *data = container_of(node, struct cluster_node, node);

        if (file_size < data->file_size) {
            node = node->rb_left;
        } else if (file_size > data->file_size) {
            node = node->rb_right;
        } else {
            return data;
        }
    }
    return NULL;
}

void cluster_node_insert(struct rb_root *root, struct cluster_node *data) {
    struct rb_node **new = &(root->rb_node), *parent = NULL;

    while (*new) {
        struct cluster_node *this = container_of(*new, struct cluster_node, node);
        parent                    = *new;
        if (data->file_size < this->file_size) {
            new = &((*new)->rb_left);
        } else if (data->file_size > this->file_size) {
            new = &((*new)->rb_right);
        } else {
            assert(false && "shouldn't try to insert an already existring node");
        }
    }

    /* Add new node and rebalance node. */
    rb_link_node(&data->node, parent, new);
    rb_insert_color(&data->node, root);
}
