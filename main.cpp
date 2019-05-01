#include "static.h"
#include "first-dynamic.h"

#include <dlfcn.h>

#include <iostream>
#include <cassert>
#include <iostream>

void process_static() {
    std::cout << static_lib::hello() << std::endl;
    assert(static_lib::unique_function_static() == 42);
}


void process_first_dynamic() {
    std::cout << first_dynamic_lib::hello() << std::endl;
    assert(first_dynamic_lib::unique_function_first_dynamic() == 4242);
}

typedef std::string(*hello_type)();
typedef int(*unique_type)();

void print_dlerror() {
    std::cerr << dlerror() << std::endl;
}


void process_second_dynamic() {
    void *handle = dlopen("libsecond-dynamic-lib.so", RTLD_NOW);
    if (handle == nullptr) {
        print_dlerror();
        return;
    }
    auto hello = reinterpret_cast<hello_type>(dlsym(handle, "_Z5helloB5cxx11v"));
    if (hello != nullptr) {
        std::cout << hello() << std::endl;
    } else {
        print_dlerror();
    }
    auto unique = reinterpret_cast<unique_type>(dlsym(handle, "_Z30unique_function_second_dynamicv"));
    if (unique != nullptr) {
        assert(unique() == 424242);
    } else {
        print_dlerror();
    }
    if (dlclose(handle) != 0) {
        print_dlerror();
    }
}


int main() {
    process_static();
    process_first_dynamic();
    process_second_dynamic();
    return 0;
}
