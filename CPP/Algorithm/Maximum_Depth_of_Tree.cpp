// Comlexity: O(v)

vector<long long> tre[N]; long long dep[N];
void dfs(auto vr, auto par = -1) {
    for (auto &child : tre[vr]) {
        if(child == par) continue;
        dep[child] = dep[vr] + 1;
        dfs(child, vr);
    }
}

// Taking input:
    long long vr; cin >> vr;
    for (i = 0; i < vr - 1; ++i) {
        long long v1, v2; cin >> v1 >> v2;
        tre[v1].emplace_back(v2); tre[v2].emplace_back(v1);
    }

// Calling: dfs(root);
// Operation:
    int mxnd = max_element(begin(dep), end(dep)) - begin(dep);
    dfs(mxnd);
    cout << *max_element(begin(dep), end(dep));