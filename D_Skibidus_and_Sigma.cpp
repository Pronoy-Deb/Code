#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const int64_t M = 1e9 + 7, N = 2e5 + 5;

void test(int32_t tc) {
    int64_t n, m; cin >> n >> m;
    int64_t aa[n][m];
    vector<pair<int64_t, int>> sum(n);
    for (int i = 0; i < n; ++i) {
        int64_t tot = 0;
        for (int j = 0; j < m; ++j) {
            cin >> aa[i][j]; tot += aa[i][j];
        }
        sum[i] = {tot, i};
    }
    sort(sum.begin(), sum.end(), greater<>());
    int i = 0; vector<int64_t> ans;
    while (i < n) {
        vector<vector<int64_t>> v;
        while (i < n - 1 and sum[i].first == sum[i + 1].first) {
            vector<int64_t> tmp;
            for (auto e : aa[sum[i].second]) {
                tmp.push_back(e);
            }
            v.push_back(tmp);
            i++;
        }
        vector<int64_t> tmp;
        for (auto e : aa[sum[i].second]) {
            tmp.push_back(e);
        }
        v.push_back(tmp);
        sort(v.begin(), v.end(), greater<>());
        for (auto &x : v) {
            for (auto &y : x) {
                // cout << y << ' ';
                ans.push_back(y);
            }
            // cout << '\n';
        }
        ++i;
    }
    // for (auto &x : ans) {
    //     cout << x << ' ';
    // }
    int64_t res = ans[0], pre = ans[0];
    for (int i = 1; i < n * m; ++i) {
        pre += ans[i]; res += pre;
    }
    cout << res;
    cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}