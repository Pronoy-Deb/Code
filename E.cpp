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
const ll M = 1e9 + 4, N = 2e5 + 5;
long double sr(long double n) {
    long double lo = 1, hi = n;
    while (hi - lo > 1e-6) {
        long double mid = (lo + hi) / 2.0;
        if (mid * mid < n) lo = mid;
        else hi = mid;
    }
    return lo;
}
void test(int tc) {
    // ll p = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    while(1) {
        long double n;
        cin >> n;
        
    }
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}