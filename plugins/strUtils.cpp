#include "common.h"
#include <algorithm>

using namespace std;


extern "C" char const *reverse(char const *arg) {
    string s = arg;
    reverse(s.begin(), s.end());
    return getCharPtr(s);
}


extern "C" char const *hash(char const *arg) {
    uint64_t hash = 0;
    const uint64_t MOD = 1503991337;
    const uint64_t P = 257;

    for (int i = 0; arg[i] != '\0'; i++) {
        hash *= P;
        hash += arg[i];
        hash %= MOD;
    }

    return getCharPtr(to_string(hash));
}

