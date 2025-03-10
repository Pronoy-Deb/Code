// Complexity: O(log(pow))
// Note: Modular multiplicative inverse: 1 / n = bex(n, M - 2)
// Iterative Approach:

int64_t bex(int64_t base, int64_t pow = M - 2) {
    base %= M; int64_t ans = 1;
    while (pow) {
        if (pow & 1) ans = (ans * base) % M;
        base = (base * base) % M; pow >>= 1;
    }
    return ans;
}

// Recursive Approach:

int64_t bex(int64_t base, int64_t pow = M - 2) {
    if (!pow) return 1;
    int64_t val = bex(base, pow >> 1);
    if (pow & 1) return (base * ((val * val) % M)) % M;
    return (val * val) % M;
}

// For int64_t value of M = 9223372036854775783ll;

uint64_t bmul(uint64_t a, uint64_t b) {
    uint64_t ans = 0;
    while (b) {
        if (b & 1) ans = (ans + a) % M;
        a = (a + a) % M; b >>= 1;
    }
    return ans;
}
int64_t bex(int64_t base, int64_t pow = M - 2) {
    base %= M; int64_t ans = 1;
    while (pow) {
        if (pow & 1) ans = bmul(ans, base);
        base = bmul(base, base); pow >>= 1;
    }
    return ans;
}

// OR,

constexpr uint64_t mod = (1ull << 61) - 1;
uint64_t modmul(uint64_t a, uint64_t b) {
	uint64_t l1 = (uint32_t)a, h1 = a >> 32, l2 = (uint32_t)b, h2 = b >> 32;
	uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
	uint64_t ret = (l & mod) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
	ret = (ret & mod) + (ret>>61); ret = (ret & mod) + (ret>>61);
	return ret-1;
}

// Purpose: To Calculate a ^ b ^ c or, pow(a, pow(b, c)):

int64_t bex(int64_t a, int64_t b, int64_t m) {
    a %= M; int64_t ans = 1;
    while (b) {
        if (b & 1) ans = (ans * a) % m;
        a = (a * a) % m; b >>= 1;
    }
    return ans;
}

// Calling: bex(a, bex(b, c, M-1), M);