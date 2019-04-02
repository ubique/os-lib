#pragma once

#include "ld_context.h"
#include "ld_error.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief ld_next_duplicate Find next group of duplicates and store results in
 * \param context.
 *
 * Each duplicate size is less than size of that in the previous call.
 *
 * @param context
 * @return ld_ERR_OK if next duplicate group is successfully found;
 * ld_ERR_END_OF_ITERATION if there are no more duplicates;
 * ld_ERR_CANCELLED if file gathering was cancelled from another thread;
 * ld_ERR_NULL if context is null;
 * ld_ERR_CANT_ACCESS if some error occurred when working with files, in this case ld_error.message is set to the name of the said file;
 * ld_ERR_NOT_DIRECTORY if context.dirname is not in fact a directory;
 * ld_ERR_OUT_OF_MEMORY;
 * ld_ERR_HASHING_ERROR;
 */
struct ld_error ld_next_duplicate(struct ld_context *context);

#ifdef __cplusplus
}
#endif
