//
// Created by rsbat on 5/1/19.
//

#include "fast.h"

bool test_fast(uint64_t number) {
    for (uint64_t i = 2; i * i < number; i++) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}