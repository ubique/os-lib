bool is_prime(int n) {
	if (n <= 0) return false;
	for (int i = 2; i * i <= n; ++i) {
		if (!(n % i)) return false;
	}
	return true;
}

