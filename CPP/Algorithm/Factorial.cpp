// Complexity: O(n)
// Iterative Approach:  // Results till 20!

long long fac(long long n) {
    long long res = 1;
    for (int i = 2; i <= n; ++i) res *= i;
    return res;
}

// Taking the values modulo M = 1e9 + 7:

long long fac(long long n) {
    long long res = 1;
    for (int i = 2; i <= n; ++i) res = (res * i) % M;
    return res;
}

// Recursive Approach:

long long fac(long long n) {
    return (n ? (fac(n - 1) * n) : 1);
}

// Storing the factorial values:

long long fac[N];
void pre() {
    fac[0] = fac[1] = 1;
    for (int i = 2; i < N; ++i) fac[i] = (fac[i - 1] * i) % M;
}

// String Approach:  // O(n^2)

auto fac(long long n) {
    string s = "1";
    for (long long i = 2; i <= n; ++i) {
        long long c = 0, sz = s.size();
        for (int j = 0; j < sz; ++j) {
            long long a = (s[j] - 48) * i + c; s[j] = (a % 10) + 48; c = a / 10;
        }
        while (c) {
            s += ((c % 10) + 48); c /= 10;
        }
    }
    reverse(s.begin(), s.end()); return s;
}

// Vector Approach:

auto fac(long long n) {
    vector<long long> v = {1};
    for (long long i = 2; i <= n; ++i) {
        long long c = 0, sz = v.size();
        for (int j = 0; j < sz; ++j) {
            long long a = v[j] * i + c; v[j] = a % 10; c = a / 10;
        }
        while (c) {
            v.emplace_back(c % 10); c /= 10;
        }
    }
    reverse(v.begin(), v.end()); return v;
}