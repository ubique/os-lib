//
// Created by leksoo on 01.05.19.
//

#include <iostream>

#include "and_static.h"

int andStatic(int num1, int num2) {
    std::cout << "andStatic was called" << std::endl;
    return num1 & num2;
}
