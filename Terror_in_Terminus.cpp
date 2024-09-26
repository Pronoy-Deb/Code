#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int K = 18;
vector<int> g[N]; int anc[N][K], lvl[N];
void dfs(int u, int par = 0) {
    lvl[u] = lvl[par] + 1; anc[u][0] = par;
    for (int k = 1; k < K; ++k) anc[u][k] = anc[anc[u][k - 1]][k - 1];
    for (auto &v : g[u]) {
        if (v == par) continue; dfs(v, u);
    }
}
int lca(int u, int v) {
    if (lvl[u] > lvl[v]) swap(u, v);
    for (int k = K - 1; k >= 0; --k)
        if (lvl[u] + (1ll << k) <= lvl[v]) v = anc[v][k];
    if (u == v) return u;
    for (int k = K - 1; k >= 0; --k) {
        if (anc[u][k] != anc[v][k]) u = anc[u][k], v = anc[v][k];
    }
    return anc[u][0];
}
int dis(int u, int v) {
    int g = lca(u, v);
    return lvl[u] + lvl[v] - (lvl[g] << 1);
}

// void dfs(int u, int p = 0) {
//     par[u][0] = p; dep[u] = dep[p] + 1; sz[u] = 1;
//     for (int i = 1; i <= LG; ++i) par[u][i] = par[par[u][i - 1]][i - 1];
//     for (auto &v : g[u]) {
//         if (v != p) {
//             dfs(v, u); sz[u] += sz[v];
//         }
//     }
// }
// int lca(int u, int v) {
//     if (dep[u] < dep[v]) swap(u, v);
//     for (int k = LG; k >= 0; --k) if (dep[par[u][k]] >= dep[v]) u = par[u][k];
//     if (u == v) return u;
//     for (int k = LG; k >= 0; --k) if (par[u][k] != par[v][k]) u = par[u][k], v = par[v][k];
//     return par[u][0];
// }
int kth(int u, int k) {
    // assert(k >= 0);
    for (int i = 0; i <= K; ++i) if (k & (1 << i)) u = anc[u][i];
    return u;
}
// int dis(int u, int v) {
//     int l = lca(u, v); return dep[u] + dep[v] - (dep[l] << 1);
// }
// kth node from u to v, 0th node is u
int go(int u, int v, int k) {
    int l = lca(u, v), d = lvl[u] + lvl[v] - (lvl[l] << 1);
    // assert(k <= d);
    if (lvl[l] + k <= lvl[u]) return kth(u, k);
    k -= lvl[u] - lvl[l];
    return kth(v, lvl[v] - lvl[l] - k);
}
void reset(int n) {
    for (int i = 0; i <= n+2; ++i) {
        g[i].clear();
        lvl[i] = 0;
        for (int j = 0; j <= K; ++j) {
            anc[i][j] = 0;
        }
    }
}
int32_t main()
{
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        for (int i = 1; i < n; i++)
        {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(1);
        int q;
        cin >> q;
        while (q--)
        {
            int u, v;
            cin >> u >> v;
            int d = dis(u, v);
            // cerr << d << endl;
            cout << go(u, v, d/2) << '\n';
        }
        reset(n);
    }
    return 0;
}