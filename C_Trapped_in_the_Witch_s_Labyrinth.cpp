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
const ll M = 1e9 + 7, N = 1e3 + 5;

int n, m, dp[N][N]; string ar[N];
bool rec(int i, int j) {
    if (i < 0 or i == n or j < 0 or j == m) return 1;
    auto &ret = dp[i][j];
    if (~ret) return ret;
    ret = 0;
    if (ar[i][j] == 'U') ret = rec(i - 1, j);
    else if (ar[i][j] == 'D') ret = rec(i + 1, j);
    else if (ar[i][j] == 'L') ret = rec(i, j - 1);
    else if (ar[i][j] == 'R') ret = rec(i, j + 1);
    else ret = (rec(i - 1, j) && rec(i + 1, j) && rec(i, j - 1) && rec(i, j + 1));
    return ret;
}

void test(int32_t tc) {
    ll nn = 0, mm = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> m;
    for (i = 0; i < n; ++i) {
        cin >> ar[i];
        for (j=0;j<m;++j) dp[i][j] = -1;
    }
    for (i=0;i<n;++i) {
        for (j=0;j<m;++j) rec(i, j);
    }
    for(i=0;i<n;++i) {
        for (j=0;j<m;++j) {
            // cout << dp[i][j] << ' ';
            c += (dp[i][j] == 0);
        }
        // cout << endl;
    }
    cout << c;
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}