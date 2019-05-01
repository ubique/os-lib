//
// Created by Кирилл Чулков on 2019-05-01.
//

#include <iostream>

#include "fibonacci.h"

long long functionalFibonacci(long long f, long long s, int n) {
    return n == 0 ? f : functionalFibonacci(s, f + s, n - 1);
}

long long calculateFibonacci(int n) {
    return functionalFibonacci(1, 1, n);
}
