#include "ldupes_list.h"
#include "ldupes_error.h"
#include "aux.h"

#include <stdlib.h> // malloc

#ifdef __STDC_ALLOC_LIB__ // needed for dynamic memory TR
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <string.h> // strdup

struct ldupes_error ldupes_list_add(struct ldupes_list *file_list, char const *file_path, size_t file_size) {
    struct ldupes_list_node *new_node = malloc(sizeof(struct ldupes_list_node));
    if (!new_node) {
        return OOM;
    }
    new_node->file.path = strdup(file_path);
    new_node->file.size = file_size;
    new_node->next = file_list->node;
    file_list->node = new_node;
    return OK;
}
