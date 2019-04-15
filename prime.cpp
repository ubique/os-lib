bool is_prime(int k) {
    if (k <= 1) return false;
    for (int j = 2; j * j <= k; j++) {
        if (k % j == 0) return false;
    }
    return true;
}

bool is_composite(int k) {
    if (k < 1) return true; //all negative numbers and zero are composite
    for (int j = 2; j * j <= k; j++) {
        if (k % j == 0) return true;
    } 
    return false;
}