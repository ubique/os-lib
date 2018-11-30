#include "file_list.h"

#include <stdlib.h> // malloc

#ifdef __STDC_ALLOC_LIB__ // needed for dynamic memory TR
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif
#include <string.h> // strdup

void file_list_init(struct file_list *file_list) { file_list->node = NULL; }

void file_list_add(struct file_list *file_list, char const *file_path) {
    struct file_list_node *new_node = malloc(sizeof(struct file_list_node));
    // TODO check new_node for NULL
    new_node->file_path             = strdup(file_path);
    new_node->next                  = file_list->node;
    file_list->node                 = new_node;
}
