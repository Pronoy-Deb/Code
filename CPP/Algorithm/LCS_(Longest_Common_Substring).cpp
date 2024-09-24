// Complexity: O(n^2)
// To determine the length:

long long lcs(auto &s1, auto &s2) {
    long long m = s1.size(), n = s2.size(), dp[n + 5][m + 5]{}, res = 0;
    for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (s1[i - 1] == s2[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
				res = max(res, dp[i][j]);
			}
		}
	}
	return res;
}

// To determine the substring:

auto lcs(auto &s1, auto &s2) {
    long long m = s1.size(), n = s2.size(), res = 0, len[2][n + 5], end = 0; bool cur = 0;
    for (int i = 0; i <= m; ++i) {
		for (int j = 0; j <= n; ++j) {
			if (i == 0 || j == 0) len[cur][j] = 0;
			else if (s1[i - 1] == s2[j - 1]) {
				len[cur][j] = len[1 - cur][j - 1] + 1;
				if (len[cur][j] > res) {
					res = len[cur][j]; end = i - 1;
				}
			}
			else len[cur][j] = 0;
		}
		cur ^= 1;
	}
	return (!res ? "" : s1.substr(end - res + 1, res));
}

// OR,

auto lcs(auto &s1, auto &s2) {
    int l1 = s1.size(), l2 = s2.size();
    vector<int> dp1(l2 + 5), dp2(l2 + 5);
    int ans = 0, end = 0;
    for (int i = 1; i <= l1; ++i) {
        for (int j = 1; j <= l2; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp1[j] = dp2[j - 1] + 1;
                if (dp1[j] > ans) {
                    ans = dp1[j]; end = i - 1;
                }
            }
            else dp1[j] = 0;
        }
        dp2 = dp1;
    }
    return s1.substr(end - ans + 1, ans);
}