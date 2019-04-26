#include <iostream>
#include "dynamicLoadedFactor.h"

extern "C"
void factor(int number) {
    int curFactor = 2;
    while (number != 1) {
        if (number % curFactor == 0) {
            std::cout << curFactor << " ";
            number /= curFactor;
        } else {
            curFactor++;
        }
    }
}
