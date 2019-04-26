#include <algorithm>
#include <iostream>
#include "dynamicLinkedGcd.h"

int gcd(int first, int second) {
    if (first < 0 || second < 0) {
        std::cerr << "Numbers should be positive" << std::endl;
        exit(EXIT_FAILURE);
    }
     if (second > first) {
        std::swap(first, second);
    }
    if (second == 0) {
        return first;
    }
    if (first % 2 == 0 && second % 2 == 0) {
        return 2 * gcd(first / 2, second / 2);
    }
    if (first % 2 == 0) {
        return gcd(first / 2, second);
    }
    if (second % 2 == 0) {
        return gcd(first, second / 2);
    }
    return gcd(first - second, second);
}
