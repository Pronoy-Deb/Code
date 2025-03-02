// Formula: P(X = i) = (i / k)^n - ((i - 1) / k)^n for (i = [1, k])
https://cses.fi/problemset/task/1727

long double bex(long double base, int64_t pow) {
    long double ans = 1;
    while (pow) {
        if (pow & 1) ans *= base;
        base *= base; pow >>= 1;
    }
    return ans;
}
long double ev(int64_t n, int k) {
    long double val = 0;
    for (long double i = 1; i <= k; ++i)
        val += i * (bex(i / k, n) - bex((i - 1) / k, n));
    return val;
}

https://atcoder.jp/contests/abc382/tasks/abc382_e

int P[N], n;
auto pre() {
    vector<long double> prob(n + 1); prob[0] = 1.0;
    for (int i = 0; i < n; ++i) {
        long double p = P[i] / 100.0;
        for (int k = n; k >= 1; --k) prob[k] = prob[k] * (1 - p) + prob[k - 1] * p;
        prob[0] *= (1 - p);
    }
    return prob;
}
long double ex(int X) {
    vector<long double> prob = pre(), dp(X + 1, 1.0); dp[0] = 0.0;
    for (int x = 1; x <= X; ++x) {
        for (int k = 1; k <= n && k <= x; ++k) dp[x] += prob[k] * dp[x - k];
        dp[x] /= (1 - prob[0]);
    }
    return dp[X];
}