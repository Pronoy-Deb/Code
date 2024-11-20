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
    cin >> n; bool ok = 1, ck = 0;
    vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; ok &= ar[i] == i + 1; ck |= ar[i] == i + 1; }
    if (ok) {
        cout << n << '\n'; return;
    }
    if (ck) {
        cout << n-1 << '\n'; return;
    }
    cout << n-2 << '\n';
    // for (i=0;i<n;++i) {
    //     c = max(c, min(i, ar[i]-1) + min((n - i - 1), (n - ar[i])));
    // }
    // cout << max(0ll, c-1) << '\n';
    // sort(ar1.begin(), ar1.end() - 1);
    // for (i=0;i<n;++i) {
    //     c += ar[i] == i + 1;
    // }
    // sort(ar.begin(), ar.end());
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}