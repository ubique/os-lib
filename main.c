#include "ldupes.h"

int main(int argc, char *argv[]) {
    struct ldupes_context context;
    ldupes_context_init(&context);
    if (argc == 1) {
        ldupes_find_duplicates(&context, ".");
    } else {
        ldupes_find_duplicates(&context, argv[1]);
    }
}
