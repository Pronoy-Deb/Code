// Complexity: O(N ^ 2)
// Application: Used to determine the minimum number of operations needed to make two strings equal.

long long ed(auto& s, auto& s1) {
    long long m = s.size(), n = s1.size(), dp[m + 1][n + 1];
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (!i) dp[i][j] = j;
            else if (!j) dp[i][j] = i;
            else if (s[i - 1] == s1[j - 1]) dp[i][j] = dp[i - 1][j - 1];
            else dp[i][j] = min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1;
        }
    }
    return dp[m][n];
}

// Problem: https://cses.fi/problemset/task/1639