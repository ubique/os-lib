//
// Created by Павел Пономарев on 2019-04-30.
//

#include <iostream>
#include "combination.h"

unsigned long long nextCombinationMask(unsigned long long currentMask) {
    unsigned long long a = currentMask & -currentMask;
    unsigned long long b = currentMask + a;
    unsigned long long c = b ^ currentMask;
    a <<= 2;
    c /= a;
    return b | c;
}
