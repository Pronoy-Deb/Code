// Formula: P(X = i) = (i / k)^n - ((i - 1) / k)^n for (i = [1, k])
https://cses.fi/problemset/task/1727

long double bex(long double base, long long pow) {
    long double ans = 1;
    while (pow) {
        if (pow & 1) ans *= base;
        base *= base; pow >>= 1;
    }
    return ans;
}
long double ev(long long n, int k) {
    long double val = 0;
    for (long double i = 1; i <= k; ++i)
        val += i * (bex(i / k, n) - bex((i - 1) / k, n));
    return val;
}