//
// Created by rsbat on 5/1/19.
//

#include "fermat.h"

#include <random>

uint64_t gcd(uint64_t a, uint64_t b) {
    while (b) {
        a %= b;
        int64_t tmp = a;
        a = b;
        b = tmp;
    }
    return a;
}

uint64_t binpower(uint64_t x, uint64_t pow, uint64_t mod) {
    int64_t result = 1;
    x %= mod;

    while (pow) {
        if (pow & 1) {
            result *= x;
            result %= mod;
        }
        x *= x;
        x %= mod;
        pow >>= 1;
    }
    return result;
}

extern "C" {
    bool test_fermat(uint64_t number) {
        std::mt19937_64 generator(42); // fixed seed for stable results
        std::uniform_int_distribution<uint64_t> distribution(2, 1'000'000'000);

        auto rnd = [&generator, &distribution]() { return distribution(generator); };

        for (size_t i = 0; i < 10; i++) {
            uint64_t test = rnd();
            if (gcd(test, number) == 1 &&
                binpower(test, number - 1, number) != 1) {
                return false;
            }
        }

        return true;
    }
}