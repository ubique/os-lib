#include "factorial.h"

extern "C"
int factorial(int n) {
	if (n <= 1) {
		return 1;
	}

	int f = 1;
	for (int i = 2; i <= n; i++) {
		f *= i;
	}

	return f;
}

