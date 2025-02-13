#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const int64_t M = 1e9 + 7, N = 2e5 + 5;

int64_t str[N], sf[N], n;
map<pair<int, int>, int64_t> dp;

int64_t rec(int i, int pre) {
    if (i == n - 1) return pre * str[i];
    auto it = dp.find({i, pre});
    if (it != dp.end()) return it->second;
    int64_t ans = M * M;
    ans = min(ans, pre * str[i] + rec(i + 1, sf[i]));
    ans = min(ans, rec(i + 1, pre));
    return dp[{i, pre}] = ans;
}

void test(int32_t tc) {
    int pre; cin >> n >> pre;
    for (int i = 0; i < n; ++i) { cin >> str[i]; }
    for (int i = 0; i < n; ++i) { cin >> sf[i]; }
    cout << rec(0, pre) << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}