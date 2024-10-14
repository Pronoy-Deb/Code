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
    cin >> n >> m; int ar[n];
    for (i = 0; i < n; ++i) { cin >> ar[i]; }
    auto ok = [&](ll x) {
        ll cnt = 0;
        for (i = 0; i < n; ++i) {
            cnt += x / ar[i];
            if (cnt >= m) return true;
        }
        return false;
    };
    function<ll(ll, ll)> bs = [&](ll l, ll r) {
        if (l == r) return l;
        ll mid = (l + r) >> 1;
        if (ok(mid)) return bs(l, mid);
        return bs(mid + 1, r);
    };
    cout << bs(1, 1e18) << '\n';
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}