#include <algorithm>
#include <iostream>
#include "staticDigitsSum.h"

int digitSum(int num) {
    num = abs(num);
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}
