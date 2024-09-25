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
long long tsum[N << 2], tmax[N << 2], ar[N], n;
void com(int nd, int lc, int rc) {
    tsum[nd] = tsum[lc] + tsum[rc];
    tmax[nd] = max(tmax[lc], tmax[rc]);
}
void make(int nd = 0, int s = 0, int e = n - 1) {
    if (s >= e) {
        if (s == e) tsum[nd] = tmax[nd] = ar[s]; return;
    }
    int m = (s + e) >> 1, lc = (nd << 1) + 1, rc = lc + 1;
    make(lc, s, m); make(rc, m + 1, e); com(nd, lc, rc);
}
void mod(int l, int r, int x, int nd = 0, int s = 0, int e = n - 1) {
	if (r < s || e < l || tmax[nd] < x) return;
    else if (s == e) {
		tsum[nd] = tmax[nd] = tmax[nd] % x; return;
	}
	int m = (s + e) >> 1, lc = (nd << 1) + 1, rc = lc + 1;
	mod(l, r, x, lc, s, m); mod(l, r, x, rc, m + 1, e); com(nd, lc, rc);
}
void up(int i, int v, int nd = 0, int s = 0, int e = n - 1) {
	if (s == e) {
		tsum[nd] = tmax[nd] = v; return;
	}
	int m = (s + e) >> 1, lc = (nd << 1) + 1, rc = lc + 1;
	if (i <= m) up(i, v, lc, s, m); else up(i, v, rc, m + 1, e); com(nd, lc, rc);
}
long long get(int l, int r, int nd = 0, int s = 0, int e = n - 1) {
	if (r < s || e < l) return 0;
    else if (l <= s && e <= r) return tsum[nd];
	int m = (s + e) >> 1, lc = (nd << 1) + 1, rc = lc + 1;
	return get(l, r, lc, s, m) + get(l, r, rc, m + 1, e);
}
void test(int tc) {
    ll a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, m = 0, q = 0;
    cin >> n >> q;
	for (i = 0; i < n; ++i) cin >> ar[i];
    make();
    while (q--) {
		int t; cin >> t;
		if (t == 1) {
            cin >> a >> b; cout << get(--a, --b) << '\n';
		}
        else if (t == 2) {
            cin >> a >> b >> c; mod(--a, --b, c);
		}
        else {
			cin >> i >> a; up(--i, a);
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