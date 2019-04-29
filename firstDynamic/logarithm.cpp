#include <cmath>
#include "logarithm.h"

double getLog(int a, int b) {
    if (b == 1 || b < 0 || a < 0) return -1;
    return log(a) / log(b);
}
