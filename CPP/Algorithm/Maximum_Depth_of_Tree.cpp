// Comlexity: O(v)

vector<int> tre[N]; long long dep[N];
void dfs(int vr, int par = -1) {
    for (auto child : tre[vr]) {
        if (child == par) continue;
        dep[child] = dep[vr] + 1;
        dfs(child, vr);
    }
}

// Taking input:
    int vr; cin >> vr;
    for (i = 0; i < vr - 1; ++i) {
        int v1, v2; cin >> v1 >> v2;
        tre[v1].push_back(v2); tre[v2].push_back(v1);
    }

// Operation:
    int mxnd = max_element(begin(dep), end(dep)) - begin(dep);
    dfs(mxnd);
    cout << *max_element(begin(dep), end(dep));