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

vector<int> g[N]; int sz[N];
void dfs(int u = 1, int p = 0) {
	sz[u] = 1;
	for (auto v : g[u]) {
		if (v ^ p) {
			dfs(v, u); sz[u] += sz[v];
		}
	}
}
vector<int> cen(int n) {
	dfs(); int u = 1;
	while (1) {
		int tmp = -1;
		for (auto v : g[u]) {
			if (sz[v] > sz[u]) continue;
			if ((sz[v] << 1) >= n) tmp = v;
		}
		if (tmp == -1) break; u = tmp;
	}
	dfs(u);
	for (auto v : g[u]) {
		if ((sz[v] << 1) == n) return {u, v};
	}
	return {u};
}
void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n;
    // vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    for (i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        g[u].push_back(v); g[v].push_back(u);
    }
    auto v = cen(n);
    cout << v.front();
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}