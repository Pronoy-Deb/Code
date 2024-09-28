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

long long pro[N], sum[N];
void up(int i, long long mul, long long add) {
    while (i < N) {
        pro[i] += mul; sum[i] += add; i |= (i + 1);
    }
}
void add(int l, int r, long long val) {
    up(l, val, -val * (l - 1)); up(r, -val, val * r);
}
long long get(int i) {
    long long mul = 0, add = 0, st = i;
    while (i >= 0) {
        mul += pro[i]; add += sum[i]; i = (i & (i + 1)) - 1;
    }
    return (mul * st + add);
}
long long get(int l, int r) { return get(r) - get(--l); }


void test(int tc) {
    ll a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, m = 0, n = 0, q = 0;
    cin >> n >> q;
    vector<ll> ar(n);
    for (i = 0; i < n; ++i) {
        cin >> ar[i]; add(i, i, ar[i]);
    }
    while(q--) {
        cin >> c;
        if(c & 1) {
            cin >> a >> b >> k; add(a - 1, b - 1, k);
        }
        else {
            cin >> a; cout << get(a - 1, a - 1) << '\n';
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