// Complexity:
// Work: Divides the tree into two parts so that product of the summation of the trees be maximum

vector<long long> tre[N]; long long ssum[N];
auto dfs(auto vr, auto par = 0) {
    ssum[vr] += vr;
    for (auto &child : tre[vr]) {
        if (child == par) continue;
        dfs(child, vr);
        ssum[vr] += ssum[child];
    }
}

// Operation:
    long long vr; cin >> vr;
    for (i = 0; i < vr - 1; ++i) {
        long long v1, v2; cin >> v1 >> v2;
        tre[v1].emplace_back(v2); tre[v2].emplace_back(v1);
    }
    dfs(rt); long long ans = 0;
    for (i = 2; i <= vr; ++i) {
        long long part1 = ssum[i], part2 = ssum[1] - part1;
        ans = max(ans, (part1 * part2) % M);
    }
    cout << ans;