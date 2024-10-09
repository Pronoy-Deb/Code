#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pe(c)                           \
    for (auto &e : c) cout << e << ' '; \
    cout << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
const ll M = 1e9 + 7, N = 2e6;

void test(int tc) {
    ll n = 0, m = 0, a = -M, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n;
    vector<ll> ar(n);
    for (i = 0; i < n; ++i) {
        cin >> ar[i];
        // a = max(a, ar[i]);
    }
    // a = (2*a + (a % 2));
    cout << N << ' ';
    // cout << a << ' ';
    if (n == 1) {
        return;
    }
    cout << ar[1] << ' ';
    if (n == 2) {
        return;
    }
    c = N + ar[1];
    for (i = 2; i < n; ++i) {
        d = ar[i] + N - c;
        cout << d << ' ';
        c += d;
        // a = max(a, d);
    }
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}