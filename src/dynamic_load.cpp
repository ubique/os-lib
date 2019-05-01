#include "dynamic_load.hpp"

#include <iostream>

static unsigned int MOD = 1000000009;

unsigned int power(unsigned int x, unsigned int p) {
    if (p == 0) {
        return 1u;
    } else {
        unsigned long long sqrt = power(x, p / 2);
        unsigned long long full = sqrt * sqrt % MOD;
        return static_cast<unsigned int>(p % 2 == 0 ? full : (full * x) % MOD);
    }
}

void print_inversion(unsigned int x) {
    unsigned int inverse = power(x, MOD - 2);

    static std::string RED = "\033[31m";
    static std::string WHITE = "\033[0m";

    std::cout << RED << x << " * " << inverse << " = 1 (mod " << MOD << ")" << std::endl << WHITE;
}
