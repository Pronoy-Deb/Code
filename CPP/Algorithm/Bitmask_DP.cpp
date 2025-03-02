// 1. There are n (1 <= n <= 21) men and n women. Compatibility of i-th man with j-th woman is C[i][j] which is either 0 or 1. Find the number of ways to form arrange marriage between them. Problem: Atcoder_dp_0

in64_t n, dp[25][(1 << 21) + 5]; bool C[25][25];
in64_t rec(int in, int mask) {
    if (in == n) return 1;
    auto &res = dp[in][mask];
    if (~res) return res; res = 0;
    for (int i = 0; i < n; ++i) {
        if (C[in][i]) {
            if (mask & (1 << i)) continue;
            res += rec(in + 1, mask | (1 << i));
        }
    }
    return res;
}

// Operation:
    cin >> n;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) cin >> C[i][j];
    }
    memset(dp, -1, sizeof dp);
    cout << rec(0, 0);

2. You are given an array a of n (1 <= n <= 10^5) integers where (1 <= ai <= 70) for every i (1 <= i <= n). Find the number of ways to choose a subset of squares such that their product is a square number. Problem: CF-895C

3. There are n rabbits. Compatibility of i-th and j-th rabbit belong to the same group ai,j. Determine the maximum compatibility of dividing the rabbits into the same groups.

int n, ar[17][17], pre[(1 << 17)], dp[(1 << 17)];

int rec(int mask) {
    if (!mask) return 0;
    auto &res = dp[mask];
    if (res != INT_MIN) return res;
    for (int sm = mask; sm; sm = (sm - 1) & mask)
        res = max(res, pre[sm] + rec(mask ^ sm));
    return res;
}

// Operation:
    cin >> n;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) cin >> ar[i][j];
    }
    for (i = 0; i < (1 << n); ++i) {
        int x = 0; vector<int> v;
        for (j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                for (auto &e : v) x += ar[e][j];
                v.push_back(j);
            }
        }
        pre[i] = x;
    }
    fill (dp, dp + (1 << 17), INT_MIN);
    cout << rec((1 << n) - 1);