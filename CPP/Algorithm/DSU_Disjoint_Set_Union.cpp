// Complexity: O(alpha(n))

int par[N], sz[N], n;
void make() {
    for (int i = 1; i <= n; ++i) {
        par[i] = i; sz[i] = 1;
    }
}
int find(int nd) {
    if (nd == par[nd]) return nd;
    return par[nd] = find(par[nd]);
}
void Union(int a, int b) {
    a = find(a); b = find(b);
    if (a != b) {
        if (sz[a] < sz[b]) swap(a, b);
        par[b] = a; sz[a] += sz[b];
    }
}

// Operation: Determining the number of CONNECTED COMPONENTS after performing the union operation:
    cin >> n >> k;
    while (k--) {
        int u, v; cin >> u >> v;
        Union(u, v);
    }
    int cc = 0;
    for (i = 1; i <= n; ++i) {
        if (find(i) == i) ++cc;
    }
    cout << cc;

// Problem: https://codeforces.com/contest/1857/problem/G

// OR,

struct dsu {
    vector<int> par;
    dsu(){};
    dsu(int n) {
        par.resize(n + 2);
        iota(par.begin(), par.end(), 0);
    }
    int find(int u) {
        if (u == par[u]) return u;
        return par[u] = find(par[u]);
    }
    int merge(int u, int v) { par[find(u)] = find(v); }
};

// OR,

struct DSU {
vector<int> par, rnk, sz; int c;
DSU(int n) : par(n + 1), rnk(n + 1, 0), sz(n + 1, 1), c(n) {
    for (int i = 1; i <= n; ++i) par[i] = i;
}
int find(int i) {
    return (par[i] == i ? i : (par[i] = find(par[i])));
}
bool same(int i, int j) { return find(i) == find(j); }
int get_size(int i) { return sz[find(i)]; }
int cc() { return c; } // connected components
int merge(int i, int j) {
    if ((i = find(i)) == (j = find(j))) return -1;
    else --c;
    if (rnk[i] > rnk[j]) swap(i, j);
    par[i] = j; sz[j] += sz[i];
    if (rnk[i] == rnk[j]) rnk[j]++;
    return j;
}
};

// DSU on Tree:

vector<int> g[N]; long long ans[N], col[N], sz[N], cnt[N]; bool big[N];
void dfs(int u, int p) {
    sz[u] = 1;
    for (auto &v : g[u]) {
        if (v == p) continue;
        dfs(v, u); sz[u] += sz[v];
    }
}
void add(int u, int p, long long x) {
    cnt[col[u]] += x;
    for (auto &v : g[u]) {
        if (v == p || big[v] == 1) continue;
        add(v, u, x);
    }
}
void dsu(int u, int p, bool keep) {
    int bigchild = -1, mx = -1;
    for (auto &v : g[u]) {
        if (v == p) continue;
        if (sz[v] > mx) mx = sz[v], bigchild = v;
    }
    for (auto &v : g[u]) {
        if (v == p || v == bigchild) continue;
        dsu(v, u, 0);
    }
    if (bigchild != -1) dsu(bigchild, u, 1), big[bigchild] = 1;
    add(u, p, 1);
    ans[u] = cnt[u];
    if (bigchild != -1) big[bigchild] = 0;
    if (keep == 0) add(u, p, -1);
}

/* Augmented DSU
Application:- used for maintaining a system of equations of the form ( y-x = d ) along
with  their consistencial queries dynamically using disjoint set union and find data structure.
Inspired by the problem http://www.spoj.com/problems/CHAIN/  which utilises this concept, which can extended for solving
problems of kind as explained above.
*/

int pot[N], prec[N], flaw; //counting numbers of inconsistent assertions
void init(int n) {
    flaw = 0;
    for (int i = 1; i <= n; ++i) {
        prec[i] = i; pot[i] = 0;
    }
}
int find(int x) {
    if (prec[x] == x) return x;
    int rx = find(prec[x]);  // rx is the root of x
    pot[x] = pot[prec[x]] + pot[x]; //add all potentials along the path,i.e.,potential calculated wrt root
    return prec[x] = rx;
}
void merge(int a, int b, int d) {
    int ra = find(a), rb = find(b);
    if (ra == rb && pot[a] - pot[b] != d) flaw++;
    else if (ra != rb) {
        pot[ra] = d + pot[b] - pot[a]; prec[ra] = rb;
    }
}
Operation:
    int n;   //no. of variables
    cin >> n;
    int m;   // no. of equations
    cin >> m;
    init(n);
    for (int i = 1; i <= m; ++i) { //consider 1-based indexing of variables
        int a, b, d;         //asserting a-b=d;
        cin >> a >> b >> d;
        merge(a, b, d);
    }
    cout << "No. of inconsistencies= " << flaw;
    //queries of type y-x=? can be given through pot[y]-pot[x] (only when then are in same component
    //i.e., can be extracted from the information so far )

