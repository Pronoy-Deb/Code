// Complexity: O(V + E)

vector<int> gp[N]; int lvl[N]; bool vis[N];
void bfs(auto src) {
    vis[src] = true; queue<int> q; q.emplace(src);
    while (!q.empty()) {
        for (auto &cld : gp[q.front()]) {
            if (!vis[cld]) {
                q.emplace(cld); vis[cld] = true;
                lvl[cld] = lvl[q.front()] + 1;
            }
        }
        q.pop();
    }
}

// Operation:
    int vr; cin >> vr;
    for (i = 0; i < vr - 1; ++i) {
        int v1, v2; cin >> v1 >> v2;
        gp[v1].emplace_back(v2); gp[v2].emplace_back(v1);
    }
    bfs(rt);

// Printing Level:
    for (i = 1; i <= vr; ++i)
        cout << i << " : " << lvl[i] << '\n';

// OR,

int n, m; vector<int> gp[N];
vector<int> bfs(int s) {
    vector<int> d(n, M), Q = {s};
    d[s] = 0; int sz = Q.size();
    for (int i = 0; i < sz; ++i) {
        for (auto &v : gp[Q[i]]) {
            if (d[v] > d[Q[i]] + 1) {
                d[v] = d[Q[i]] + 1; Q.push_back(v);
            }
        }
    }
    return d;
}

// Operation:
    cin >> n >> m;
    for (i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        gp[u].push_back(v); gp[v].push_back(u);
    }
    int src, snk; cin >> src >> snk;
    auto d1 = bfs(src), d2 = bfs(snk);
    int ans = 0;
    for (i = 0; i < n; ++i) {
        ans = max(ans, d1[i] + d2[i]); gp[i].clear();
    }
    cout << ans << '\n';

// OR,

vector<int> gp[N];

// Operation:
    cin >> n >> m;
    for (i = 1; i <= m; ++i) {
        int u, v; cin >> u >> v;
        gp[u].push_back(v); gp[v].push_back(u);
    }
    vector<int> d(n + 1, M), par(n + 1, -1);
    queue<int> q; q.push(1); d[1] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &v : gp[u]) {
            if (d[u] + 1 < d[v]) {
                d[v] = d[u] + 1; par[v] = u; q.push(v);
            }
        }
    }
    if (d[n] == M) {
        cout << "IMPOSSIBLE\n"; return;
    }
    cout << d[n] + 1 << '\n';
    int cur = n; vector<int> path;
    while (cur != -1) {
        path.push_back(cur); cur = par[cur];
    }
    reverse(path.begin(), path.end());
    for (auto &u : path) cout << u << ' ';

// https://cses.fi/problemset/task/1667