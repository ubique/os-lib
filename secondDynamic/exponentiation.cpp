#include "exponentiation.h"

int getExp(int a, int b) {
    if (b == 0)
        return 1;
    if (b % 2 == 1)
        return getExp(a, b - 1) * a;
    else {
        int b = getExp(a, b / 2);
        return b * b;
    }
}
