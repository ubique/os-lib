//
// Created by Noname Untitled on 01.05.19.
//

#include <iostream>

extern "C"
void printSum(int first, int second) {
    std::cout << first << " + " << second << " = " << first + second << std::endl;
}

