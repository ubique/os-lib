#pragma once

#include "ldupes_error.h"

static struct ldupes_error const OK = {.type = ldupes_ERR_OK};
static struct ldupes_error const OOM = {.type = ldupes_ERR_OUT_OF_MEMORY};
