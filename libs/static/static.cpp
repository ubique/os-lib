#include "static.h"

uint64_t const generate_secret_key(int seed)
{
    return uint64_t(1337) * static_cast<uint32_t>(seed);
}
