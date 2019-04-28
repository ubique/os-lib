#include <chrono>
#include <cmath>
#include <random>

#include "millerrabin.h"

using namespace modulo;

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

bool miller_rabin(const ll n, int rounds)
{
    if (!(n & 1LL) || n <= 1LL)
    {
        return n == 2LL;
    }
    if (rounds <= 0)
    {
        rounds = std::log2(n) + 1;
    }

    ll t = n - 1;
    int s = 0;
    while (!(t & 1)) // n - 1 = 2^s * t
    {
        ++s;
        t >>= 1;
    }
    std::uniform_int_distribution<ll> unif(2, n - 1);
    const auto one = mi(1, n);
    const auto nmo = mi(n - 1, n);
    for (auto i = 0; i < rounds; ++i)
    {
        mi x(unif(rng), n);
        x = exp(x, t);
        if (x == one || x == nmo)
        {
            continue;
        }
        int j = 1;
        for (; j < s; ++j)
        {
            x *= x;
            if (x == one)
            {
                return false;
            }
            if (x == nmo)
            {
                break;
            }
        }
        if (j == s) return false;
    }
    return true;
}
