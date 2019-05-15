//
// Created by Anton Shelepov on 2019-05-14.
//

#include "dyn1.h"
#include <iostream>

void my_first_dynamic_lib::greet() {
    std::cout << "Hello, I'm first dynamic library. I was built dynamically, linked to the program during linkage and provide some functions." << std::endl;
}