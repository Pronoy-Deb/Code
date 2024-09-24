#define log __lg
#define ctz __builtin_ctz

// Rooted tree
struct arborescence {
    vector<vector<long long>> children;
    long long rt;
};

arborescence sdt(vector<vector<long long>> &gp, auto rt = 0) {
    int n = gp.size();
    vector<vector<long long>> decomposition_tree(n), stacks(log(n) + 1);
    auto extract_chain = [&](long long labels, long long u) {
        while (labels) {
            int label = log(labels); labels ^= 1ll << label;
            long long v = stacks[label].back(); stacks[label].pop_back();
            decomposition_tree[u].push_back(v); u = v;
        }
    };
    vector<long long> forbidden(n, -1);
    auto dfs = [&](long long u, long long p, auto&& self) -> void {
        long long forbidden_once = 0, forbidden_twice = 0;
        for (auto &v : gp[u]) {
            if (v != p) {
                self(v, u, self);
                forbidden_twice |= forbidden_once & (forbidden[v] + 1);
                forbidden_once |= forbidden[v] + 1;
            }
        }
        forbidden[u] = forbidden_once | ((1ll << log((forbidden_twice << 1)  + 1)) - 1);
        long long label_u = ctz(forbidden[u] + 1);
        stacks[label_u].push_back(u);
        for (int i = gp[u].size() - 1; i >= 0; --i) {
            extract_chain((forbidden[gp[u][i]] + 1) & ((1ll << label_u) - 1), u);
        }
    };
    dfs(rt, -1, dfs);
    long long max_label = log(forbidden[rt] + 1), drt = stacks[max_label].back();
    stacks[max_label].pop_back();
    extract_chain((forbidden[rt] + 1) & ((1ll << max_label) - 1), drt);
    return {move(decomposition_tree), drt};
}