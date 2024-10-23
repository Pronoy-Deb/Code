#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ll long long
#define pe(c) for (auto &e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const ll M = 1e9 + 7, N = 1e6 + 5;

ll ar[105], dp[N], n, x;
long long coin(int i, int tot) {
    if (i >= n) return 0;
    if (tot == 0) return 1;
    auto &ans = dp[tot];
    if (~ans) return ans;
    ans = 0;
    for (int j = 0; j <= x; ++j) {
        if (j >= ar[i]) {
            ans += coin(i, j - ar[i]);
            ans %= M;
            ans += coin(i + 1, j);
            ans %= M;
        }
    }
    return ans;
}

void test(int tc) {
    ll o = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> x;
    for (i = 0; i < n; ++i) {
        cin >> ar[i];
    }
    memset(dp, -1, sizeof dp);
    cout << coin(0, x);
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}