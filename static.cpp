#include "static.h"

std::string static_lib::get_library_name() {
    return "static";
}

std::string static_lib::hello() {
    return "Hello, I'm " + get_library_name() + " library";
}

int static_lib::unique_function_static() {
    return 42;
}
