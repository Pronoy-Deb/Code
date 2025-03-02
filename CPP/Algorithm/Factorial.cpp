// Complexity: O(n)
// Iterative Approach:  // Results till 20!

int64_t fac(int64_t n) {
    int64_t res = 1;
    for (int i = 2; i <= n; ++i) res *= i;
    return res;
}

// Taking the values modulo M = 1e9 + 7:

int64_t fac(int64_t n) {
    int64_t res = 1;
    for (int i = 2; i <= n; ++i) res = (res * i) % M;
    return res;
}

// Recursive Approach:

int64_t fac(int64_t n) {
    return (n ? (fac(n - 1) * n) : 1);
}

// Storing the factorial values:

int64_t fac[N];
void pre() {
    fac[0] = fac[1] = 1;
    for (int i = 2; i < N; ++i) fac[i] = (fac[i - 1] * i) % M;
}

// String Approach:  // O(n^2)

auto fac(int64_t n) {
    string s = "1";
    for (int64_t i = 2; i <= n; ++i) {
        int64_t c = 0, sz = s.size();
        for (int j = 0; j < sz; ++j) {
            int64_t a = (s[j] - 48) * i + c; s[j] = (a % 10) + 48; c = a / 10;
        }
        while (c) {
            s += ((c % 10) + 48); c /= 10;
        }
    }
    reverse(s.begin(), s.end()); return s;
}

// Vector Approach:

auto fac(int64_t n) {
    vector<int64_t> v = {1};
    for (int64_t i = 2; i <= n; ++i) {
        int64_t c = 0, sz = v.size();
        for (int j = 0; j < sz; ++j) {
            int64_t a = v[j] * i + c; v[j] = a % 10; c = a / 10;
        }
        while (c) {
            v.emplace_back(c % 10); c /= 10;
        }
    }
    reverse(v.begin(), v.end()); return v;
}