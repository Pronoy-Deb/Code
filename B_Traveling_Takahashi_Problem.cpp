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

// long long sr(long double x) {
// 	long double p = sqrtl(0.5 + x); while (p * p < x) ++p;
// 	while (p * p > x) --p; return p;
// }

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n;
    // vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    long double px = 0, py = 0, ans = 0;
    while(n--) {
        long double x, y; cin >> x >> y;
        long double xx = (px - x) * (px - x), yy = (py - y) * (py - y);
        long double tem = sqrtl(xx + yy);
        ans += tem;
        px = x; py = y;
    }
    ans += sqrtl(px * px + py * py);
    cout << fixed << setprecision(20) << ans << '\n';
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}