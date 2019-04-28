#include "ldupes.h"

#include <inttypes.h> // uint64_t
#include <dlfcn.h>    // dlopen, dlsym, dlclose, dlerror
#include <stdio.h>    // snprintf, fprintf, stderr
#include <string.h>   // strcpy

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
    void *handle = dlopen("libsize-to-str.so", RTLD_LAZY);
    if (handle == NULL) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    char *(*size_to_str)(size_t size_in_bytes) = dlsym(handle, "size_to_str");
    if (size_to_str == NULL) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    dlerror(); // clear errors

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
            --duplicates_count;
            total_size -= context.dups_list.file_size;
            LD_RANKED_LIST_CLEAR(&context.dups_list);
        } else if (err.type != ld_ERR_END_OF_ITERATION && err.type != ld_ERR_CANCELLED) {
            fprintf(stderr, "error occured: %s\n", error_msg(err));
            ld_context_clear(&context);
            exit(EXIT_FAILURE);
        } else {
            break;
        }
    }
    char *size_presentation = size_to_str(total_size);
    printf("In '%s' %u duplicates found (in %u sets), occupying %s\n", dirname, duplicates_count, sets_count, size_presentation);
    free(size_presentation);

    ld_context_clear(&context);
    dlclose(handle);
}
