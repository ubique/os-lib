#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

#include <foo.h>
#include <bar.h>

const char LIBBAZ_SO[] = "libbaz.so";

int main()
{
    void* libbaz_handle = dlopen(LIBBAZ_SO, RTLD_LAZY);
    if (!libbaz_handle) {
        fprintf(stderr, "Failed to open library: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    
    void (*baz)(void) = (void (*)(void)) dlsym(libbaz_handle, "baz");
    if (!baz) {
        fprintf(stderr, "Failed to load symbol: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    
    foo();
    bar();
    (*baz)();
    printf("\n");
    
    if (dlclose(libbaz_handle) != 0) {
        fprintf(stderr, "Failed to close library: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    
    return EXIT_SUCCESS;
}
