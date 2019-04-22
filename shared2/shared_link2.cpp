//
// Created by max on 22.04.19.
//

#include <iostream>
#include "shared_link2.h"

extern "C" {

std::string function_shared_link2(const std::string &name) {
    return std::string("Hello, ").append(name).append("!");
}

void function_shared_link2_1() {
    std::cout << "HI" << std::endl;
}
}