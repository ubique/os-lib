//
// Created by dumpling on 30.04.19.
//

#include <iostream>

extern "C" void print_welcome() {
    std::cout << "Stretch the console so that the world is correctly positioned and press any button" << std::endl
              << std::endl;
}

extern "C" void print_help() {
    std::cout << "command line argument:" << std::endl
              << "-ss very small field" << std::endl
              << "-s small field (used by default)" << std::endl
              << "-m medium size field" << std::endl
              << "-b big field" << std::endl
              << std::endl
              << "To control use WASD, to exit Q, to pause (and resume) P" << std::endl;
}

extern "C" void print_game_over() {
    std::cout << "Game over!" << std::endl;
}

extern "C" void print_win() {
    std::cout << "You win!" << std::endl;
}

