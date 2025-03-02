// Complexity:
// Work: Sums up and Count the value of vertices

vector<int64_t> tre[N]; int64_t ssum[N], sevn[N];
auto dfs(auto ver, auto par = 0) {
    if (~ver & 1) ++sevn[ver];
    ssum[ver] += ver;
    for (auto &child : tre[ver]) {
        if (child == par) continue;
        dfs(child, ver);
        ssum[ver] += ssum[child];
        sevn[ver] += sevn[child];
    }
}

// Operation:
    int vr; cin >> vr;
    for (i = 0; i < vr - 1; ++i) {
        int v1, v2; cin >> v1 >> v2;
        tre[v1].emplace_back(v2); tre[v2].emplace_back(v1);
    }
    dfs(rt);
    for (i = 1; i <= vr; ++i) cout << ssum[i] << ' ' << sevn[i] << '\n';