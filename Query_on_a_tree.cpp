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
const ll M = 1e9 + 7, N = 1e4 + 5;

vector<int> gp[N];
int sz[N], P[N], dep[N], tre[N << 1], id[N], tp[N], val[N], n;
inline int op(int l, int r) { return max(l, r); }
void up(int in, int val) {
    for (tre[in += n] = val; in > 1; in >>= 1) tre[in >> 1] = op(tre[in], tre[in ^ 1]);
}
int get(int l, int r) {
    int res = 0;
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
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
	up(id[cur], val[cur]); int h_chi = -1, h_sz = -1;
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
int path(int u, int v) {
	int ret = 0;
	while (tp[u] != tp[v]) {
		if (dep[tp[u]] < dep[tp[v]]) swap(u, v);
		ret = op(ret, get(id[tp[u]], id[u])); u = P[tp[u]];
	}
	if (dep[u] > dep[v]) swap(u, v);
    // if (u != v) ret = op(ret, get(id[u] + 1, id[v])); // for edge query
    ret = op(ret, get(id[u], id[v])); // for node query
	return ret;
}
void reset() {
    for (int i = 1; i <= n; ++i) {
        sz[i] = dep[i] = tp[i] = tre[i] = tre[i + n] = 0; gp[i].clear();
    }
    ct = 0;
}

void test(int tc) {
    ll o = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n;
	for (i = 2; i <= n; ++i) {
        int u, v, wt; cin >> u >> v >> wt; val[i] = wt;
		gp[u].push_back(v); gp[v].push_back(u);
	}
	dfs_sz(); dfs_hld();
	while (1) {
        string tp; cin >> tp;
        if (tp == "DONE") return;
		if (tp == "CHANGE") {
			int s, x; cin >> s >> x; ++s;
			val[s] = x; up(id[s], val[s]);
		}
        else {
            int u, v; cin >> u >> v;
			cout << path(u, v) << '\n';
		}
	}
    reset();
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}