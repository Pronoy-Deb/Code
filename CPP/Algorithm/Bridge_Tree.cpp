/*
 * It could be a forest rather than a single tree.
 * The 'tree' holds the bridge trees' edges
 * 'ptr' = the number of new nodes in the bridge tree
 * solves : LightOj 1291
 */

vector<in64_t> g[N], tre[N];
in64_t in[N], low[N], ptr, compID[N];
void go(in64_t u, in64_t par = -1) {
    in[u] = low[u] = ++ptr;
    for (auto &v : g[u]) {
        if (in[v]) {
            if (v == par) par = -1;
            else low[u] = min(low[u], in[v]);
        }
        else {
            go(v, u); low[u] = min(low[u], low[v]);
        }
    }
}
void shrink(in64_t u, in64_t id) {
    compID[u] = id;
    for (auto &v : g[u]) {
        if (!compID[v]) {
            if (low[v] > in[u]) {
                tre[id].emplace_back(++ptr);
                tre[ptr].emplace_back(id);
                shrink(v, ptr);
            }
            else shrink(v, id);
        }
    }
}

// Operation:
    cin >> n >> m;
    for (i = 1; i <= n; ++i) {
        g[i].clear(), tre[i].clear();
        in[i] = 0, compID[i] = 0, low[i] = 0;
    }
    while (m--) {
        in64_t u, v; cin >> u >> v; u++, v++;
        g[u].emplace_back(v); g[v].emplace_back(u);
    }
    for (i = 1; i <= n; ++i) if (!in[i]) go(i);
    ptr = 0;
    for (i = 1; i <= n; ++i) {
        if (!compID[i]) shrink(i, ++ptr);
    }
    in64_t ans = 0;
    for (i = 1; i <= ptr; ++i) ans += (tre[i].size() == 1);
    cout << ((ans + 1) >> 1);

// OR,
// Finding Bridge:

in64_t dt[N], low[N], Time; vector<in64_t> adj[N];
vector<pair<in64_t, in64_t>> bridges;
void bridge(in64_t u, in64_t p) {
    low[u] = dt[u] = ++Time;
    for (auto &v : adj[u]) {
        if (v == p) continue;
        if (dt[v]) low[u] = min(low[u], dt[v]);
        else {
            bridge(v, u);
            if (dt[u] < low[v]) bridges.push_back(pii(u, v));
            low[u] = min(low[u], low[v]);
        }
    }
}