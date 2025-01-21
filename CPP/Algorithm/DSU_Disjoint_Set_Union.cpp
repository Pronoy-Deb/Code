// Complexity: O(alpha(n))
https://codeforces.com/contest/1857/problem/G

struct dsu {
    vector<int> par, sz;
    dsu(int n) : par(n + 5), sz(n + 5, 1) {
        iota(par.begin(), par.end(), 0);
    }
    int get(int i) {
        return (par[i] == i ? i : par[i] = get(par[i]));
    }
    void uni(int a, int b) {
        a = get(a); b = get(b);
        if (a != b) {
            if (sz[a] < sz[b]) swap(a, b);
            par[b] = a; sz[a] += sz[b];
        }
    }
    bool same(int a, int b) { return get(a) == get(b); }
    int len(int a) { return sz[get(a)]; }
    int cc(int n) {
        int cc = 0;
        for (int i = 1; i <= n; ++i) {
            if (get(i) == i) ++cc;
        }
        return cc;
    }
};

// Operation: Determining the number of CONNECTED COMPONENTS after performing the union operation:
    int64_t n, k; cin >> n >> k;
    dsu d(n);
    while (k--) {
        int u, v; cin >> u >> v; d.uni(u, v);
    }
    cout << d.cc() << '\n';

// OR,

struct dsu {
    int c; vector<int> par, rnk, sz;
    dsu(int n) : c(n), par(n + 5), rnk(n + 5), sz(n + 5, 1) {
        iota(par.begin(), par.end(), 0);
    }
    int get(int i) {
        return (par[i] == i ? i : (par[i] = get(par[i])));
    }
    bool same(int i, int j) { return get(i) == get(j); }
    int len(int i) { return sz[get(i)]; }
    int cc() { return c; } // connected components
    int uni(int i, int j) {
        if ((i = get(i)) == (j = get(j))) return -1;
        else --c;
        if (rnk[i] > rnk[j]) swap(i, j);
        par[i] = j; sz[j] += sz[i];
        if (rnk[i] == rnk[j]) rnk[j]++;
        return j;
    }
};

// Moving & Erasing Operation with Summation & Length:
https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=0&problem=3138&mosmsg=Submission+received+with+ID+29844967

struct dsu {
    vector<int64_t> sz, tot;
    dsu(int n) : sz((n << 1) + 5), tot((n << 1) + 5) {
        for (int i = 1; i <= n; ++i) { sz[i] = n + i; sz[i + n] = -1; tot[i + n] = i; }
    }
    int get(int x) { return sz[x] < 0 ? x : sz[x] = get(sz[x]); }
    inline bool del(int x) { return sz[x] == -1; }
    void uni(int x, int y) {
        auto X = get(x), Y = get(y); if (del(x) || del(y) || X == Y) return;
        if (sz[X] > sz[Y]) swap(X, Y); sz[X] += sz[Y]; sz[Y] = X; tot[X] += tot[Y];
    }
    void move(int x, int y) { // move x to the set that contains y
        auto X = get(x), Y = get(y); if (del(x) || del(y) || X == Y) return;
        ++sz[X]; --sz[Y]; tot[X] -= x; tot[Y] += x; sz[x] = Y;
    }
    void rem(int x) { if (del(x)) return; ++sz[get(x)]; sz[x] = -1; }
    int len(int x) { return -sz[get(x)]; }
    int64_t sum(int x) { return tot[get(x)]; } // summation of elements in the set containing x
};

// DSU on Tree: O(n*logn)
https://cses.fi/problemset/task/1139

vector<int> gp[N]; map<int, int> fre[N];
int64_t cnt[N], clr[N], sz[N]; bitset<N> big;
void dfs(int u = 1, int p = 1) {
    sz[u] = 1;
    for (auto &v : gp[u]) {
        if (v != p) { dfs(v, u); sz[u] += sz[v]; }
    }
}
void add(int u, int p, int64_t x, auto &freq) {
    freq[clr[u]] += x;
    if (freq[clr[u]] == 0) freq.erase(clr[u]);
    for (auto &v : gp[u]) {
        if (v != p && !big[v]) add(v, u, x, freq);
    }
}
void dsu(int u = 1, int p = 1, bool keep = 1) {
    int bcld = -1, mx = -1;
    for (auto &v : gp[u]) {
        if (v != p and sz[v] > mx) mx = sz[v], bcld = v;
    }
    for (auto &v : gp[u]) {
        if (v != p && v != bcld) dsu(v, u, 0);
    }
    if (~bcld) {
        dsu(bcld, u, 1); big[bcld] = 1; fre[u].swap(fre[bcld]);
    }
    add(u, p, 1, fre[u]); cnt[u] = fre[u].size();
    if (~bcld) big[bcld] = 0; if (!keep) add(u, p, -1, fre[u]);
}

