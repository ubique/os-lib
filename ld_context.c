#include "ld_context.h"
#include "aux.h"

#ifdef __STDC_ALLOC_LIB__ // needed for dynamic memory TR
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <assert.h>
#include <stdlib.h> // free
#include <string.h> // strdup

struct ld_error ld_context_init(struct ld_context *this, char const *dirname) {
    assert(this && dirname);
    this->dirname = strdup(dirname);
    if (!this->dirname) {
        return OOM;
    }
    this->duplicates_tree.root = RB_ROOT;
    this->current_node         = NULL;
    SLIST_INIT(&this->dups_list);

    this->min_file_size = 16;
    return OK;
}

void ld_context_clear(struct ld_context *this) {
    free(this->dirname);
    ld_duplicates_tree_clear(&this->duplicates_tree);
}
