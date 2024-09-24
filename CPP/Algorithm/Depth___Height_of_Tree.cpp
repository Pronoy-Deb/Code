// Complexity: 
// Note: For Tree -> No of Edges = No of Vertices - 1

vector<long long> tre[N]; long long dep[N], hit[N];
void dfs(long long ver, long long par = 0) {
    for (auto &child : tre[ver]) {
        if (child == par) continue;
        dep[child] = dep[ver] + 1;
        dfs(child, ver);
        hit[ver] = max(hit[ver], hit[child] + 1);
    }
}

// Operation:
    long long vr; cin >> vr;
    for (i = 0; i < vr - 1; ++i) {
        long long v1, v2; cin >> v1 >> v2;
        tre[v1].emplace_back(v2); tre[v2].emplace_back(v1);
    }
    dfs(root);
    for (i = 1; i <= vr; ++i) cout << dep[i] << ' ' << hit[i] << '\n';