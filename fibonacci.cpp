//
// Created by Павел Пономарев on 2019-04-30.
//
#include <iostream>
#include "fibonacci.h"

extern "C"
int calculateNthFibonacci(int n) {
    if (n <= 0) {
        return 0;
    }
    if (n == 1 || n == 2) {
        return 1;
    }
    int prev = 1;
    int prePrev = 1;
    int result = 0;
    for (int i = 3; i <= n; ++i) {
        result = prePrev + prev;
        prePrev = prev;
        prev = result;
    }
    return result;
}