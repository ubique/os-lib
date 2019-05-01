#pragma once
#include <sys/types.h>

struct fnv32 {
    unsigned int hash;
    size_t bytes_total;
};

void fnv32_init(struct fnv32* fnv);
void fnv32_update(struct fnv32* fnv, void* buf, size_t len);
unsigned int fnv32_get_hash(struct fnv32* fnv);
size_t fnv32_get_bytes(struct fnv32* fnv);
