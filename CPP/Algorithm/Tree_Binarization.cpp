// Complexity: O(nlogn)

const int N = 2e5 + 9, M = (N << 1) + N * 19 * 2;
vector<pair<int, int>> g[N << 1], G[N];
inline void add(int u, int v, int w) {
    g[u].push_back({v, w});
}
int T;
void binarize(int u, int p = 0) {
    int lst = 0, tmp = 0;
    for (auto &e : G[u]) {
        int v = e.first, w = e.second;
        if (v == p) continue;
        if (++tmp == 1) {
            add(u, v, w); add(v, u, w); lst = u;
        }
        else if (tmp == ((int) G[u].size()) - (u != 1)) {
            add(lst, v, w); add(v, lst, w);
        }
        else {
            add(lst, ++T, 0); add(T, lst, 0);
            lst = T; add(T, v, w); add(v, T, w);
        }
    }
    for (auto &[f, s] : G[u]) {
        if (f == p) continue; binarize(f, u);
    }
}
int sz[N << 1], tot, done[N << 1], cenpar[N << 1];
void calc_sz(int u, int p) {
    ++tot; sz[u] = 1;
    for (auto &[f, s] : g[u]) {
        if (f == p || done[f]) continue;
        calc_sz(f, u); sz[u] += sz[f];
    }
}
int find_cen(int u, int p) {
    for (auto &[f, s]: g[u]) {
        if (f == p || done[f]) continue;
        else if (sz[f] > (tot >> 1)) return find_cen(f, u);
    }
    return u;
}
int64_t d[20][N << 1];
void yo(int u, int p, int64_t nw, int l) {
    d[l][u] = nw;
    for (auto &[f, s] : g[u]) {
        if (f == p || done[f]) continue;
        yo(f, u, nw + s, l);
    }
}
int st[N << 1], en[N << 1], DT;
struct node {
    vector<int> ct; //adjacent edges in centroid tree
    int64_t sum = 0, parsum = 0, level = 0, id = 0, cnt = 0;
}t[M];
int decompose(int u, int p = 0, int l = 0) {
    tot = 0; calc_sz(u, p);
    int cen = find_cen(u, p);
    cenpar[cen] = p; done[cen] = 1;
    u = cen; st[u] = ++DT;
    t[u].id = u; t[u].level = l;
    yo(u, p, 0, l);
    for (auto &[f, s] : g[u]) {
        if (f == p || done[f]) continue;
        int x = decompose(f, u, l + 1);
        t[u].ct.push_back(x);
    }
    en[u] = DT; return u;
}
bool insub(int r, int c) {
    r = t[r].id, c = t[c].id;
    return (st[r] <= st[c] && en[c] <= en[r]);
}
int up(int cur, int u) { //update node u in cur tree
    assert(++T < M);
    t[T] = t[cur]; cur = T; t[cur].cnt++;
    t[cur].sum += d[t[cur].level][u];
    for (auto &v : t[cur].ct) {
        if (insub(v, u)) {
            v = up(v, u); t[v].parsum += d[t[cur].level][u];
        }
    }
    return cur;
}
int64_t query(int cur, int u) { // query on cur tree
    int64_t ans = 0;
    while (t[cur].id != t[u].id) {
        int v = 0;
        for (auto &x : t[cur].ct) if (insub(x, u)) v = x;
        assert(v);
        ans += d[t[cur].level][t[u].id] * (t[cur].cnt - t[v].cnt);
        ans += t[cur].sum - t[v].parsum; cur = v;
    }
    ans += t[cur].sum; return ans;
}
int ar[N], root[N];

// Operation:
    cin >> n >> q;
    for (i = 1; i <= n; ++i) cin >> ar[i];
    for (i = 1; i < n; ++i) {
        int u, v, w; cin >> u >> v >> w;
        G[u].push_back({v, w}); G[v].push_back({u, w});
    }
    T = n; binarize(1); root[0] = decompose(1);
    for (i = 1; i <= n; ++i) root[i] = up(root[i - 1], ar[i]);
    int64_t ans = 0; const int mod = 1 << 30;
    while (q--) {
        int ty; cin >> ty;
        if (ty == 1) {
            int l, r, u; cin >> l >> r >> u;
            l ^= ans; r ^= ans; u ^= ans;
            ans = query(root[r], u) - query(root[l - 1], u);
            cout << ans << '\n'; ans %= mod;
        }
        else {
            int x; cin >> x; x ^= ans;
            root[x] = up(root[x - 1] , ar[x + 1]);
            swap(ar[x], ar[x + 1]);
        }
    }

// Problem: https://codeforces.com/contest/757/problem/G