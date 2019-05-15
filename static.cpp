#include <iostream>

void printBinary(unsigned int i) {
    int buf[64];
    int index = 0;
    while (i != 0) {
        buf[index++] = i % 2;
        i /= 2;
    }
    for (int j = index - 1; j > -1; j--) {
        std::cout << buf[j];
    }
    std::cout << std::endl;
}

