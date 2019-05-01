#include "libfnv32.h"

unsigned int fnv32(char const* str) {
    unsigned int hash = 0x811c9dc5;
    while (*str)
    {
        hash *= 0x01000193;
        hash ^= (unsigned int)*(str++);
    }
    return hash;
}

void fnv32_init(struct fnv32* fnv) {
    fnv->hash = 0x811c9dc5;
    fnv->bytes_total = 0;
}

void fnv32_update(struct fnv32* fnv, void* buf, size_t len) {
    fnv->bytes_total += len;

    for (;len --;) {
        fnv->hash *= 0x01000193;
        fnv->hash ^= (unsigned int)*((unsigned char*)buf);
    }
}

unsigned int fnv32_get_hash(struct fnv32* fnv) {
    return fnv->hash;
}

size_t fnv32_get_bytes(struct fnv32* fnv) {
    return fnv->bytes_total;
}
