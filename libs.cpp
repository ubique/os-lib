//
// Created by dumpling on 30.04.19.
//

#include <iostream>
#include <dlfcn.h>

std::string get_hello();

std::string get_world();

using func_type = std::string(*)();

void print_err() {
    std::cerr << "\033[31m" << dlerror() << "\033[0m" << std::endl;
}

int main() {

    auto handle = dlopen("./libsecond_shared.so", RTLD_NOW);
    if (handle == nullptr) {
        print_err();
    }

    auto fun = dlsym(handle, "get_exclamation");
    if (fun == nullptr) {
        print_err();
    }

    auto last_part = (reinterpret_cast<func_type>(fun))();

    std::cout << get_hello() << ", " << get_world() << last_part << std::endl;

    if (dlclose(handle) != 0) {
        print_err();
    }
}

