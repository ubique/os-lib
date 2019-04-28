#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "greater.h"
#include "usergreater.h"

#define ull unsigned long long int
#define DLERROR_CHECK if ((error = dlerror()) != NULL) {fprintf(stderr, "%s\n", error);exit(EXIT_FAILURE);};

int main() {
    printHelloWorld(); // from libgreater.a
    printHelloUserString("Username"); // from libusergreater.so

    // from libtetration.so
    char* error;
    void* handle = dlopen("libtetration.so", RTLD_LAZY);
    if (!handle) {
        fputs(dlerror(), stderr);
        exit(EXIT_FAILURE);
    }
    DLERROR_CHECK;
    ull (* tetration)(ull, ull) = (ull (*)(ull, ull)) dlsym(handle, "tetration");
    DLERROR_CHECK;
    ull base = 2;
    ull height = 4;
    printf("tetration of base %llu and height %llu = %llu\n", base, height, (*tetration)(base, height));
    dlclose(handle);
    DLERROR_CHECK;
    return EXIT_SUCCESS;
}
