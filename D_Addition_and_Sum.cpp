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
long long pro[N], bit[N]; set<int> ind;
void up(int i, long long mul, long long add) {
    while (i < N) {
        // ind.insert(i);
        pro[i] += mul; bit[i] += add; i |= (i + 1);
    }
}
void add(int l, int r, long long val) {
    up(l, val, -val * (l - 1)); up(r, -val, val * r);
}
long long get(int i) {
    long long mul = 0, add = 0, st = i;
    while (i >= 0) {
        mul += pro[i]; add += bit[i]; i = (i & (i + 1)) - 1;
    }
    return (mul * st + add);
}
long long get(int l, int r) { return get(r) - get(--l); }
void reset() { for (auto &i : ind) pro[i] = bit[i] = 0; ind.clear(); }

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> q;
    // vector<ll> v(n); for (i = 0; i < n; ++i) { cin >> v[i]; }
    while(q--) {
        cin >> d;
        if(d&1) {
            cin >> a >> b >> c;
            add(a, --b, c);
        }
        else {
            cin >> a >> b;
            cout << get(a, --b);
            cout << '\n';
        }
    }
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}