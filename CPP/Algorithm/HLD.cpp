// Complexity: O(logn) per get

vector<int> gp[N];
long long dep[N], par[N], pos[N], val[N], head[N], heavy[N], cnt, n;
long long combine(long long l, long long r) { return max(l, r); }
struct ST {
    vector<long long> tre, lz;
    ST() {};
    ST(long long sz) {
        n = sz; tre.resize(n << 2, 0); lz.resize(n << 2, 0);
    }
    void propagate(int u, int st, int en) {
        if (!lz[u]) return;
        tre[u] = lz[u];
        if (st != en) {
            lz[(lc)] = lz[u]; lz[rc] = lz[u];
        }
        lz[u] = 0;
    }
    void up(int u, int st, int en, int l, int r, long long x) {
        propagate(u, st, en);
        if (r < st || en < l) return;
        if (l <= st && en <= r) {
            lz[u] += x; propagate(u, st, en); return;
        }
        int mid = (st + en) >> 1, lc = u << 1, rc = lc + 1;
        up(lc, st, mid, l, r, x); up(rc, mid + 1, en, l, r, x);
        tre[u] = combine(tre[lc], tre[rc]);
    }
    long long get(int u, int st, int en, int l, int r) {
        propagate(u, st, en);
        if (r < st || en < l) return 0;
        if (l <= st && en <= r) return tre[u];
        int mid = (st + en) >> 1, lc = u << 1, rc = lc + 1;
        return combine(get(lc, st, mid, l, r), get(rc, mid + 1, en, l, r));
    }
} tree;
long long dfs(int u, int p) {
    long long sz = 1, mxsz = 0;
    dep[u] = dep[p] + 1;
    for (auto &v : gp[u]) {
        if (v == p) continue; par[v] = u;
        long long subsz = dfs(v, u);
        if (subsz > mxsz) heavy[u] = v, mxsz = subsz;
        sz += subsz;
    }
    return sz;
}
void dcom(int u, int h) {
    head[u] = h, pos[u] = ++cnt;
    if (heavy[u] != -1) dcom(heavy[u], h);
    for (auto &v : gp[u]) {
        if (v == par[u]) continue;
        if (heavy[u] != v) dcom(v, v);
    }
}
long long get(long long u, long long v) {
    long long ret = 0;
    for (; head[u] != head[v]; v = par[head[v]]) {
        if (dep[head[u]] > dep[head[v]]) swap(u, v);
        ret = max(ret, tree.get(1, 1, cnt, pos[head[v]], pos[v]));
    }
    if (dep[u] > dep[v]) swap(u, v);
    // for edge query
    // if (u != v) ret = combine(ret, get(1, 1, cnt, pos[u] + 1, pos[v]));
    // for node query
    ret = combine(ret, tree.get(1, 1, cnt, pos[u], pos[v]));
    return ret;
}
void up(int u, int v, long long x) {
    for (; head[u] != head[v]; v = par[head[v]]) {
        if (dep[head[u]] > dep[head[v]]) swap(u, v);
        tree.up(1, 1, cnt, pos[head[v]], pos[v], x);
    }
    if (dep[u] > dep[v]) swap(u, v);
    /*update on edge
      if (u != v) up(1, 1, cnt, pos[u] + 1, pos[v], x); */
    // update on node
    tree.up(1, 1, cnt, pos[u], pos[v], x);
}
void pre(int root = 1) {
    for (int i = 1; i <= n; ++i) heavy[i] = -1;
    cnt = 0, dfs(root, 0); dcom(root, root);
}

// Operation:
    cin >> n >> q;
    for (i = 1; i <= n; ++i) cin >> val[i];
    for (i = 1; i < n; ++i) {
        int u, v;  cin >> u >> v;
        gp[u].push_back(v); gp[v].push_back(u);
    }
    pre(); // decomsing tree
    tree = ST(n);
    for (i = 1; i <= n; ++i) up(i, i, val[i]);
    while (q--) {
        int tp; cin >> tp;
        if (tp == 1) {
            long long s, x; cin >> s >> x; up(s, s, x);
        }
        else {
            int u, v; cin >> u >> v;
            cout << get(u, v) << " ";
        }
    }
    for (i = 1; i <= n; ++i) gp[i].clear();

