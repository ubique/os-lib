#include "ld_duplicates_tree.h"

#include <stdlib.h> // free

void destroy_node(struct rb_node *node) {
    if (!node) {
        return;
    }

    struct ld_duplicates_tree_node *container = container_of(node, struct ld_duplicates_tree_node, node);
    LD_RANKED_LIST_CLEAR(container);

    destroy_node(node->rb_left);
    destroy_node(node->rb_right);
    free(node);
}

void ld_duplicates_tree_clear(struct ld_duplicates_tree *this) {
    destroy_node(this->root.rb_node);
}
