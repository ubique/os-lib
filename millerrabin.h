#pragma once
#include <iostream>
#include <limits>

using ll = long long;

bool miller_rabin(const ll n, int rounds = 0);

namespace modulo 
{

using ll = long long;
using typ = ll;

const typ MOD = std::numeric_limits<typ>::max() / 2;

ll inv_general(ll a, ll b)
{
    a %= b;
    if (a == 0) return b == 1 ? 0 : -1;
    ll x = inv_general(b, a);
    return x == -1 ? -1 : ((1 - ll(b) * x) / a + b) % b;
}

struct mi
{
    typ val;
    typ mod;

    mi(typ val = 0, typ mod = MOD)
        : val(val), mod(mod)
    {
        normalize();
    }

    mi& operator+=(mi const& b)
    {
        if ((val += typ(b)) >= mod) val -= mod;
        return *this;
    }

    mi& operator-=(mi const& b)
    {
        if ((val -= typ(b)) < 0) val += mod;
        return *this;
    }

    mi& operator*=(mi const& b)
    {
        val = __int128(val) * typ(b.val) % mod;
        return *this;
    }

    explicit operator typ() const { return val; }
    friend std::ostream& operator<<(std::ostream& os, const mi& a) { return os << a.val; }
    friend bool operator==(const mi& a, const mi& b) { return a.val == b.val; }
    friend bool operator!=(const mi& a, const mi& b) { return !(a == b); }

    friend mi operator+(mi a, const mi& b) { return a += b; }
    friend mi operator-(mi a, const mi& b) { return a -= b; }
    friend mi operator-(const mi& a) { return mi(0) - a; }
    friend mi operator*(mi a, const mi& b) { return a *= b; }

    void normalize()
    {
        if (mod == 0) return;
        val %= mod;
        if (val < 0) val += mod;
    }

    friend mi exp(mi b, ll p);

};

mi exp(mi b, ll p)
{
    mi ans = mi(1, b.mod);
    for (; p; p >>= 1, b *= b) if (p & 1) ans *= b;
    return ans;
}

}