// DSU Partially Persistent:

struct DSU {
vector<vector<pair<int, int>>> par;
int time = 0; // initial time
DSU(int n) : par(n + 1, {{-1, 0}}) {}
bool merge(int u, int v) {
    ++time;
    if ((u = root(u, time)) == (v = root(v, time))) return false;
    if (par[u].back().first > par[v].back().first) swap(u, v);
    par[u].push_back({par[u].back().first + par[v].back().first, time});
    par[v].push_back({u, time}); // par[v] = u
    return true;
}
bool same(int u, int v, int t) {
    return root(u, t) == root(v, t);
}
int root(int u, int t) { // root of u at time t
    if (par[u].back().first >= 0 && par[u].back().second <= t) return root(par[u].back().first, t);
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
};

int ar[N];
// Operation:
    cin >> n >> m;
    DSU d(n);
    for (i = 1; i <= m; ++i) {
        int ty, u, v; cin >> ty >> u >> v;
        if (ty == 1) {
            d.merge(u, v); ar[d.time] = i;
        }
        else {
            int ans = -1, l = 0, r = d.time;
            while (l <= r) {
                int mid = l + r >> 1;
                if (d.same(u, v, mid)) ans = ar[mid], r = mid - 1;
                else l = mid + 1;
            }
            cout << ans << '\n';
        }
    }

// Problem: https://codeforces.com/gym/100814/problem/C

// DSU with Rollbacks:

struct DSU {
vector<int> par, sz, w; vector<array<int, 3>> op; bool flag;
DSU() {}
DSU(int n) {
    par.resize(n + 1); sz.resize(n + 1); w.resize(n + 1);
    flag = true;
    for (int i = 1; i <= n; ++i) {
        par[i] = i; sz[i] = 1; w[i] = 0;
    }
}
bool is_bipartite() { return flag; }
pair<int, int> find(int u) {
    int ans = 0;
    while (par[u] != u)  {
        ans ^= w[u]; u = par[u];
    }
    return make_pair(u, ans);
}
bool merge(int u, int v) {
    auto pu = find(u), pv = find(v);
    u = pu.first; v = pv.first;
    int last = flag, z = pu.second ^ pv.second ^ 1;
    if (u == v) {
        if (z) flag = false;
        op.push_back({-1, -1, last});
        return false;
    }
    if (sz[u] > sz[v]) swap(u, v);
    op.push_back({u, w[u], last});
    par[u] = v; w[u] = z; sz[v] += sz[u];
    return true;
}
void undo() {
    assert(!op.empty()); auto x = op.back();
    flag = x[2]; int u = x[0];
    if (u != -1) {
        sz[par[u]] -= sz[u]; par[u] = u; w[u] = x[1];
    }
    op.pop_back();
}
};
struct update {
bool type; int x, y;
update(int _x, int _y) {
    x = _x; y = _y; type = 0;
}
};
struct DSUQueue {
DSU D;
vector<update> S;
DSUQueue(int n) { D = DSU(n); }
void push(update u) {
    D.merge(u.x, u.y); S.push_back(u);
}
void pop() {
    assert(!S.empty());
    vector<update> t[2];
    do {
        t[S.back().type].push_back(S.back());
        S.pop_back(); D.undo();
    } while (t[1].size() < t[0].size() && !S.empty());
    if (t[1].empty()) {
        for (auto &u : t[0]) {
            u.type = 1; push(u);
        }
    }
    else {
        for (int i : {0, 1}) {
            reverse(t[i].begin(), t[i].end());
            for (auto &u : t[i]) push(u);
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
    for (int i = 1; i <= m; ++i) D.push(update(u[i], v[i]));
    for (int l = 1, r = 1; l <= m; ++l) {
        while (r < l || (!D.is_bipartite() && r <= m)) {
            D.pop(); ++r;
        }
        if (D.is_bipartite()) a[l] = r - 1;
        else a[l] = m + 1;
        D.push(update(u[l], v[l]));
    }
    while (q--) {
        int l, r; cin >> l >> r;
        if (a[l] <= r) cout << "NO\n";
        else cout << "YES\n";
    }

// https://codeforces.com/contest/1386/problem/C
// https://codeforces.com/blog/entry/83467