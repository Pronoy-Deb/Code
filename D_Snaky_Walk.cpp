#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ll long long
#define pe(c) for (auto e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const ll M = 1e9 + 7, N = 1e3 + 5;

string ar[N]; int a, b, c, d, n, m; bool ok = 0;
ll dp[N][N][3]; bitset<N> vis[N];
ll rec(int i, int j, int st = 2) {
    if (i < 0 || j < 0 || i >= n || j >= m || ar[i][j] == '#' || (ar[i][j] == 'S' && st != 2) || vis[i][j]) return M*M;
    if (i == c && j == d) { ok = 1; return 0; }
    ll &ans = dp[i][j][st];
    if (ans != -1) return ans;
    vis[i][j] = 1; ans = M*M;
    if (st == 2) {
        ans = min(ans, 1 + rec(i + 1, j, 0));
        ans = min(ans, 1 + rec(i - 1, j, 0));
        ans = min(ans, 1 + rec(i, j + 1, 1));
        ans = min(ans, 1 + rec(i, j - 1, 1));
    }
    else {
        if (st) {
            ans = min(ans, 1 + rec(i + 1, j, 0));
            ans = min(ans, 1 + rec(i - 1, j, 0));
        }
        else {
            ans = min(ans, 1 + rec(i, j + 1, 1));
            ans = min(ans, 1 + rec(i, j - 1, 1));
        }
    }
    vis[i][j] = 0;
    return ans;
}
void test(int32_t tc) {
    cin >> n >> m;
    // vector<ll> ar(n); for (int i = 0; i < n; ++i) { cin >> ar[i]; }
    for (int i = 0; i < n; ++i) {
        cin >> ar[i];
        for (int j = 0; j < m; ++j) {
            if (ar[i][j] == 'S') {
                a = i; b = j;
            }
            else if (ar[i][j] == 'G') {
                c = i; d = j;
            }
        }
    }
    memset(dp, -1, sizeof dp);
    ll ans = rec(a, b);
    if (!ok) cout << "-1\n";
    else cout << ans << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}