int is_prime(int k) {
    if (k <= 1) return 0;
    for (int j = 2; j * j <= k; j++) {
        if (k % j == 0) return 0;
    }
    return 1;
}

int is_composite(int k) {
    if (k < 1) return 1; //all negative numbers and zero are composite
    for (int j = 2; j * j <= k; j++) {
        if (k % j == 0) return 1;
    } 
    return 0;
}