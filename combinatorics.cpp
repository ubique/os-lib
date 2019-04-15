
int nth_fibonacci(int n, int mod) {
    if (n == 0) return 0;
    int f0 = 0, f1 = 1;
    for (int i = 2; i <= n; i++) {
        int k = (1LL * f1 + f0) % mod;
        f0 = f1;
        f1 = k;
    }
    return f1;
}

int factorial(int n, int mod) {
    if (n < 0) return 0;
    int ans = 1;
    for (int j = 0; j < n; j++) {
        ans = (1LL * ans * (j + 1)) % mod;
    }
    return ans;
}
