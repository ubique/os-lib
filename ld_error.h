#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct ld_error {
    enum {
        ld_ERR_OK,
        ld_ERR_CANT_ACCESS,
        ld_ERR_NOT_DIRECTORY,
        ld_ERR_OUT_OF_MEMORY,
        ld_ERR_END_OF_ITERATION,
        ld_ERR_HASHING_ERROR,
        ld_ERR_CANCELLED,
    } type;
    char *message;
};

#ifdef __cplusplus
}
#endif
