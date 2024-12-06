// Complexity: O(logn) per query (1 based index)
https://cses.fi/problemset/task/1138/

vector<int> gp[N];
long long sz[N], P[N], dep[N], tre[N << 1], id[N], tp[N], val[N], n;
inline long long op(long long l, long long r) { return (l + r); }
void up(int in, long long val) {
    for (tre[in += n] = val; in > 1; in >>= 1) tre[in >> 1] = op(tre[in], tre[in ^ 1]);
}
long long get(int l, int r) {
    long long res = 0;
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = op(res, tre[l++]); if (r & 1) res = op(res, tre[--r]);
    }
    return res;
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
			cout << path(u, v) << '\n';
		}
	}

// OR,

vector<int> gp[N];
long long sz[N], P[N], dep[N], tre[N << 1], lz[N], id[N], tp[N], val[N], n;
inline long long op(long long l, long long r) { return (l + r); }
inline void apply(int in, long long val, int k) {
    tre[in] += val * k; if (in < n) lz[in] += val;
}
void push(int l, int r) {
    int s = (sizeof(int) << 3) - __builtin_clz(n), k = 1 << (s - 1);
    for (l += n, r += n - 1; s > 0; --s, k >>= 1) {
        for (int i = l >> s; i <= r >> s; ++i) {
            if (lz[i]) {
                apply(i << 1, lz[i], k); apply(i << 1 | 1, lz[i], k); lz[i] = 0;
            }
        }
    }
}
void rebuild(int l, int r) {
    int k = 2;
    for (l += n, r += n - 1; l > 1; k <<= 1) {
        l >>= 1, r >>= 1;
        for (int i = r; i >= l; --i) tre[i] = op(tre[i << 1], tre[i << 1 | 1]) + lz[i] * k;
    }
}
void add(int l, int r, long long val) {
    push(l, l + 1); push(r, ++r); int l0 = l, r0 = r, k = 1;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1) {
        if (l & 1) apply(l++, val, k); if (r & 1) apply(--r, val, k);
    }
    rebuild(l0, l0 + 1); rebuild(r0 - 1, r0);
}
long long get(int l, int r) {
    push(l, l + 1); push(r, ++r); long long res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = op(res, tre[l++]); if (r & 1) res = op(res, tre[--r]);
    }
    return res;
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
	add(id[cur], id[cur], val[cur] - get(id[cur], id[cur]));
    int h_chi = -1, h_sz = -1;
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
			long long s, x; cin >> s >> x; val[s] = x;
            add(id[s], id[s], val[s] - get(id[s], id[s]));
		}
        else {
            int u = 1, v; cin >> v;
			cout << path(u, v) << '\n';
		}
	}
}

// OR,

vector<int> gp[N];
long long dep[N], par[N], pos[N], val[N], head[N], heavy[N], cnt;
inline long long op(long long l, long long r) { return (l + r); }
struct ST {
    vector<long long> tre, lz;
    ST() {};
    ST(int n) {
        tre.resize(n << 2, 0); lz.resize(n << 2, 0);
    }
    void propagate(int u, int st, int en) {
        if (!lz[u]) return; tre[u] = lz[u];
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
        tre[u] = op(tre[lc], tre[rc]);
    }
    long long get(int u, int st, int en, int l, int r) {
        propagate(u, st, en); if (r < st || en < l) return 0;
        if (l <= st && en <= r) return tre[u];
        int mid = (st + en) >> 1, lc = u << 1, rc = lc | 1;
        return op(get(lc, st, mid, l, r), get(rc, mid + 1, en, l, r));
    }
} t;
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
        ret = op(ret, t.get(1, 1, cnt, pos[head[v]], pos[v]));
    }
    if (dep[u] > dep[v]) swap(u, v);
    // if (u != v) ret = op(ret, t.get(1, 1, cnt, pos[u] + 1, pos[v])); // for edge query
    ret = op(ret, t.get(1, 1, cnt, pos[u], pos[v])); // for node query
    return ret;
}
void up(int u, int v, long long x) {
    for (; head[u] != head[v]; v = par[head[v]]) {
        if (dep[head[u]] > dep[head[v]]) swap(u, v);
        t.up(1, 1, cnt, pos[head[v]], pos[v], x);
    }
    if (dep[u] > dep[v]) swap(u, v);
    // if (u != v) up(1, 1, cnt, pos[u] + 1, pos[v], x); // update on edge
    t.up(1, 1, cnt, pos[u], pos[v], x); // update on node
}
void make(int n, int root = 1) {
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
    make(n); t = ST(n);
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
void up(int in, long long val) {
    for (tre[in += n] = val; in > 1; in >>= 1) tre[in >> 1] = op(tre[in], tre[in ^ 1]);
}
long long get(int l, int r) {
    long long res = 0;
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = op(res, tre[l++]); if (r & 1) res = op(res, tre[--r]);
    }
    return res;
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
    // if (u != v) ret = op(ret, get(id[u] + 1, id[v])); // for edge query
    ret = op(ret, get(id[u], id[v])); // for node query
	return ret;
}
void reset() {
    for (int i = 1; i <= n; ++i) {
        sz[i] = dep[i] = tp[i] = tre[i] = tre[i + n] = 0; gp[i].clear();
    }
    ct = 0;
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

// OR,

vector<int> gp[N];
long long dep[N], par[N], pos[N], val[N], head[N], heavy[N], tre[N << 2], lz[N << 2], C;
inline long long op(long long l, long long r) { return max(l, r); }
void up(int in, long long val, int nd = 1, int s = 1, int e = C) {
    if (s == e) { tre[nd] = val; return; }
    int m = (s + e) >> 1, lc = nd << 1, rc = lc | 1;
    if (in <= m) up(in, val, lc, s, m); else up(in, val, rc, m + 1, e);
    tre[nd] = op(tre[lc], tre[rc]);
}
long long get(int l, int r, int nd = 1, int s = 1, int e = C) {
    if (s > e || s > r || e < l) return 0;
    if (s >= l && e <= r) return tre[nd];
    int m = (s + e) >> 1, lc = nd << 1, rc = lc | 1;
    return op(get(l, r, lc, s, m), get(l, r, rc, m + 1, e));
}
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
    head[u] = h, pos[u] = ++C;
    if (heavy[u] != -1) dcom(heavy[u], h);
    for (auto &v : gp[u]) {
        if (v == par[u]) continue;
        if (heavy[u] != v) dcom(v, v);
    }
}
void make(int n, int root = 1) {
    for (int i = 1; i <= n; ++i) heavy[i] = -1;
    C = 0; dfs(root, 0); dcom(root, root);
}
long long path(int u, int v) {
    long long ret = 0;
    for (; head[u] != head[v]; v = par[head[v]]) {
        if (dep[head[u]] > dep[head[v]]) swap(u, v);
        ret = op(ret, get(pos[head[v]], pos[v]));
    }
    if (dep[u] > dep[v]) swap(u, v);
    // if (u != v) ret = op(ret, get(pos[u] + 1, pos[v])); // for edge query
    ret = op(ret, get(pos[u], pos[v])); // for node query
    return ret;
}

