#include "dyn1.h"

uint64_t const generate_public_key(int seed)
{
    return uint64_t(42) * static_cast<uint32_t>(seed);
}
