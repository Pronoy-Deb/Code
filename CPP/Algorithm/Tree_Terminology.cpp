// Complexity: O(n)

vector<long long> tre[N]; long long par[N], lvl[N], streSz[N];
auto dfs(auto u, auto p) {
    par[u] = p; streSz[u] = 1;
    for (auto &v : tre[u]) {
        if (v != p) {
            lvl[v] = lvl[u] + 1;
            dfs(v, u); streSz[u] += streSz[v];
        }
    }
}

// Operation:
    int eg; cin >> eg;
    for (i = 0; i < eg - 1; ++i) {
        int u, v; cin >> u >> v;
        tre[u].push_back(v); tre[v].push_back(u);
    }
    lvl[1] = 0; dfs(1, -1);
    for (i = 1; i <= eg; ++i) {
        cout << i << ' ' << par[i] << ' ' << lvl[i] << ' ' << streSz[i] << '\n';
    }