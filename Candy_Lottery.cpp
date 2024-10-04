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
long double bex(long double base, long long pow) {
    long double ans = 1;
    while (pow) {
        if (pow & 1) ans *= base;
        base *= base; pow >>= 1;
    }
    return ans;
}
long double ev(long long n, int k) {
    long double val = 0;
    for (long double i = 1; i <= k; ++i)
        val += i * (bex(i / k, n) - bex((i - 1) / k, n));
    return val;
}
void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> k;
    cout << setprecision(6) << fixed << ev(n, k);
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}