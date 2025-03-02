https://atcoder.jp/contests/abc293/tasks/abc293_e
// Complexity: O(log(n))

int64_t m;
int64_t gp(int64_t a, int64_t n) {
	if (n == 0) return 0;
	if (n & 1) return (1 + (a * gp(a, n - 1)) % m) % m;
	return (gp((a * a) % m, n >> 1) * (a + 1)) % m;
}

// OR,

int64_t m;
pair<int64_t, int64_t> gp(int64_t a, int64_t n) {
    if (n == 1) return {a, 1 % m};
    if (n & 1) {
        auto [x, y] = gp(a, n - 1);
        return {(a * x) % m, (1 + (a * y) % m) % m};
    }
    auto [x, L] = gp(a, n >> 1); int64_t R = (x * L) % m;
    return {(x * x) % m, (L + R) % m};
}

// OR, Complexity: O(log^2(n))

int64_t m;
int64_t bex(int64_t base, int64_t pow = M - 2) {
    base %= M; int64_t ans = 1;
    while (pow) {
        if (pow & 1) ans = (ans * base) % m;
        base = (base * base) % m; pow >>= 1;
    }
    return ans;
}
int64_t gp(int64_t a, int64_t n) {
    if (n == 1) return 1 % m;
    if (n & 1) return (1 + (a * gp(a, n - 1)) % m) % m;
    int64_t L = gp(a, n >> 1), R = (bex(a, n >> 1) * L) % m;
    return (L + R) % m;
}

// Note:

* Summation of an arithmetic progression: n * (a + l) >> 1;  // n = number of terms, a = first term, l = last term

* Summation of a geometric progression: (l * r - a) / (r - 1);  // a = first term, l = last term, r = common ratio

* The sum of first n natural numbers:
    i = 1 + 2 + 3 + ... + n = (n * (n + 1)) >> 1;

* The sum of the squares of the first n natural numbers:
    i^2 = 1^2 + 2^2 + 3^2 + ... + n^2 = (n * (n + 1) * ((n << 1) + 1)) / 6;

* The sum of the cubes of the first n natural numbers:
    i^3 = 1^3 + 2^3 + 3^3 + ... + n^3 = (n * n * (n + 1) * (n + 1)) >> 2;

* The sum of the fourth powers of the first n natural numbers:
    i^4 = 1^4 + 2^4 + 3^4 + ... + n^4 = (1/30)*n*(n+1)*(2n+1)*((3*n*n)+(3*n)-1);

* The sum of the first n even natural numbers:
    2i = 2 + 4 + 6 + ... (n numbers) = n * (n + 1);

* The sum of the first n odd natural numbers:
    (2i-1) = 1 + 3 + 5 + .... (n numbers) = n * n;

* The sum of the arithmetic sequence a, a + d, a + 2d, ... , a + (n - 1) d:
    (n >> 1) * ((a << 1) + ((n - 1) * d));  // d = common difference, a = first element

* For the geometric sequence a, ar, ar^2, ... , ar^(n-1),
    The sum of the first n terms:  // r = common ratio, a = first element
    (a * (1 - (int64_t)pow(r, n))) / (1 - r);  // when r < 1
    (a * ((int64_t)pow(r, n) - 1)) / (r - 1);  // when r > 1

* The sum of the infinite terms, ∑∞ = a / (1 - r);  // only when |r| < 1

* 1 + 3 + 6 + 10 + 15 + ... + n = 1 + (1 + 2) + (1 + 2 + 3) + (1 + 2 + 3 + ... + n) + ... + n = (n * (n + 1) * (n + 2)) / 6