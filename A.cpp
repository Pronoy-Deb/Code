#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pe(c) for (auto &e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
const ll M = 1e9 + 7, N = 2e5 + 5;
// long long xr(int l, int r) { return xr[r] ^ xr[l - 1]; }
void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n;
    long long xr[n+5], ar[n]; xr[0] = 0;
    for (i = 0; i < n; ++i) { cin >> ar[i]; xr[i + 1] = xr[i] ^ ar[i]; }
    for(i=1;i<n;++i) {
        c += (xr[i] == (xr[n] ^ xr[i]));
    }
    cout << c;
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}