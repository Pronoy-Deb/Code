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

vector<int> gp[N], ord; bitset<N> vis;
void dfs(int u) {
    vis[u] = true;
    for (auto v : gp[u]) { if (!vis[v]) dfs(v); }
    ord.push_back(u);
}

void test(int32_t tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> m;
    while (m--) {
        int u, v; cin >> u >> v; gp[u].push_back(v);
    }
    for (i = 1; i <= n; ++i) { if (!vis[i]) dfs(i); }
    reverse(ord.begin(), ord.end()); int pos[n + 5];
    for (i = 0, d = ord.size(); i < d; ++i) pos[ord[i]] = i;
    for (int u = 1; u <= n; ++u) {
        for (auto v : gp[u]) {
            if (pos[u] >= pos[v]) {
                cout << "IMPOSSIBLE\n"; return;
            }
        }
    }
    for (auto u : ord) cout << u << ' ';
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}