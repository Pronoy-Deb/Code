#define log __lg
#define ctz __builtin_ctz

// Rooted tree
struct arborescence {
    vector<vector<int64_t>> children;
    int64_t rt;
};

arborescence sdt(vector<vector<int64_t>> &gp, auto rt = 0) {
    int n = gp.size();
    vector<vector<int64_t>> decomposition_tree(n), stacks(log(n) + 1);
    auto extract_chain = [&](int64_t labels, int64_t u) {
        while (labels) {
            int label = log(labels); labels ^= 1ll << label;
            int64_t v = stacks[label].back(); stacks[label].pop_back();
            decomposition_tree[u].push_back(v); u = v;
        }
    };
    vector<int64_t> forbidden(n, -1);
    auto dfs = [&](int64_t u, int64_t p, auto&& self) -> void {
        int64_t forbidden_once = 0, forbidden_twice = 0;
        for (auto &v : gp[u]) {
            if (v != p) {
                self(v, u, self);
                forbidden_twice |= forbidden_once & (forbidden[v] + 1);
                forbidden_once |= forbidden[v] + 1;
            }
        }
        forbidden[u] = forbidden_once | ((1ll << log((forbidden_twice << 1)  + 1)) - 1);
        int64_t label_u = ctz(forbidden[u] + 1);
        stacks[label_u].push_back(u);
        for (int i = gp[u].size() - 1; i >= 0; --i) {
            extract_chain((forbidden[gp[u][i]] + 1) & ((1ll << label_u) - 1), u);
        }
    };
    dfs(rt, -1, dfs);
    int64_t max_label = log(forbidden[rt] + 1), drt = stacks[max_label].back();
    stacks[max_label].pop_back();
    extract_chain((forbidden[rt] + 1) & ((1ll << max_label) - 1), drt);
    return {move(decomposition_tree), drt};
}