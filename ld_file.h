#pragma once

#include "ld_error.h"

#include <stdbool.h>
#include <stdlib.h> // free

struct ld_file {
    char *path; // owns
    unsigned long long hash;
    bool has_hash;
};

static inline void ld_file_clear(struct ld_file *this) {
    free(this->path);
}
