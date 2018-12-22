#pragma once

#include "ld_context.h"
#include "ld_error.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ld_error ld_next_duplicate(struct ld_context *context);

#ifdef __cplusplus
}
#endif
