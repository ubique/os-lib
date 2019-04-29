int bin_pow(int x, int p) { 
	int res = 1;
	while (p) {
		if (p & 1) {
			res *= x;
			--p;
		} else {
			x *= x;
			p >>= 1;
		}
	}
	return res;
}

