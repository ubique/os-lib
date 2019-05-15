//
// Created by Anton Shelepov on 2019-05-14.
//

#include "dyn2.h"
#include <iostream>

extern "C" {

void greet() {
    std::cout
            << "Hello, I'm second dynamic library. I was built dynamically, loaded at runtime and provide some functions."
            << std::endl;
}

}