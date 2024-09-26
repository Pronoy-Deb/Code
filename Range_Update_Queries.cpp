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
template <class T>
struct BIT { // 1-indexed
int n; vector<T> t;
BIT() {}
BIT(int _n) {
    n = _n; t.assign(n + 5, 0);
}
void up(int i, T val) {
    if (i <= 0) return;
    for (++i; i < n; i += (i & -i)) t[i] += val;
}
void up(int l, int r, T val) {
    up(l, val); up(r + 1, -val);
}
T get(int i) {
    T ans = 0;
    for (++i; i > 0; i -= i & -i) ans += t[i];
    return ans;
}
T get(int l, int r) { return get(r) - get(l - 1); }
};
void test(int tc) {
    ll a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, m = 0, n = 0, q = 0;
    cin >> n >> q;
    vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    BIT<ll> bit(n);
    for (i = 1; i <= n; ++i) {
        bit.up(i, ar[i - 1]);
    }
    while (q--) {
        ll ty; cin >> ty;
        if (ty == 1) {
            cin >> a >> b >> c;
            bit.up(a, b, c);
        }
        else {
            cin >> a;
            cout << bit.get(a) << '\n';
        }
    }
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}