#include "libstress.h"

void stress_run() {
    volatile double sum = 50;

    double a[10] = {1,2,3,4,5,6,7,8,9,10};

    for (unsigned int i = 0x0fffffff; --i; ) {
        for(int j = 1; j < 10; ++j) {
            a[j] = (a[j - 1]*7 - a[j]) / 2;
        }
        sum = a[1];
    }

}