// Operation:
    cin >> n;
    for (i = 1; i <= n; ++i) { cin >> clr[i]; }
    for (i = 1; i < n; ++i) {
        cin >> a >> b; gp[a].push_back(b); gp[b].push_back(a);
    }
    dfs(); dsu();
    for (i = 1; i <= n; ++i) cout << cnt[i] << ' ';

// Augmented DSU / Weighted DSU:
// Application:- used for maintaining a system of equations of the form (y - x = d) along
// with  their consistencial queries dynamically using disjoint set union and get data structure.
// Inspired by the problem http://www.spoj.com/problems/CHAIN/ which utilises this concept, which can extended for solving
https://atcoder.jp/contests/abc328/tasks/abc328_f

int64_t pot[N], par[N], inc; // numbers of inconsistencies
void make(int n) {
    inc = 0;
    for (int i = 1; i <= n; ++i) {
        par[i] = i; pot[i] = 0;
    }
}
int get(int x) {
    if (par[x] == x) return x;
    int rx = get(par[x]); pot[x] = pot[par[x]] + pot[x];
    return par[x] = rx;
}
void uni(int a, int b, int d) {
    int ra = get(a), rb = get(b);
    if (ra == rb && pot[a] - pot[b] != d) ++inc;
    else if (ra != rb) {
        pot[ra] = d + pot[b] - pot[a]; par[ra] = rb;
    }
}
// Operation:
    cin >> n >> m;
    make(n);
    for (i = 1; i <= m; ++i) {
        cin >> a >> b >> d; uni(a, b, d);
    }
    cout << inc;
    // queries of type y - x = ? can be given through pot[y] - pot[x] (only when then are in same component, i.e., can be extracted from the information so far )

// Partially Persistent DSU:
https://cses.fi/problemset/task/2101
https://codeforces.com/gym/100814/problem/C

int par[N], Time[N], sz[N];
void make(int n) {
 	for (int i = 1; i <= n; ++i) {
        par[i] = i; sz[i] = 1;
	}
}
int get(int i) { return (par[i] == i ? i : get(par[i])); }
void uni(int a, int b, int t) {
	a = get(a); b = get(b);
	if (a == b) return;
    if (sz[a] > sz[b]) swap(a, b);
	sz[b] += sz[a]; par[a] = b; Time[a] = t;
}
int time(int a, int b) { // minimum time when a & b are in the same set
    int ans = 0;
    while (a != b) {
        if (par[a] == a && par[b] == b) return -1;
        if (par[a] != a && (Time[a] < Time[b] || par[b] == b)) {
            ans = Time[a]; a = par[a];
        }
        else { ans = Time[b]; b = par[b]; }
    }
    return ans;
}

// Operation:
	cin >> n >> m >> q;
    make(n);
	for (i = 1; i <= m; ++i) {
        cin >> a >> b; uni(a, b, i);
	}
	while (q--) {
        cin >> a >> b;
        cout << time(a, b) << '\n';
	}

// OR,

