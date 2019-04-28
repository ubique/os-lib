#include <inttypes.h> // uint64_t, PRIu64
#include <stdio.h>    // snprintf
#include <string.h>   // strcpy
#include <stdlib.h>   // malloc

#define DIM(x) (sizeof(x) / sizeof(*(x)))

const char *sizes[]      = {"GiB", "MiB", "KiB", "B"};
const uint64_t gibibytes = 1024ULL * 1024ULL * 1024ULL;

char *size_to_str(size_t size_in_bytes) {
    char *result        = malloc(sizeof(char) * 20);
    uint64_t multiplier = gibibytes;

    for (size_t i = 0; i < DIM(sizes); i++, multiplier /= 1024) {
        if (size_in_bytes < multiplier) {
            continue;
        }
        if (size_in_bytes % multiplier == 0) {
            snprintf(result, 20, "%" PRIu64 " %s", size_in_bytes / multiplier, sizes[i]);
        } else {
            snprintf(result, 20, "%.1lf %s", (double)size_in_bytes / multiplier, sizes[i]);
        }
        return result;
    }
    strcpy(result, "0");
    return result;
}
