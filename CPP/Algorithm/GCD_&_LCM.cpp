// Complexity: O(log(min(a, b)))
// Note: The algorithm is also called Euclidean Algorithm
// Built-in: gcd(a, b);
// Iterative Approach:

int64_t gc(int64_t a, int64_t b) {
    while (b) {
        int64_t tmp = a; a = b; b = tmp % b;
    }
    return a;
}

// Recursive Approach:

int64_t gc(int64_t a, int64_t b) {
    return (!b ? a : gc(b, a % b));
}

// OR,

int64_t gc(int64_t a, int64_t b) {
    if (!a || a == b) return b;
    if (!b) return a;
    if (~a & 1) {
        if (b & 1) return gc(a >> 1, b);
        return gc(a >> 1, b >> 1) << 1;
    }
    if (~b & 1) return gc(a, b >> 1);
    if (a > b) return gc((a - b) >> 1, b);
    return gc((b - a) >> 1, a);
}

// Pre-computation in a 2-D array:
// Complexity: O(n^2 * log(n))

int64_t gc[N][N];
void pre() {
    for (int i = 2; i < N; ++i) {
        for (int j = i; j < N; j += i) {
            gc[i][j] = i;
            for (int k = j + i; k < N; k += i) gc[j][k] = gc[k][j] = i;
        }
    }
}

Operation: gc[a][b] ? gc[a][b] : 1

// LCM: O(log(min(a, b)))
// Built-in: lcm(a, b);

int64_t lc(int64_t a, int64_t b) {
    int64_t ans = a * b;
    while (b) {
        int64_t tmp = a; a = b; b = tmp % b;
    }
    return (ans / a);
}

// OR,

int64_t lc(int64_t a, int64_t b) {
	if (a < b) swap(a, b);
	int64_t tmp = a; while (tmp % b) tmp += a;
	return tmp;
}

// Pre-computation Approach:
// Complexity: O(n^2 * log(n))

int64_t gc[N][N];
void pre() {
    for (int i = 2; i < N; ++i) {
        for (int j = i; j < N; j += i) {
            gc[i][j] = i;
            for (int k = j + i; k < N; k += i) {
                gc[j][k] = gc[k][j] = i;
            }
        }
    }
}
int64_t lc(int64_t a, int64_t b) {
    return ((a * b) / (gc[a][b] ? gc[a][b] : 1));
}