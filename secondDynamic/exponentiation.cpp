#include "exponentiation.h"

extern "C"

int getExp(int a, int b) {
    int res = 1;
    for (int i = 0; i < b; ++i)
        res *= a;
    return res;
}
