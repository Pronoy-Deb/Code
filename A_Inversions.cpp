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
const ll M = 1e9 + 7, N = 1e5 + 5;
long long bit[N], n;
void add(int in, long long val) {
    for (++in; in <= n; in += in & -in) bit[in] += val;
}
void add(int l, int r, long long val) { add(l, val); add(++r, -val); }
long long get(int in) {
    long long tot = 0;
    for (++in; in > 0; in -= in & -in) tot += bit[in];
    return tot;
}
long long get(int l, int r) { return get(r) - get(--l); }
void reset() { for (int i = 0; i <= n; ++i) bit[i] = 0; }
void test(int tc) {
    ll a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, m = 0, q = 0;
    cin >> n;
    vector<ll> ar(n); for (i = 0; i < n; ++i) {
        cin >> ar[i];
        cout << (ar[i] == n ? 0 : get(ar[i], n - 1)) << ' ';
        add(ar[i] - 1, 1);
    }
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}