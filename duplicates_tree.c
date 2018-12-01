#include "duplicates_tree.h"

struct ldupes_error insert(struct duplicates_tree_node **p_this, struct ldupes_file *file) {
    assert(p_this);
    if (!*p_this) {
        *p_this = calloc(1, sizeof(struct duplicates_tree_node));
        if (!*p_this) { return OOM; }
        return ldupes_list_add(&(*p_this)->duplicates, file->path, file->size);
    }

    assert((*p_this)->duplicates.node);
    size_t this_size = (*p_this)->duplicates.node->file.size;
    if (file->size < this_size) {
        return insert(&(*p_this)->lesser, file);
    } else if (file->size > this_size) {
        return insert(&(*p_this)->greater, file);
    } else {
        return ldupes_list_add(&(*p_this)->duplicates, file->path, file->size);
    }
}

struct ldupes_error duplicates_tree_add(struct duplicates_tree *this, struct ldupes_file *file) {
    return insert(&this->node, file);
}
