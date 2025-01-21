https://codeforces.com/gym/100551/problem/A

struct pdsu {
    struct state {
        int u, v, rnku, rnkv;
        state() { u = v = rnkv = rnku = -1; }
        state(int _u, int _rnku, int _v, int _rnkv) {
            u = _u; rnku = _rnku; v = _v; rnkv = _rnkv;
        }
    };
    stack<state> sk; vector<int> par, dep; int comp;
    void init(int n) {
        comp = n; dep.assign(n + 1, 1);
        par.resize(n + 1); iota(par.begin(), par.end(), 0);
    }
    inline int root(int x) { if (x == par[x]) return x; return root(par[x]); }
    inline bool same(int x, int y) { return root(x) == root(y); }
    void uni(int x, int y) {
        int rx = root(x), ry = root(y);
        if (rx == ry) { sk.push(state()); return; }
        if (dep[rx] < dep[ry]) par[rx] = ry;
        else if (dep[ry] < dep[rx]) par[ry] = rx;
        else { par[rx] = ry; ++dep[rx]; }
        --comp; sk.push(state(rx, dep[rx], ry, dep[ry]));
    }
    void backtrack(int c) { // how many last added edges to remove
        while (!sk.empty() && c) {
            if (sk.top().u == -1) { sk.pop(); --c; continue; }
            par[sk.top().u] = sk.top().u;
            par[sk.top().v] = sk.top().v;
            dep[sk.top().u] = sk.top().rnku;
            dep[sk.top().v] = sk.top().rnkv;
            sk.pop(); --c; ++comp;
        }
    }
} d;
vector<pair<int, int>> alive[N << 2];
void up(int n, int b, int e, int i, int j, auto &p) {
    if (b > j || e < i) return;
    if (b >= i && e <= j) { alive[n].push_back(p); return; }
    int l = (n << 1), r = l | 1, m = (b + e) >> 1;
    up(l, b, m, i, j, p); up(r, m + 1, e, i, j, p);
}
int cc[N];
void cal(int n, int b, int e) {
    if (b > e) return; int prevsz = d.sk.size();
    for (auto [f, s] : alive[n]) d.uni(f, s);
    if (b == e) {
        cc[b] = d.comp; d.backtrack(d.sk.size() - prevsz); return;
    }
    int l = (n << 1), r = l | 1, m = (b + e) >> 1;
    cal(l, b, m); cal(r, m + 1, e); d.backtrack(d.sk.size() - prevsz);
}
struct hs {
    size_t operator()(const pair<int64_t, int64_t> &x) const {
        return hash<int64_t>()((x.first ^ x.second) << 32);
    }
};

// Operation:
    int n, m; cin >> n >> m; d.init(n);
    set<pair<int, int>> st; bool isquery[m + 1]{};
    unordered_map<pair<int, int>, int, hs> mp;
    for (int i = 1; i <= m; ++i) {
        char t; cin >> t;
        if (t == '?') isquery[i] = 1;
        else if (t == '+') {
            int u, v; cin >> u >> v; if (u > v) swap(u, v);
            pair<int, int> p = {u, v}; st.insert(p); mp[p] = i;
        }
        else {
            int u, v; cin >> u >> v; if (u > v) swap(u, v);
            pair<int, int> p = {u, v}; st.erase(p);
            up(1, 1, m, mp[p], i - 1, p); // in this time range this edge was in the DSU
        }
    }
    for (auto p : st) up(1, 1, m, mp[p], m, p); cal(1, 1, m);
    for (int i = 1; i <= m; ++i) {
        if (isquery[i]) cout << cc[i] << '\n';
    }