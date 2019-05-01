#include "second-dynamic.h"

std::string get_library_name() {
    return "second dynamic";
}

std::string hello() {
    return "Hello, I'm " + get_library_name() + " library";
}

int unique_function_second_dynamic() {
    return 424242;
}
