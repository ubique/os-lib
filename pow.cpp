//
// Created by daniil on 01.05.19.
//

#include "pow.h"

extern "C" int my_pow(int a, int b) {
    int ans = 1;
    for (int i = 0; i < b; i++) {
        ans *= a;
    }
    return ans;
}