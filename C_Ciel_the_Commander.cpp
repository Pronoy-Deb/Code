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
const ll M = 1e9 + 7, N = 1e5 + 5;

vector<int> gp[N]; bitset<N> vis; int sz[N], cPar[N], dep[N], siz;
void subSize(int u, int p) {
    ++siz; sz[u] = 1;
    for (auto v : gp[u]) {
        if (v == p || vis[v]) continue; subSize(v, u); sz[u] += sz[v];
    }
}
int centroid(int u, int p) {
    for (auto v : gp[u]) {
        if (v == p || vis[v]) continue;
        if (sz[v] > (siz >> 1)) return centroid(v, u);
    }
    return u;
}
void dcom(int u = 1, int p = 0) {
    siz = 0; subSize(u, p); int c = centroid(u, p); cPar[c] = p; vis[c] = 1;
    for (auto v : gp[c]) {
        if (v == p || vis[v]) continue; dcom(v, c);
    }
}
void dfs(int u, int p = 0) {
    for (auto v : gp[u]) {
        if (v == p) continue; dep[v] = dep[u] + 1; dfs(v, u);
    }
}

void test(int32_t tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n;
    for (i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        gp[u].push_back(v); gp[v].push_back(u);
    }
    dcom();
    for (i = 1; i <= n; ++i) gp[i].clear();
    int rt = 1;
    for (i = 1; i <= n; ++i) {
        gp[cPar[i]].push_back(i); gp[i].push_back(cPar[i]);
        if (cPar[i] == 0) rt = i;
    }
    dfs(rt);
    for (i = 1; i <= n; ++i) cout << char(dep[i] + 'A') << ' ';
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}