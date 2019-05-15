#include <cmath>

unsigned int setBit(unsigned int base, unsigned int bit) {
    if (bit >= 32) {
        return base;
    }
    auto right = static_cast<unsigned int>(pow(2, bit));
    auto res = base | right;
    return res;
}
