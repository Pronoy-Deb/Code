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
const ll M = 1e9 + 7, N = 2e5 + 5;

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> a >> b;
    // vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    if (n == 1) {
        cout << (b > 0) << '\n'; return;
    }
    if(b >= n) {
        cout << n << '\n';
        return;
    }
    c = a + b;
    // d = c - b;
    if (b == 0 and c == 0) {
        if (n == 2) cout << 1;
        else cout << -1;
        cout << '\n';
        return;
    }
    if (a == 0) {
        if(b >= n-2) cout << n - 1; else cout << -1;
        cout << '\n';
        return;
    }
    cout << n - ((n - b) / a + bool((n - b) % a)) << '\n';
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}