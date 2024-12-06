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

vector<pair<long long, long long>> nd, gp[N];
long long heavy[N], sub[N], chain[N], pa[N], head[N], costre[N], dep[N], tre[N << 2], pos[N], ar[N], n;
inline long long op(long long l, long long r) { return max(l, r); }
void make(int c = 1, int s = 1, int e = n) {
    if (s >= e) { if (s == e) tre[c] = ar[s]; return; }
    int m = (s + e) >> 1, l = c << 1, r = l | 1;
    make(l, s, m); make(r, m + 1, e); tre[c] = op(tre[l], tre[r]);
}
void up(int x, long long val, int c = 1, int b = 1, int e = n) {
	if (b == e) { tre[c] = val; return; }
	int m = (b + e) >> 1, l = c << 1, r = l | 1;
	if (x <= m) up(x, val, l, b, m); else up(x, val, r, m + 1, e);
	tre[c] = op(tre[l], tre[r]);
}
long long get(int x, int y, int c = 1, int b = 1, int e = n) {
	if (x <= b and e <= y) return tre[c];
	if (y < b or e < x) return 0;
	int m = (b + e) >> 1, l = c << 1, r = l | 1;
	return op(get(x, y, l, b, m), get(x, y, r, m + 1, e));
}
void dfs(int x = 1, int par = 1) {
	pa[x] = par; heavy[x] = -1; sub[x] = 1;
	for (int j = 0, sz = gp[x].size(); j < sz; ++j) {
		auto k = gp[x][j]; int i = k.first;
		if (i == par) continue;
		costre[i] = k.second; dep[i] = 1 + dep[x];
		dfs(i, x); sub[x] += sub[i];
		if (heavy[x] == -1 || sub[heavy[x]] < sub[i]) heavy[x] = i;
	}
}
void pre() {
	dfs(); int num = 0, posi = 0;
	for (int i = 1; i <= n; ++i) {
		if (pa[i] == -1 or heavy[pa[i]] != i) {
			++num;
			for (int k = i; k != -1; k = heavy[k]) {
				pos[k] = ++posi; up(pos[k], costre[k]);
				chain[k] = num; head[k] = i;
			}
		}
		if (i != n && pa[nd[i].first] == nd[i].second) swap(nd[i].first, nd[i].second);
	}
}
long long path(int u, int v) {
	long long ans = 0;
	while (chain[u] != chain[v]) {
		if (dep[head[u]] > dep[head[v]]) swap(u, v);
		ans = op(ans, get(pos[head[v]], pos[v]));
		v = pa[head[v]];
	}
	if (dep[u] > dep[v]) swap(u, v);
	if (dep[heavy[u]] <= dep[v]) ans = op(ans, get(pos[heavy[u]], pos[v]));
	return ans;
}
void reset() {
	for (int i = 0; i <= n; ++i) {
		gp[i].clear(); tre[i] = tre[i + n] = tre[i + (n << 1)] = tre[i + (3 * n)] = heavy[i] = sub[i] = chain[i] = pa[i] = head[i] = costre[i] = dep[i] = pos[i] = 0;
	}
	nd.clear();
}
void test(int tc) {
	ll nn = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
	cin >> n >> q;
    for (i = 1; i <= n; ++i) { cin >> ar[i]; }
	nd.push_back({-1, -1});
	for (i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		gp[u].push_back({v, ar[i]}); gp[v].push_back({u, ar[i]});
		nd.push_back({u, v});
	}
	// make();
    pre();
	while (q--) {
		int x, y; cin >> c >> x >> y;
		if (c == 2) cout << path(x, y) << ' ';
		else up(pos[nd[x].second], y);
	}
    cout << '\n';
}

signed main() {
	cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
	int tc = 0, tt = 1;
	// cin >> tt;
	while (tc++ < tt) test(tc);
	return 0;
}