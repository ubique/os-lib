#ifndef DYNAMIC_LINKAGE_HPP
#define DYNAMIC_LINKAGE_HPP

#include <iostream>

inline unsigned int mod() {
    static unsigned int mod = 1000000009;
    return mod;
}

inline unsigned int power(unsigned int x, unsigned int p) {
    if (p == 0) {
        return 1u;
    } else {
        unsigned long long sqrt = power(x, p / 2);
        unsigned long long full = sqrt * sqrt % mod();
        return static_cast<unsigned int>(p % 2 == 0 ? full : (full * x) % mod());
    }
}

void print_inversion(unsigned int x) {
    unsigned int inverse = power(x, mod() - 2);

    static std::string RED = "\033[31m";
    static std::string WHITE = "\033[0m";

    std::cout << RED << x << " * " << inverse << " = 1 (mod " << mod() << ")" << std::endl << WHITE;
}

#endif // DYNAMIC_LINKAGE_HPP
