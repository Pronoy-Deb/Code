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
const ll M = 1e9 + 7, N = 2e5 + 5;

void test(int32_t tc) {
    ll n, m; cin >> n >> m;
    // vector<ll> ar(n); for (int i = 0; i < n; ++i) { cin >> ar[i]; }
    string s; cin >> s;
    ll ar[n][m];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) cin >> ar[i][j];
    }
    ll rs[n], cs[m];
    for (int i = 0; i < n; ++i) {
        ll sum = 0;
        for (int j = 0; j < m; ++j) sum += ar[i][j];
        rs[i] = sum;
    }
    for (int i = 0; i < m; ++i) {
        ll sum = 0;
        for (int j = 0; j < n; ++j) sum += ar[j][i];
        cs[i] = sum;
    }
    int in = 0, i = 0, j = 0;
    while (1) {
        if (i == n - 1 and j == m - 1) break;
        if (s[in] == 'R') {
            ar[i][j] = -1 * cs[j]; rs[i] += ar[i][j]; ++j;
        }
        else {
            ar[i][j] = -1 * rs[i]; cs[j] += ar[i][j]; ++i;
        }
        ++in;
    }
    ar[n - 1][m - 1] = -1 * rs[n - 1];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) cout << ar[i][j] << ' ';
        cout << '\n';
    }
    // cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}