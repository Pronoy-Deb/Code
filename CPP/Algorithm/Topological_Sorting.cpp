https://cses.fi/problemset/task/1679

vector<int> gp[N], ord; bitset<N> vis;
void dfs(int u) {
    vis[u] = true;
    for (auto v : gp[u]) { if (!vis[v]) dfs(v); }
    ord.push_back(u);
}

// Operation:
    cin >> n >> m;
    while (m--) {
        int u, v; cin >> u >> v; gp[u].push_back(v);
    }
    for (int i = 1; i <= n; ++i) { if (!vis[i]) dfs(i); }
    reverse(ord.begin(), ord.end()); int pos[n + 5];
    for (int i = 0, d = ord.size(); i < d; ++i) pos[ord[i]] = i;
    for (int u = 1; u <= n; ++u) {
        for (auto v : gp[u]) {
            if (pos[u] >= pos[v]) {
                cout << "IMPOSSIBLE\n"; return;
            }
        }
    }
    for (auto u : ord) cout << u << ' ';