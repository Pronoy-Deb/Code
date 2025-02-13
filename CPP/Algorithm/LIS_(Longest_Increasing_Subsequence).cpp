// Note: Gives result of STRICTLY incresing subsequence
// For longest non-decreasing subsequence, replace 'lower_bound' with 'upper_bound' and for longest decreasing subsequence, replace aa[i] *= -1;
// Iterative Approach to determine the length: O(n * log(n))

int64_t aa[N], n;
int lis() {
    vector<int64_t> ans; ans.push_back(aa[0]);
    for (int i = 1; i < n; ++i) {
        if (aa[i] > ans.back()) ans.push_back(aa[i]);
        else {
            int low = lower_bound(ans.begin(), ans.end(), aa[i]) - ans.begin();
            ans[low] = aa[i];
        }
    }
    return (int)ans.size();
}

// Complexity: O(n^2)  // For all of the following codes

int lis(auto &v) {
    int n = v.size(), dp[n], ans = 1;
    for (int i = 0; i < n; ++i) {
        dp[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (v[j] < v[i]) ans = max(ans, dp[i] = max(dp[i], dp[j] + 1));
        }
    }
    return ans;
}

// Operation:
    cin >> n;
    vector<int64_t> v(n); for (i = 0; i < n; ++i) { cin >> v[i]; }
    cout << lis(v);

// Recursive Approach:

int aa[N], dp[N];
int lis(int i) {
    if (dp[i] != -1) return dp[i];
    int ans = 1;
    for (int j = 0; j < i; ++j) {
        if (aa[i] > aa[j]) ans = max(ans, lis(j) + 1);
    }
    return dp[i] = ans;
}

// Operation:
    cin >> n; for (i = 0; i < n; ++i) cin >> aa[i];
    memset(dp, -1, sizeof dp);
    int ans = 0;
    for (i = 0; i < n; ++i) ans = max(ans, lis(i));
    cout << ans;

// To determine the subsequence:

int aa[N], dp[N], in = 0; vector<int> sub;
int lis(auto i) {
    if (dp[i] != -1) return dp[i];
    int ans = 1; bool ok = true;
    for (int j = 0; j < i; ++j) {
        if (aa[i] >= aa[j]) {
            ans = max(ans, lis(j) + 1);
            if (ok) {
                sub.emplace_back(aa[i]);
                in = i; ok = false;
            }
        }
    }
    return dp[i] = ans;
}

// Operation:
    cin >> n; for (i = 0; i < n; ++i) cin >> aa[i];
    memset(dp, -1, sizeof dp);
    for (i = 0; i < n; ++i) lis(i);
    for (i = 0; i < in; ++i) {
        if (aa[i] <= aa[in]) {
            sub.emplace_back(aa[i]); break;
        }
    }
    cout << sub.size() << '\n';
    for (i = sub.size() - 1; i >= 0; --i) cout << sub[i] << ' ';
    // reverse(sub.begin(), sub.end());
    // for (auto &e : sub) cout << e << ' ';