struct dsu {
vector<vector<pair<int, int>>> par;
int T = 0;
dsu(int n) : par(n + 1, {{-1, 0}}) {}
bool uni(int u, int v) {
    ++T; if ((u = root(u, T)) == (v = root(v, T))) return false;
    if (par[u].back().first > par[v].back().first) swap(u, v);
    par[u].push_back({par[u].back().first + par[v].back().first, T});
    par[v].push_back({u, T}); return true;
}
bool same(int u, int v, int t) { return root(u, t) == root(v, t); }
int root(int u, int t) { // root of u at time t
    if (par[u].back().first >= 0 && par[u].back().second <= t)
        return root(par[u].back().first, t);
    return u;
}
int size(int u, int t) { // size of the component of u at time t
    u = root(u, t);
    int l = 0, r = (int) par[u].size() - 1, ans = 0;
    while (l <= r) {
        int mid = l + r >> 1;
        if (par[u][mid].second <= t) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    return -par[u][ans].first;
}
int time(int u, int v) { // minimum time when u & v are in the same set
    int ans = -1, l = 0, r = T;
    while (l <= r) {
        int mid = l + r >> 1;
        if (same(u, v, mid)) ans = ar[mid], r = mid - 1;
        else l = mid + 1;
    }
    return ans;
}
};

// Operation:
    cin >> n >> m;
    dsu o(n); int ar[n + 1];
    for (i = 1; i <= m; ++i) {
        int ty, u, v; cin >> ty >> u >> v;
        if (ty == 1) {
            o.uni(u, v); ar[o.T] = i;
        }
        else cout << o.time(u, v) << '\n';
    }

// Persistent Union Find:
https://judge.yosupo.jp/problem/persistent_unionfind

template <typename T>
struct PersistentArray { // 0-indexed
    struct node {
        node *l, *r; T x;
    };
    int n = 1; vector<node *> root;
    int make(vector<T> v) {
        int sz = v.size(); while (n < sz) n <<= 1;
        root.push_back(make(0, n - 1, v)); return root.size() - 1;
    }
    node *make(int l, int r, vector<T> &v) {
        node *cur = new node();
        if (l == r) {
            if (l < v.size()) cur->x = v[l]; else cur->x = 0;
        }
        else {
            int lc = (l + r) >> 1, rc = lc + 1;
            cur->l = make(l, lc, v); cur->r = make(rc, r, v);
        }
        return cur;
    }
    // get the ith value of the r-th array
    T get_val(int r, int i) { return get_val(root[r], i, 0, n - 1); }
    T get_val(node *cur, int i, int l, int r) {
        if (l == r) return cur->x; int lc = (l + r) >> 1, rc = lc + 1;
        if (i <= ((l + r) >> 1)) return get_val(cur->l, i, l, lc);
        return get_val(cur->r, i, rc, r);
    }
    // update the ith value if the rth array by x and return the new root of the array
    int up(int r, int i, T x) {
        root.push_back(up(root[r], i, x, 0, n - 1)); return root.size() - 1;
    }
    void set(int r, int i, T x) {
        int k = up(r, i, x); root[r] = root[k]; root.pop_back();
    }
    node *up(node *pre, int i, T x, int l, int r) {
        node *cur = new node();
        if (l == r) cur->x = x;
        else {
            int lc = (l + r) >> 1, rc = lc + 1;
            if (i <= lc) {
                cur->l = up(pre->l, i, x, l, lc); cur->r = pre->r;
            }
            else {
                cur->l = pre->l; cur->r = up(pre->r, i, x, rc, r);
            }
        }
        return cur;
    }
};
mt19937_64 ran(chrono::high_resolution_clock::now().time_since_epoch().count());
struct dsu {
    PersistentArray<int> par, sz;
    vector<int> c; int cur = 0; dsu() {}
    dsu(int n, int q) { // q -> maximum instances of DSU
        vector<int> p(n + 1); for (int i = 1; i <= n; ++i) p[i] = i;
        par.make(p); sz.make(vector<int>(n + 1, 1)); c.resize(q + 1, n);
        cur = 0; // initial DSU is the 0th one
    }
    int get(int r, int u) {
        int p = par.get_val(r, u); if (p == u) return u;
        int cur = get(r, p); par.set(r, u, cur); return cur;
    }
    bool same(int r, int u, int v) { return get(r, u) == get(r, v); }
    int get_size(int r, int u) { return sz.get_val(r, get(r, u)); }
    int count(int r) { return c[r]; } // connected components
    int merge(int r, int u, int v) { // returns the updated root
        cur++; c[cur] = c[r];
        if ((u = get(r, u)) == (v = get(r, v))) {
            par.up(r, 0, 0); sz.up(r, 0, 0);
            // assert(cur == par.root.size() - 1);
            return cur;
        }
        else c[cur]--; if (ran() & 1) swap(u, v);
        int x = sz.get_val(r, v) + sz.get_val(r, u);
        par.up(r, u, v); sz.up(r, v, x);
        // assert(cur == par.root.size() - 1);
        return cur;
    }
};
int r[N];

// Operation:
    cin >> n >> q;
    dsu o(n, q + 1);
    for (i = 1; i <= q; i++) {
        int ty, id, u, v;
        cin >> ty >> id >> u >> v;
        ++id, ++u; ++v;
        if (ty == 0)  r[i] = o.merge(r[id], u, v);
        else {
            r[i] = r[i - 1]; cout << o.same(r[id], u, v) << '\n';
        }
    }

// DSU with Rollbacks:
https://codeforces.com/edu/course/2/lesson/7/3/practice/contest/289392/problem/A

class DSU {
  private:
	vector<int> par, sz; int c;
    vector<pair<int&, int>> history;
  public:
	DSU(int n) : par(n + 1), sz(n + 1, 1), c(n) {
        iota(par.begin(), par.end(), 0);
    }
	int get(int i) {
        return (par[i] == i ? i : get(par[i]));
    }
    int cc() { return c; }
	void uni(int a, int b) {
		a = get(a); b = get(b); if (a == b) return;
		if (sz[a] < sz[b]) { swap(a, b); }
        history.push_back({c, c});
        history.push_back({sz[a], sz[a]});
        history.push_back({par[b], par[b]});
		par[b] = a; sz[a] += sz[b]; --c;
	}
	int ss() { return history.size(); }
	void rlbk(int until) {
		while (ss() > until) {
			history.back().first = history.back().second;
			history.pop_back();
		}
	}
};

// Operation:
    cin >> n >> q; DSU dsu(n);
    vector<int> ss;
    while (q--) {
        string op; cin >> op;
        if (op == "union") {
            cin >> a >> b; dsu.uni(a, b);
            cout << dsu.cc() << '\n';
        }
        else if (op == "persist")
            ss.push_back(dsu.ss());
        else {
            if (ss.empty()) continue;
            dsu.rlbk(ss.back());
            ss.pop_back();
            cout << dsu.cc() << '\n';
        }
    }

// OR,
https://codeforces.com/contest/1386/problem/C
https://codeforces.com/blog/entry/83467

struct DSU {
vector<int> par, sz, w; vector<array<int, 3>> op; bool flag;
DSU() {}
DSU(int n) {
    par.resize(n + 1); sz.resize(n + 1); w.resize(n + 1); flag = true;
    for (int i = 1; i <= n; ++i) { par[i] = i; sz[i] = 1; w[i] = 0; }
}
bool is_bipartite() { return flag; }
pair<int, int> get(int u) {
    int ans = 0; while (par[u] != u)  { ans ^= w[u]; u = par[u]; }
    return make_pair(u, ans);
}
bool uni(int u, int v) {
    auto pu = get(u), pv = get(v); u = pu.first; v = pv.first;
    int last = flag, z = pu.second ^ pv.second ^ 1;
    if (u == v) {
        if (z) flag = false; op.push_back({-1, -1, last}); return false;
    }
    if (sz[u] > sz[v]) swap(u, v); op.push_back({u, w[u], last});
    par[u] = v; w[u] = z; sz[v] += sz[u]; return true;
}
void undo() {
    assert(!op.empty()); auto x = op.back(); flag = x[2]; int u = x[0];
    if (u != -1) { sz[par[u]] -= sz[u]; par[u] = u; w[u] = x[1]; }
    op.pop_back();
}
};
struct up {
bool ty; int x, y; up(int _x, int _y) { x = _x; y = _y; ty = 0; }
};
struct DSUQueue {
DSU D; vector<up> S;
DSUQueue(int n) { D = DSU(n); }
void push(up u) { D.uni(u.x, u.y); S.push_back(u); }
void pop() {
    assert(!S.empty()); vector<up> t[2];
    do {
        t[S.back().ty].push_back(S.back()); S.pop_back(); D.undo();
    } while (t[1].size() < t[0].size() && !S.empty());
    if (t[1].empty()) {
        for (auto &u : t[0]) { u.ty = 1; push(u); }
    }
    else {
        for (int i : {0, 1}) {
            reverse(t[i].begin(), t[i].end()); for (auto &u : t[i]) push(u);
        }
    }
    S.pop_back(); D.undo();
}
bool is_bipartite() { return D.is_bipartite(); }
};
int u[N], v[N], a[N];

// Operation:
    cin >> n >> m >> q;
    DSU P(n);
    for (int i = 1; i <= m; ++i) cin >> u[i] >> v[i];
    DSUQueue D(n);
    for (int i = 1; i <= m; ++i) D.push(up(u[i], v[i]));
    for (int l = 1, r = 1; l <= m; ++l) {
        while (r < l || (!D.is_bipartite() && r <= m)) {
            D.pop(); ++r;
        }
        if (D.is_bipartite()) a[l] = r - 1;
        else a[l] = m + 1;
        D.push(up(u[l], v[l]));
    }
    while (q--) {
        int l, r; cin >> l >> r;
        if (a[l] <= r) cout << "NO\n";
        else cout << "YES\n";
    }