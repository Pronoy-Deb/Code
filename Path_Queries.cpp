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
vector<int> gp[N];
long long sz[N], P[N], dep[N], tre[N << 1], lz[N], id[N], tp[N], val[N], n;
inline long long op(long long l, long long r) { return (l + r); }
void apply(int in, long long val, int k) {
    tre[in] += val * k; if (in < n) lz[in] += val;
}
void push(int l, int r) {
    int s = (sizeof(int) << 3) - __builtin_clz(n), k = 1 << (s - 1);
    for (l += n, r += n - 1; s > 0; --s, k >>= 1) {
        for (int i = l >> s; i <= r >> s; ++i) {
            if (lz[i]) {
                apply(i << 1, lz[i], k); apply(i << 1 | 1, lz[i], k); lz[i] = 0;
            }
        }
    }
}
void rebuild(int l, int r) {
    int k = 2;
    for (l += n, r += n - 1; l > 1; k <<= 1) {
        l >>= 1, r >>= 1;
        for (int i = r; i >= l; --i) tre[i] = op(tre[i << 1], tre[i << 1 | 1]) + lz[i] * k;
    }
}
void add(int l, int r, long long val) {
    push(l, l + 1); push(r, ++r); int l0 = l, r0 = r, k = 1;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1) {
        if (l & 1) apply(l++, val, k); if (r & 1) apply(--r, val, k);
    }
    rebuild(l0, l0 + 1); rebuild(r0 - 1, r0);
}
long long get(int l, int r) {
    push(l, l + 1); push(r, ++r); long long res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = op(res, tre[l++]); if (r & 1) res = op(res, tre[--r]);
    }
    return res;
}
int dfs_sz(int cur = 1, int par = 1) {
	sz[cur] = 1; P[cur] = par;
	for (auto &chi : gp[cur]) {
		if (chi == par) continue; dep[chi] = dep[cur] + 1;
		P[chi] = cur; sz[cur] += dfs_sz(chi, cur);
	}
	return sz[cur];
}
int ct = 0;
void dfs_hld(int cur = 1, int par = 1, int top = 1) {
	id[cur] = ++ct; tp[cur] = top;
	add(id[cur], id[cur], val[cur] - get(id[cur], id[cur]));
    int h_chi = -1, h_sz = -1;
	for (auto &chi : gp[cur]) {
		if (chi == par) continue;
		if (sz[chi] > h_sz) {
			h_sz = sz[chi]; h_chi = chi;
		}
	}
	if (h_chi == -1) return; dfs_hld(h_chi, cur, top);
	for (auto &chi : gp[cur]) {
		if (chi == par || chi == h_chi) continue;
		dfs_hld(chi, cur, chi);
	}
}
long long path(int x, int y) {
	long long ret = 0;
	while (tp[x] != tp[y]) {
		if (dep[tp[x]] < dep[tp[y]]) swap(x, y);
		ret = op(ret, get(id[tp[x]], id[x])); x = P[tp[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	return op(ret, get(id[x], id[y]));
}

void test(int tc) {
    ll o = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> q;
	for (i = 1; i <= n; ++i) cin >> val[i];
	for (i = 2; i <= n; ++i) {
        int u, v; cin >> u >> v;
		gp[u].push_back(v); gp[v].push_back(u);
	}
	dfs_sz(); dfs_hld();
	while (q--) {
        int tp; cin >> tp;
		if (tp == 1) {
			long long s, x; cin >> s >> x; val[s] = x;
            add(id[s], id[s], val[s] - get(id[s], id[s]));
		}
        else {
            int u = 1, v; cin >> v;
			cout << path(u, v) << ' ';
            cout << '\n';
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