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

void test(int tc) {
    cout << "Case #" << tc << ": ";
    ll n = 0, m = 0, a = 0, b = 0, c = M, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n;
    vector<pair<long double,long double>> ar(n); for (i = 0; i < n; ++i) {
        cin >> ar[i].first >> ar[i].second;
        // if (ar[i].second - ar[i].first < c) {
        //     c = ar[i].second - ar[i].first;
        //     a = ar[i].first, b = ar[i].second;
        //     d = i + 1;
        // }
    }
    long double lo = ar[n-1].first, hi = ar[n-1].second ans = -1;
    while(hi - lo > 1e-6) {
        long double mid = (lo + hi) / 2, tmp = (1.0 * n) / mid;
        for (i = 0; i < n; ++i) {
            if()
        }
    }
    cout << fixed << setprecision(6) << ans << '\n';
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    #ifndef ONLINE_JUDGE
    freopen("subsonic_subway_validation_input.txt", "r", stdin); freopen("out1", "w", stdout);
    #endif
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}