//
// Created by max on 22.04.19.
//

#include <dlfcn.h>
#include <iostream>

#include "static_link.h"
#include "shared_link1.h"

void show_error(const std::string &msg) {
    std::cerr << msg << std::endl;
    std::cerr << dlerror() << std::endl;
}

int main() {
    std::cout << function_static_link() << std::endl;

    std::cout << std::boolalpha << function_shared_link1(true) << " " << function_shared_link1(false) << std::endl;

    void *shared_lib2 = dlopen("./shared2/libshared_lib2.so", RTLD_NOW);

    if (nullptr == shared_lib2) {
        show_error("Error loading library");
        return EXIT_FAILURE;
    }

    using function_shared_link2_t = std::string (*)(const std::string &);
    if (auto function_shared_link2 =
                ((function_shared_link2_t) dlsym(shared_lib2, "function_shared_link2"));
            nullptr != function_shared_link2) {
        std::cout << function_shared_link2("MAX") << std::endl;
    } else {
        show_error("function function_shared_link2 was not loaded");
        return EXIT_FAILURE;
    }


    using function_shared_link1_t = void (*)();
    if (auto function_shared_link1 =
                (function_shared_link1_t(dlsym(shared_lib2, "function_shared_link2_1")));
            nullptr != function_shared_link1) {
        function_shared_link1();
    } else {
        show_error("function function_shared_link2 was not loaded");
        return EXIT_FAILURE;
    }


    if (0 != dlclose(shared_lib2)) {
        show_error("Error closing library");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}