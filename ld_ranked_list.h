#pragma once

#ifdef __cplusplus
extern "C" {
#endif


#include "ld_error.h"
#include "ld_file.h"

#include <sys/queue.h> // SLIST_*

#include <stddef.h> // size_t
#include <stdlib.h> // free

struct ld_ranked_list_entry {
    SLIST_ENTRY(ld_ranked_list_entry) entries; // owns
    struct ld_file file;
};

struct ld_ranked_list {
    struct ld_ranked_list_entry *slh_first; // owns; don't change the name, macros depend on it
    size_t file_size;
};

#define LD_RANKED_LIST_INIT(head, f_size) \
    do {                                  \
        (head)->slh_first = NULL;         \
        (head)->file_size = (f_size);     \
    } while (0)

#define LD_RANKED_LIST_CLEAR(head)                                  \
    do {                                                            \
        while (!SLIST_EMPTY(head)) {                                \
            struct ld_ranked_list_entry *first = SLIST_FIRST(head); \
            SLIST_REMOVE_HEAD(head, entries);                       \
            ld_ranked_list_entry_destroy(first);                    \
        }                                                           \
    } while (0)

static inline void ld_ranked_list_entry_destroy(struct ld_ranked_list_entry *cthis) {
    if (!cthis) {
        return;
    }
    ld_file_clear(&cthis->file);
    free(cthis);
}

#define LD_RANKED_LIST_SMALL(head) (SLIST_EMPTY(head) || SLIST_NEXT(SLIST_FIRST(head), entries) == NULL)


#ifdef __cplusplus
}
#endif
