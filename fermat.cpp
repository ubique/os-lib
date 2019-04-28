#include <cmath>
#include <random>

#include "fermat.h"

using ll = long long;

ll modulo(ll base, ll exponent, ll mod)
{
    ll x = 1;
    ll y = base;
    while (exponent > 0)
    {
        if (exponent & 1LL == 1LL)
        {
            x = (__int128(x) * y) % mod;
        }
        y = (__int128(y) * y) % mod;
        exponent >>= 1;
    }
    return x % mod;
}

bool fermat(const ll n)
{
    if (!(n & 1LL) || n <= 1LL)
    {
        return n == 2LL;
    }
    int rounds = std::log2(n) + 1;
    for (auto i = 0; i < rounds; ++i)
    {
        const ll a = rand() % (n - 1) + 1;
        if (modulo(a, n - 1, n) != 1LL)
        {
            return false;
        }
    }
    return true;
}