// Operation:
    cin >> n >> q;
    for (i = 1; i <= n; ++i) cin >> val[i];
    for (i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        gp[u].push_back(v); gp[v].push_back(u);
    }
    make(n); for (i = 1; i <= n; ++i) up(pos[i], val[i]);
    while (q--) {
        int tp; cin >> tp;
        if (tp == 1) {
            long long s, x; cin >> s >> x; up(pos[s], x);
        }
        else {
            int u, v; cin >> u >> v; cout << path(u, v) << ' ';
        }
    }
    // for (i = 1; i <= n; ++i) gp[i].clear();

https://www.spoj.com/problems/QTREE/

vector<pair<long long, long long>> nd, gp[N];
long long heavy[N], sub[N], chain[N], pa[N], head[N], costre[N], dep[N], tre[N << 2], pos[N], n;
inline long long op(long long l, long long r) { return max(l, r); }
void up(int x, long long val, int c = 1, int b = 1, int e = n) {
	if (b == e) { tre[c] = val; return; }
	int m = (b + e) >> 1, l = c << 1, r = l | 1;
	if (x <= m) up(x, val, l, b, m); else up(x, val, r, m + 1, e);
	tre[c] = op(tre[l], tre[r]);
}
long long get(int x, int y, int c = 1, int b = 1, int e = n) {
	if (x <= b and e <= y) return tre[c];
	if (y < b or e < x) return 0;
	int m = (b + e) >> 1, l = c << 1, r = l | 1;
	return op(get(x, y, l, b, m), get(x, y, r, m + 1, e));
}
void dfs(int x, int par) {
	pa[x] = par; heavy[x] = -1; sub[x] = 1;
	for (int j = 0, sz = gp[x].size(); j < sz; ++j) {
		auto k = gp[x][j]; int i = k.first;
		if (i == par) continue;
		costre[i] = k.second; dep[i] = 1 + dep[x];
		dfs(i, x); sub[x] += sub[i];
		if (heavy[x] == -1 || sub[heavy[x]] < sub[i]) heavy[x] = i;
	}
}
void pre() {
	dfs(1, 1); int num = 0, posi = 1;
	for (int i = 1; i <= n; ++i) {
		if (pa[i] == -1 or heavy[pa[i]] != i) {
			++num;
			for (int k = i; k != -1; k = heavy[k]) {
				pos[k] = posi++; up(pos[k], costre[k]);
				chain[k] = num; head[k] = i;
			}
		}
		if (i != n && pa[nd[i].first] == nd[i].second) swap(nd[i].first, nd[i].second);
	}
}
long long path(int u, int v) {
	long long ans = 0;
	while (chain[u] != chain[v]) {
		if (dep[head[u]] > dep[head[v]]) swap(u, v);
		ans = op(ans, get(pos[head[v]], pos[v]));
		v = pa[head[v]];
	}
	if (dep[u] > dep[v]) swap(u, v);
	if (dep[heavy[u]] <= dep[v]) ans = op(ans, get(pos[heavy[u]], pos[v]));
	return ans;
}
void reset() {
	for (int i = 0; i <= n; ++i) {
		gp[i].clear(); tre[i] = tre[i + n] = tre[i + (n << 1)] = tre[i + (3 * n)] = heavy[i] = sub[i] = chain[i] = pa[i] = head[i] = costre[i] = dep[i] = pos[i] = 0;
	}
	nd.clear();
}

// Operation:
	cin >> n;
	nd.push_back({-1, -1});
	for (i = 1; i < n; ++i) {
		int u, v; long long w; cin >> u >> v >> w;
		gp[u].push_back({v, w}); gp[v].push_back({u, w});
		nd.push_back({u, v});
	}
	pre();
	while (1) {
		string s; cin >> s;
		if (s[0] == 'D') break;
		int x, y; cin >> x >> y;
		if (s[0] == 'Q') cout << path(x, y) << '\n';
		else up(pos[nd[x].second], y);
	}
	reset();

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