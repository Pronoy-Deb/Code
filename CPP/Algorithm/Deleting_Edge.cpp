// Complexity:
// Work: Divides the tree into two parts so that product of the summation of the trees be maximum

vector<int64_t> tre[N]; int64_t ssum[N];
auto dfs(auto vr, auto par = 0) {
    ssum[vr] += vr;
    for (auto &child : tre[vr]) {
        if (child == par) continue;
        dfs(child, vr);
        ssum[vr] += ssum[child];
    }
}

// Operation:
    int64_t vr; cin >> vr;
    for (i = 0; i < vr - 1; ++i) {
        int64_t v1, v2; cin >> v1 >> v2;
        tre[v1].emplace_back(v2); tre[v2].emplace_back(v1);
    }
    dfs(rt); int64_t ans = 0;
    for (i = 2; i <= vr; ++i) {
        int64_t part1 = ssum[i], part2 = ssum[1] - part1;
        ans = max(ans, (part1 * part2) % M);
    }
    cout << ans;