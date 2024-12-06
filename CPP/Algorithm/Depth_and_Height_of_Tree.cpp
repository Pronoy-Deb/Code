// Complexity:
// Note: For Tree -> No of Edges = No of Vertices - 1

vector<int> tre[N]; int dep[N], hit[N];
void dfs(int vr, int par = 0) {
    for (auto &child : tre[vr]) {
        if (child == par) continue;
        dep[child] = dep[vr] + 1;
        dfs(child, vr);
        hit[vr] = max(hit[vr], hit[child] + 1);
    }
}

// Operation:
    int vr; cin >> vr;
    for (i = 0; i < vr - 1; ++i) {
        int v1, v2; cin >> v1 >> v2;
        tre[v1].emplace_back(v2); tre[v2].emplace_back(v1);
    }
    dfs(root);
    for (i = 1; i <= vr; ++i) cout << dep[i] << ' ' << hit[i] << '\n';