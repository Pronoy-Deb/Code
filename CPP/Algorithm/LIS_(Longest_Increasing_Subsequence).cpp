// Note: Gives result of STRICTLY incresing subsequence
// For longest non-decreasing subsequence, replace 'lower_bound' with 'upper_bound' and for longest decreasing subsequence, replace ar[i] *= -1;
// Iterative Approach to determine the length: O(n * log(n))

long long ar[N], n;
int lis() {
    vector<long long> ans; ans.push_back(ar[0]);
    for (int i = 1; i < n; ++i) {
        if (ar[i] > ans.back()) ans.push_back(ar[i]);
        else {
            int low = lower_bound(ans.begin(), ans.end(), ar[i]) - ans.begin();
            ans[low] = ar[i];
        }
    }
    return ans.size();
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
    vector<long long> v(n); for (i = 0; i < n; ++i) { cin >> v[i]; }
    cout << lis(v);

// Recursive Approach:

int ar[N], dp[N];
int lis(int i) {
    if (dp[i] != -1) return dp[i];
    int ans = 1;
    for (int j = 0; j < i; ++j) {
        if (ar[i] > ar[j]) ans = max(ans, lis(j) + 1);
    }
    return dp[i] = ans;
}

// Operation:
    cin >> n; for (i = 0; i < n; ++i) cin >> ar[i];
    memset(dp, -1, sizeof dp);
    int ans = 0;
    for (i = 0; i < n; ++i) ans = max(ans, lis(i));
    cout << ans;

// To determine the subsequence:

int ar[N], dp[N], in = 0; vector<int> sub;
int lis(auto i) {
    if (dp[i] != -1) return dp[i];
    int ans = 1; bool ok = true;
    for (int j = 0; j < i; ++j) {
        if (ar[i] >= ar[j]) {
            ans = max(ans, lis(j) + 1);
            if (ok) {
                sub.emplace_back(ar[i]);
                in = i; ok = false;
            }
        }
    }
    return dp[i] = ans;
}

// Operation:
    cin >> n; for (i = 0; i < n; ++i) cin >> ar[i];
    memset(dp, -1, sizeof dp);
    for (i = 0; i < n; ++i) lis(i);
    for (i = 0; i < in; ++i) {
        if (ar[i] <= ar[in]) {
            sub.emplace_back(ar[i]); break;
        }
    }
    cout << sub.size() << '\n';
    for (i = sub.size() - 1; i >= 0; --i) cout << sub[i] << ' ';
    // reverse(sub.begin(), sub.end());
    // for (auto &e : sub) cout << e << ' ';