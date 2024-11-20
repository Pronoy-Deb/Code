// Complexity: O(logn) per query
https://cses.fi/problemset/task/1138/

vector<int> gp[N];
long long sz[N], P[N], dep[N], tre[N << 1], id[N], tp[N], val[N], n;
inline long long op(long long l, long long r) { return (l + r); }
void up(int idx, long long val) {
	tre[idx += n] = val; idx >>= 1;
	while (idx) {
        tre[idx] = op(tre[idx << 1], tre[(idx << 1) | 1]); idx >>= 1;
    }
}
long long get(int lo, int hi) {
	long long ra = 0, rb = 0;
	for (lo += n, hi += n + 1; lo < hi; lo >>= 1, hi >>= 1) {
		if (lo & 1) ra = op(ra, tre[lo++]);
		if (hi & 1) rb = op(rb, tre[--hi]);
	}
	return op(ra, rb);
}
int dfs_sz(int cur = 1, int par = 1) {
	sz[cur] = 1; P[cur] = par;
	for (auto &chi : gp[cur]) {
		if (chi == par) continue; dep[chi] = dep[cur] + 1;
		P[chi] = cur; sz[cur] += dfs_sz(chi, cur);
	}
	return sz[cur];
}
int ct = 0;
void dfs_hld(int cur = 1, int par = 1, int top = 1) {
	id[cur] = ++ct; tp[cur] = top;
	up(id[cur], val[cur]); int h_chi = -1, h_sz = -1;
	for (auto &chi : gp[cur]) {
		if (chi == par) continue;
		if (sz[chi] > h_sz) {
			h_sz = sz[chi]; h_chi = chi;
		}
	}
	if (h_chi == -1) return; dfs_hld(h_chi, cur, top);
	for (auto &chi : gp[cur]) {
		if (chi == par || chi == h_chi) continue;
		dfs_hld(chi, cur, chi);
	}
}
long long path(int x, int y) {
	long long ret = 0;
	while (tp[x] != tp[y]) {
		if (dep[tp[x]] < dep[tp[y]]) swap(x, y);
		ret = op(ret, get(id[tp[x]], id[x])); x = P[tp[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	return op(ret, get(id[x], id[y]));
}

// Operation:
    cin >> n >> q;
	for (i = 1; i <= n; ++i) cin >> val[i];
	for (i = 2; i <= n; ++i) {
        int u, v; cin >> u >> v;
		gp[u].push_back(v); gp[v].push_back(u);
	}
	dfs_sz(); dfs_hld();
	while (q--) {
        int tp; cin >> tp;
		if (tp == 1) {
			long long s, x; cin >> s >> x;
			val[s] = x; up(id[s], val[s]);
		}
        else {
            int u = 1, v; cin >> v;
			cout << path(u, v) << ' ';
            cout << '\n';
		}
	}

// OR,

vector<int> gp[N];
long long dep[N], par[N], pos[N], val[N], head[N], heavy[N], cnt;
inline long long op(long long l, long long r) { return (l + r); }
struct ST {
    vector<long long> stre, lz;
    ST() {};
    ST(int n) {
        stre.resize(n << 2, 0); lz.resize(n << 2, 0);
    }
    void propagate(int u, int st, int en) {
        if (!lz[u]) return; stre[u] = lz[u];
        if (st != en) {
            lz[u << 1] = lz[u]; lz[u << 1 | 1] = lz[u];
        }
        lz[u] = 0;
    }
    void up(int u, int st, int en, int l, int r, long long x) {
        propagate(u, st, en); if (r < st || en < l) return;
        if (l <= st && en <= r) {
            lz[u] += x; propagate(u, st, en); return;
        }
        int mid = (st + en) >> 1, lc = u << 1, rc = lc | 1;
        up(lc, st, mid, l, r, x); up(rc, mid + 1, en, l, r, x);
        stre[u] = op(stre[lc], stre[rc]);
    }
    long long get(int u, int st, int en, int l, int r) {
        propagate(u, st, en); if (r < st || en < l) return 0;
        if (l <= st && en <= r) return stre[u];
        int mid = (st + en) >> 1, lc = u << 1, rc = lc | 1;
        return op(get(lc, st, mid, l, r), get(rc, mid + 1, en, l, r));
    }
} tre;
int dfs(int u, int p) {
    int sz = 1, mxsz = 0; dep[u] = dep[p] + 1;
    for (auto &v : gp[u]) {
        if (v == p) continue; par[v] = u;
        int subsz = dfs(v, u);
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
long long get(int u, int v) {
    long long ret = 0;
    for (; head[u] != head[v]; v = par[head[v]]) {
        if (dep[head[u]] > dep[head[v]]) swap(u, v);
        ret = op(ret, tre.get(1, 1, cnt, pos[head[v]], pos[v]));
    }
    if (dep[u] > dep[v]) swap(u, v);
    // if (u != v) ret = op(ret, get(1, 1, cnt, pos[u] + 1, pos[v])); // for edge query
    ret = op(ret, tre.get(1, 1, cnt, pos[u], pos[v])); // for node query
    return ret;
}
void up(int u, int v, long long x) {
    for (; head[u] != head[v]; v = par[head[v]]) {
        if (dep[head[u]] > dep[head[v]]) swap(u, v);
        tre.up(1, 1, cnt, pos[head[v]], pos[v], x);
    }
    if (dep[u] > dep[v]) swap(u, v);
    // if (u != v) up(1, 1, cnt, pos[u] + 1, pos[v], x); // update on edge
    tre.up(1, 1, cnt, pos[u], pos[v], x); // update on node
}
void pre(int n, int root = 1) {
    for (int i = 1; i <= n; ++i) heavy[i] = -1;
    cnt = 0; dfs(root, 0); dcom(root, root);
}

// Operation:
    cin >> n >> q;
    for (i = 1; i <= n; ++i) cin >> val[i];
    for (i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        gp[u].push_back(v); gp[v].push_back(u);
    }
    pre(n); tre = ST(n);
    for (i = 1; i <= n; ++i) up(i, i, val[i]);
    while (q--) {
        int tp; cin >> tp;
        if (tp == 1) {
            long long s, x; cin >> s >> x; up(s, s, x);
        }
        else {
            int u = 1, v; cin >> v;
            cout << get(u, v) << '\n';
        }
    }
    // for (i = 1; i <= n; ++i) gp[i].clear();

https://cses.fi/problemset/task/2134

vector<int> gp[N];
long long sz[N], P[N], dep[N], tre[N << 1], id[N], tp[N], val[N], n;
inline long long op(long long l, long long r) { return max(l, r); }
void up(int idx, long long val) {
	tre[idx += n] = val; idx >>= 1;
	while (idx) {
        tre[idx] = op(tre[idx << 1], tre[(idx << 1) | 1]); idx >>= 1;
    }
}
long long get(int lo, int hi) {
	long long ra = 0, rb = 0;
	for (lo += n, hi += n + 1; lo < hi; lo >>= 1, hi >>= 1) {
		if (lo & 1) ra = op(ra, tre[lo++]);
		if (hi & 1) rb = op(rb, tre[--hi]);
	}
	return op(ra, rb);
}
int dfs_sz(int cur = 1, int par = 1) {
	sz[cur] = 1; P[cur] = par;
	for (auto &chi : gp[cur]) {
		if (chi == par) continue; dep[chi] = dep[cur] + 1;
		P[chi] = cur; sz[cur] += dfs_sz(chi, cur);
	}
	return sz[cur];
}
int ct = 0;
void dfs_hld(int cur = 1, int par = 1, int top = 1) {
	id[cur] = ++ct; tp[cur] = top;
	up(id[cur], val[cur]); int h_chi = -1, h_sz = -1;
	for (auto &chi : gp[cur]) {
		if (chi == par) continue;
		if (sz[chi] > h_sz) {
			h_sz = sz[chi]; h_chi = chi;
		}
	}
	if (h_chi == -1) return; dfs_hld(h_chi, cur, top);
	for (auto &chi : gp[cur]) {
		if (chi == par || chi == h_chi) continue;
		dfs_hld(chi, cur, chi);
	}
}
long long path(int x, int y) {
	long long ret = 0;
	while (tp[x] != tp[y]) {
		if (dep[tp[x]] < dep[tp[y]]) swap(x, y);
		ret = op(ret, get(id[tp[x]], id[x])); x = P[tp[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	return op(ret, get(id[x], id[y]));
}

// Operation:
    cin >> n >> q;
	for (i = 1; i <= n; ++i) cin >> val[i];
	for (i = 2; i <= n; ++i) {
        int u, v; cin >> u >> v;
		gp[u].push_back(v); gp[v].push_back(u);
	}
	dfs_sz(); dfs_hld();
	while (q--) {
        int tp; cin >> tp;
		if (tp == 1) {
			long long s, x; cin >> s >> x;
			val[s] = x; up(id[s], val[s]);
		}
        else {
            int u, v; cin >> u >> v;
			cout << path(u, v) << ' ';
		}
	}

https://www.hackerrank.op/challenges/subtrees-and-paths/problem

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
    inline int op(int a, int b) {
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
        return op(get(lc, b, mid, i, j), get(rc, mid + 1, e, i, j));
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
int T, head[N], tre[N], en[N];
void dfs_hld(int u) {
    tre[u] = ++T;
    for (auto &v : g[u]) {
        head[v] = (v == g[u][0] ? head[u] : v); dfs_hld(v);
    }
    en[u] = T;
}
int n;
int query_up(int u, int v) {
    int ans = -inf;
    while (head[u] != head[v]) {
        ans = max(ans, t.get(1, 1, n, tre[head[u]], tre[u]));
        u = par[head[u]][0];
    }
    ans = max(ans, t.get(1, 1, n, tre[v], tre[u]));
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
        if (ty == "add") t.up(1, 1, n, tre[u], en[u], v);
        else cout << get(u, v) << '\n';
    }