#include <cmath>

#include "trial_division.h"

using ll = long long;

bool trial_division(const ll n)
{
    if (!(n & 1LL) || n <= 1LL)
    {
        return n == 2LL;
    }
    const ll sqr = std::sqrt(n) + 1;
    for (ll x = 2; x <= sqr; ++x)
    {
        if (n % x == 0) return false;
    }
    return true;
}
