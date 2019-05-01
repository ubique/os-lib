#include "first-dynamic.h"

std::string first_dynamic_lib::get_library_name() {
    return "first dynamic";
}

std::string first_dynamic_lib::hello() {
    return "Hello, I'm " + get_library_name() + " library";
}

int first_dynamic_lib::unique_function_first_dynamic() {
    return 4242;
}
