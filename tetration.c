#include "tetration.h"

unsigned long long int exponentiation(unsigned long long int base, unsigned long long int power) {
    if (power == 0) {
        return 1;
    } else {
        return base * exponentiation(base, power - 1);
    }
}

unsigned long long int tetration(unsigned long long int base, unsigned long long int height) {
    if (height == 0) {
        return 1;
    } else {
        return exponentiation(base, tetration(base, height - 1));
    }
}
