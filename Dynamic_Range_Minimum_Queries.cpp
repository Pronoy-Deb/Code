#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ll long long
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const ll M = 1e9 + 7, N = 2e5 + 5;

long long ar[N], bs, n, ini = M; vector<long long> block;
long long op(long long a, long long b) { return min(a, b); }
void pre() {
    bs = (int)ceil(sqrt(n)); block.assign((n + bs - 1) / bs, ini);
    for (int i = 0; i < n; ++i) block[i / bs] = op(block[i / bs], ar[i]);
}
void up(int in, int val) {
    block[in / bs] = ini; ar[in] = val;
    for (int i = (in / bs) * bs, e = min(n, (in / bs + 1) * bs); i < e; ++i)
        block[in / bs] = op(block[in / bs], ar[i]);
}
long long get(int l, int r) {
    long long sb = l / bs, eb = r / bs, res = ini;
    if (sb == eb) {
        for (int i = l; i <= r; ++i) res = op(res, ar[i]);
    }
    else {
        for (int i = l, e = (sb + 1) * bs; i < e; ++i) res = op(res, ar[i]);
        for (int i = sb + 1; i < eb; ++i) res = op(res, block[i]);
        for (int i = eb * bs; i <= r; ++i) res = op(res, ar[i]);
    }
    return res;
}

void test(int tc) {
    ll o = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> q;
    // vector<ll> ar(n);
    for (i = 0; i < n; ++i) {
        cin >> ar[i];
    }
    pre();
    while (q--) {
        cin >> c >> a >> b;
        if (c == 1)
            up(a - 1, b);
        else cout << get(a - 1, b - 1) << '\n';
    }
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}