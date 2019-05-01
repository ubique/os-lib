#include "power.h"

int power(int num, int pow) {
	if (pow == 0) {
		return 1;
	}

	int result = 1;
	for (int i = 0; i < pow; i++) {
		result *= num;
	}
	
	return result;
}
