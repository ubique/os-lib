//
// Created by vitalya on 01.05.19.
//

#include "hello_world_static.h"
#include "hello_world_dynamic1.h"
#include "hello_world_dynamic2.h"

#include <dlfcn.h>
#include <iostream>

int main() {
    void* dynamic_lib = dlopen("shared_lib2/libshared_lib2.so", RTLD_LAZY);
    if (!dynamic_lib) {
        std::cout << "Error while loading dynamic library: " + std::string(dlerror()) << std::endl;
        return EXIT_FAILURE;
    }

    auto hello_world_dynamic2 = (char* (*)())dlsym(dynamic_lib, "hello_world_dynamic2");
    if (!hello_world_dynamic2) {
        std::cout << "Error while loading function from dynamic library: " + std::string(dlerror()) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << hello_world_static() << std::endl;
    std::cout << hello_world_dynamic1() << std::endl;
    std::cout << hello_world_dynamic2() << std::endl;

    if (dlclose(dynamic_lib) != 0) {
        std::cout << "Error while closing dynamic library: " + std::string(dlerror()) << std::endl;
        return EXIT_FAILURE;
    }
}