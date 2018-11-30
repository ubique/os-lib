#pragma once

#include "ldupes_error.h"

struct ldupes_context {
};

void ldupes_context_init(struct ldupes_context *context);

struct ldupes_error ldupes_find_duplicates(struct ldupes_context *, char const *dirname);
