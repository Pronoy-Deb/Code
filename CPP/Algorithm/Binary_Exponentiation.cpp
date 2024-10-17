// Complexity: O(log(pow))
// Note: Modular multiplicative inverse: 1 / n = bex(n, M - 2)
// Iterative Approach:

long long bex(long long base, long long pow = M - 2) {
    base %= M; long long ans = 1;
    while (pow) {
        if (pow & 1) ans = (ans * base) % M;
        base = (base * base) % M; pow >>= 1;
    }
    return ans;
}

// Recursive Approach:

long long bex(long long base, long long pow = M - 2) {
    if (!pow) return 1;
    long long val = bex(base, pow >> 1);
    if (pow & 1) return (base * ((val * val) % M)) % M;
    return (val * val) % M;
}

// For long long value:
// const long long M = 1e18 + 7;

long long bmul(long long a, long long b) {
    long long ans = 0;
    while (b) {
        if (b & 1) ans = (ans + a) % M;
        a = (a + a) % M; b >>= 1;
    }
    return ans;
}
long long bex(long long base, long long pow = M - 2) {
    base %= M; long long ans = 1;
    while (pow) {
        if (pow & 1) ans = bmul(ans, base);
        base = bmul(base, base); pow >>= 1;
    }
    return ans;
}

// Purpose: To Calculate a ^ b ^ c or, pow(a, pow(b, c)):

long long bex(long long a, long long b, long long m) {
    a %= M; long long ans = 1;
    while (b) {
        if (b & 1) ans = (ans * a) % m;
        a = (a * a) % m; b >>= 1;
    }
    return ans;
}

// Calling: bex(a, bex(b, c, M-1), M);