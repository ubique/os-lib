#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

#include <A.h>
#include <B.h>

const char* libName = "./build/libC/libC.so";

int main() {
    printf("Static lib: \n");
    printA();
    printf("Dynamic lib, linking by hands: \n");
    printB();
    printf("Dynamic lib in runtime: \n");
    void* libHandle = dlopen(libName, RTLD_LAZY);
    if (!libHandle) {
        fprintf (stderr, "Error while opening library! Cause: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    void (*printC)(void) = (void (*)(void))dlsym(libHandle, "printC");
    if (dlerror() != NULL)  {
        fprintf (stderr, "Error: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    (*printC)();
    if(dlclose(libHandle)) {
        fprintf (stderr, "Error while closing! Cause: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}