// OR,

const int N = 1e5 + 9, LG = 18, inf = 1e9 + 9;

struct ST {
    #define lc (n << 1)
    #define rc ((n << 1) | 1)
    int tre[(N << 2)], lz[(N << 2)];
    ST() {
        fill(tre, tre + (N << 2), -inf); fill(lz, lz + (N << 2), 0);
    }
    inline void push(int n, int b, int e) {
        if (lz[n] == 0) return;
        tre[n] = tre[n] + lz[n];
        if (b != e) {
            lz[lc] = lz[lc] + lz[n]; lz[rc] = lz[rc] + lz[n];
        }
        lz[n] = 0;
    }
    inline int combine(int a, int b) {
        return max(a, b); // merge left and right queries
    }
    inline void pull(int n) {
        tre[n] = max(tre[lc], tre[rc]); // merge lower nodes of the tree to get the parent node
    }
    void build(int n, int b, int e) {
        if (b == e) {
            tre[n] = 0; return;
        }
        int mid = (b + e) >> 1;
        build(lc, b, mid); build(rc, mid + 1, e); pull(n);
    }
    void up(int n, int b, int e, int i, int j, int v) {
        push(n, b, e); if (j < b || e < i) return;
        if (i <= b && e <= j) {
            lz[n] += v; push(n, b, e); return;
        }
        int mid = (b + e) >> 1;
        up(lc, b, mid, i, j, v); up(rc, mid + 1, e, i, j, v);
        pull(n);
    }
    int get(int n, int b, int e, int i, int j) {
        push(n, b, e); if (i > e || b > j) return -inf;
        if (i <= b && e <= j) return tre[n];
        int mid = (b + e) >> 1;
        return combine(get(lc, b, mid, i, j), get(rc, mid + 1, e, i, j));
    }
} t;

vector<int> g[N]; int par[N][LG + 1], dep[N], sz[N];
void dfs(int u, int p = 0) {
    par[u][0] = p; dep[u] = dep[p] + 1; sz[u] = 1;
    for (int i = 1; i <= LG; ++i) par[u][i] = par[par[u][i - 1]][i - 1];
    if (p) g[u].erase(find(g[u].begin(), g[u].end(), p));
    for (auto &v : g[u]) {
        if (v != p) {
            dfs(v, u); sz[u] += sz[v];
            if (sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
        }
    }
}
int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int k = LG; k >= 0; --k) {
        if (dep[par[u][k]] >= dep[v]) u = par[u][k];
    }
    if (u == v) return u;
    for (int k = LG; k >= 0; --k) {
        if (par[u][k] != par[v][k]) u = par[u][k], v = par[v][k];
    }
    return par[u][0];
}
int kth(int u, int k) {
    assert(k >= 0);
    for (int i = 0; i <= LG; ++i) {
        if (k & (1 << i)) u = par[u][i];
    }
    return u;
}
int T, head[N], st[N], en[N];
void dfs_hld(int u) {
    st[u] = ++T;
    for (auto &v : g[u]) {
        head[v] = (v == g[u][0] ? head[u] : v); dfs_hld(v);
    }
    en[u] = T;
}
int n;
int query_up(int u, int v) {
    int ans = -inf;
    while (head[u] != head[v]) {
        ans = max(ans, t.get(1, 1, n, st[head[u]], st[u]));
        u = par[head[u]][0];
    }
    ans = max(ans, t.get(1, 1, n, st[v], st[u]));
    return ans;
}
int get(int u, int v) {
    int l = lca(u, v), ans = query_up(u, l);
    if (v != l) ans = max(ans, query_up(v, kth(v, dep[v] - dep[l] - 1)));
    return ans;
}

// Operation:
    cin >> n;
    for (i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        g[u].push_back(v); g[v].push_back(u);
    }
    dfs(1); head[1] = 1; dfs_hld(1);
    t.build(1, 1, n); cin >> q;
    while (q--) {
        string ty; int u, v;
        cin >> ty >> u >> v;
        if (ty == "add") t.up(1, 1, n, st[u], en[u], v);
        else cout << get(u, v) << '\n';
    }
    
// https://www.hackerrank.com/challenges/subtrees-and-paths/problem