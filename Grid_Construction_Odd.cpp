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
    ll n; cin >> n;
    // vector<ll> ar(n); for (int i = 0; i < n; ++i) { cin >> ar[i]; }
    int ar[n][n];
    if (n & 1) {
        int c = (n + 1) >> 1;
        for (int i = 0; i < n; ++i) ar[i][i] = c;
        for (int i = 0; i < n; ++i) {
            --c; if (c == 0) c = n; int a = c;
            for (int j = 0; j < n; ++j) {
                ++a; if (a == n + 1) a = 1;
                if (i == j) continue;
                ar[i][j] = a;
            }
        }
    }
    else {
        int c = (n >> 1);
        for (int i = 0; i < n; ++i) ar[i][i] = c;
        for (int i = 0; i < n; ++i) {
            --c; if (c == 0) c = n; int a = c;
            for (int j = 0; j < n; ++j) {
                ++a; if (a == n + 1) a = 1;
                if (i == j) continue;
                ar[i][j] = a;
            }
        }
        for (int i = 0; i < n; ++i) {
            ar[i][n - i - 1] = c;
            --c; if (c == 0) c = n;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) cout << ar[i][j] << ' ';
        cout << '\n';
    }
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}