#include "ldupes.h"

#include <inttypes.h> // uint64_t
#include <stdio.h>    // snprintf
#include <string.h>   // strcup

#define DIM(x) (sizeof(x) / sizeof(*(x)))

const char *sizes[]      = {"GiB", "MiB", "KiB", "B"};
const uint64_t gibibytes = 1024ULL * 1024ULL * 1024ULL;

char *calculate_size(size_t size_in_bytes) {
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

char const *error_msg(struct ld_error err) {
    switch (err.type) {
    case ld_ERR_OK:
        return "ok";
    case ld_ERR_CANT_ACCESS:
        return "can't access a file";
    case ld_ERR_NOT_DIRECTORY:
        return "not a directory";
    case ld_ERR_OUT_OF_MEMORY:
        return "out of memory";
    case ld_ERR_END_OF_ITERATION:
        return "end of iteration";
    case ld_ERR_HASHING_ERROR:
        return "hashing error";
    case ld_ERR_CANCELLED:
        return "cancelled";
    case ld_ERR_NULL:
        return "null parameter";
    default:
        return "unexpected error";
    }
}

int main(int argc, char *argv[]) {
    char const *dirname = argc == 1 ? "." : argv[1];
    struct ld_context context;
    ld_context_init(&context, dirname);
    unsigned duplicates_count = 0, sets_count = 0;
    uint64_t total_size = 0;
    while (true) {
        struct ld_error err = ld_next_duplicate(&context);
        if (err.type == ld_ERR_OK) {
            ++sets_count;
            struct ld_ranked_list_entry *it;
            SLIST_FOREACH(it, &context.dups_list, entries) {
                ++duplicates_count;
                total_size += context.dups_list.file_size;
            }
            --duplicates_count, total_size -= context.dups_list.file_size;
            LD_RANKED_LIST_CLEAR(&context.dups_list);
        } else if (err.type != ld_ERR_END_OF_ITERATION && err.type != ld_ERR_CANCELLED) {
            printf("error occured: %s\n", error_msg(err));
            ld_context_clear(&context);
            return 0;
        } else {
            break;
        }
    }
    char *size_presentation = calculate_size(total_size);
    printf("%u duplicates found (in %u sets), occupying %s\n", duplicates_count, sets_count, size_presentation);
    free(size_presentation);
    ld_context_clear(&context);
}
