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

long long tre[N << 2], lz[N << 2], ar[N], n;
inline long long op(long long l, long long r) { return (l + r); }
void make(int nd = 1, int s = 0, int e = n - 1) {
    if (s >= e) { if (s == e) tre[nd] = ar[s]; return; }
    int m = (s + e) >> 1, lc = nd << 1, rc = lc | 1;
    make(lc, s, m); make(rc, m + 1, e); tre[nd] = op(tre[lc], tre[rc]);
}
void up(int in, long long val, int nd = 1, int s = 0, int e = n - 1) {
    if (s == e) { tre[nd] = val; return; }
    int m = (s + e) >> 1, lc = nd << 1, rc = lc | 1;
    if (in <= m) up(in, val, lc, s, m); else up(in, val, rc, m + 1, e);
    tre[nd] = op(tre[lc], tre[rc]);
}
long long get(int l, int r, int nd = 1, int s = 0, int e = n - 1) {
    if (s > e || s > r || e < l) return 0;
    if (s >= l && e <= r) return tre[nd];
    int m = (s + e) >> 1, lc = nd << 1, rc = lc | 1;
    return op(get(l, r, lc, s, m), get(l, r, rc, m + 1, e));
}

void test(int tc) {
    ll o = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> q;
    for (i = 0; i < n; ++i) { cin >> ar[i]; }
    make();
    while (q--) {
        int tp; cin >> tp;
        if (tp == 1) {
            long long s, x; cin >> s >> x;
            up(--s, x);
        } else {
            int u, v; cin >> u >> v;
            cout << get(--u, --v) << '\n';
        }
    }
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}