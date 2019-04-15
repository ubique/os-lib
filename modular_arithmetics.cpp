int sum(int a, int b, int mod) {
    return (1LL * a + b) % mod;
}

int mul(int a, int b, int mod) {
    return (1LL * a * b) % mod;
}

int sub(int a, int b, int mod) {
    return sum(a, (mod - b % mod) % mod, mod);
}