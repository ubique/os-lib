#pragma once

struct ldupes_error {
    enum {
          ldupes_ERR_OK,
          ldupes_ERR_CANT_ACCESS,
          ldupes_ERR_NOT_DIRECTORY,
          ldupes_ERR_OUT_OF_MEMORY
    } type;
    char const *message;
};
