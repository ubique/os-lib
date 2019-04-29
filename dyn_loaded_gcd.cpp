extern "C" {
	int gcd(int, int);
}
int gcd_(int a, int b) {
	return (b ? gcd_(b, a % b) : a);
}

int gcd(int a, int b) {
	return (a >= b ? gcd_(a, b) : gcd_(b, a));
}
