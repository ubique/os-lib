//
// Created by dumpling on 30.04.19.
//

#include <iostream>

extern "C" void print_welcome() {
    std::cout << "Stretch the console so that the world is correctly positioned and press any button" << std::endl
              << std::endl;
}

extern "C" void print_help() {
    std::cout << "help";
}

