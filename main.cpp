//
// Created by Anton Shelepov on 2019-05-14.
//

#include "libs/include/static.h"
#include "libs/include/dyn1.h"
#include <dlfcn.h>
#include <iostream>

struct dl_descriptor {
    dl_descriptor(const char* lib_name) {
        desc = dlopen(lib_name, RTLD_LAZY);
        if (desc == nullptr) {
            std::cout << "Couldn't load dynamic library " << lib_name << ": " << dlerror() << std::endl;
            return;
        }
    }

    ~dl_descriptor() {
        if (loaded()) {
            if (dlclose(desc) != 0) {
                std::cout << "Couldn't close dynamic library: " << dlerror() << std::endl;
            }
        }
    }

    bool loaded() {
        return desc != nullptr;
    }

    void* get_function_ptr(const char* func_name) {
        return dlsym(desc, func_name);
    }

private:
    void* desc = nullptr;
};

int main() {

    std::cout << "The first library says: ";
    my_static_lib::greet();
    std::cout << std::endl;
    std::cout << "The second library says: ";
    my_first_dynamic_lib::greet();
    std::cout << std::endl;

    dl_descriptor descriptor("libdyn2.so");

    if (descriptor.loaded()) {
        std::cout << "The third library says: ";
        auto func_ptr = reinterpret_cast<void (*)()>(descriptor.get_function_ptr("greet"));
        if (func_ptr == nullptr) {
            std::cout << "Couldn't get pointer to required function: " << dlerror() << std::endl;
        } else {
            func_ptr();
        }
    }
}