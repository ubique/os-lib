//
// Created by leksoo on 01.05.19.
//
#include <iostream>

#include "xor_loaded.h"
extern "C"
int xorLoaded(int num1, int num2) {
    std::cout << "xorLoaded was called" << std::endl;
    return num1 ^ num2;
}
