// Complexity: O(n * wt)
// wt = Total weight, p = profit, w = weight.

long long n, wt, dp[N], w[N], p[N];
auto knap() {
    for(int i = 0; i < n; ++i) {
        for(int j = wt; j >= w[i]; --j) {
            dp[j] = max(dp[j], p[i] + dp[j - w[i]]);
        }
    }
    return dp[wt];
}

// Operation:
    cin >> n >> wt;
    for (i = 0; i < n; ++i) cin >> w[i];
    for (i = 0; i < n; ++i) cin >> p[i];
    cout << knap();

// Problem: https://cses.fi/problemset/task/1158/