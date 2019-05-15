//
// Created by Anton Shelepov on 2019-05-14.
//

#include "static.h"
#include <iostream>

void my_static_lib::greet() {
    std::cout << "Hello, I'm static library. I was built statically and provide some functions." << std::endl;
}