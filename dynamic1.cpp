#include "dynamic1.h"

int pow(int a, int n) {
    int res = 1;
    while (n != 0)
        if (n & 1) {
            res *= a;
            n--;
        } else {
            a *= a;
            n /= 2;
        }
    return res;
}
