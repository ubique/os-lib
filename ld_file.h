#pragma once

#ifdef __cplusplus
extern "C" {
#endif


#include "ld_error.h"

#include <stdbool.h>
#include <stdlib.h> // free

struct ld_file {
    char *path; // owns
    unsigned long long hash;
    bool has_hash;
};

static inline void ld_file_clear(struct ld_file *cthis) {
    free(cthis->path);
}


#ifdef __cplusplus
}
#endif
