#ifndef ROOTS
#define ROOTS

#include <cstddef>

namespace roots {
using ullong = unsigned long long;

const double EPS = 1e-6;

double power(double value, ullong power) {
    double result = 1;
    while (power) {
        if (power & 1) {
            result *= value;
        }
        value *= value;
        power >>= 1;
    }
    return result;
}

template <std::size_t power> double root(double const &value) {
    double left = 0;
    double right = value > 1 ? value / power : value * power;
    while (right - left > EPS) {
        double middle = (left + right) / 2;
        if (roots::power(middle, power) > value) {
            right = middle;
        } else {
            left = middle;
        }
    }
    return left;
}

} // namespace roots

#endif // ROOTS
