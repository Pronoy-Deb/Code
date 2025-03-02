// Kruskal's Algorithm for Minimum Spanning Tree:
// Complexity: O(alpha(n)) or, O(E*log(E)) or, O(E*log(V))
// Use: Used to determine the cost for building an MST and the connected vertices
// Note: 1-based index

vector<pair<int64_t, int64_t>> cv; // To store the connected vertices
vector<pair<int64_t, pair<int64_t, int64_t>>> gp;
int64_t par[N], vr;
auto get(int i) {
    return par[i] == i ? i : par[i] = get(par[i]);
}
int64_t mst() {
    sort(gp.begin(), gp.end());
    int64_t sz[vr + 5];
    for (int i = 1; i <= vr; ++i) {
        par[i] = i; sz[i] = 1;
    }
    int64_t cost = 0;
    for (auto &[f, s] : gp) {
        int64_t a = get(s.first), b = get(s.second);
        if (a == b) continue; // Checking whether making cycle
        cv.emplace_back(s.first, s.second);
        if (sz[a] < sz[b]) swap(a, b); // Union by size
        par[b] = a;
        sz[a] += sz[b];
        cost += f;
    }
    return cost;
}

// Operation:
    int eg;
    cin >> vr >> eg;
    for (i = 0; i < eg; ++i) {
        int v1, v2, wt; cin >> v1 >> v2 >> wt;
        gp.push_back({wt, {v1, v2}});
    }
    cout << mst() << '\n';
    for (auto &[f, s] : cv) cout << f << ' ' << s << '\n';

// OR,

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9, mod = 1e9;

struct dsu {
    vector<int> par, rnk, size;
    int c;
    dsu(int n) : par(n + 1), rnk(n + 1, 0), size(n + 1, 1), c(n) {
        for (int i = 1; i <= n; ++i)
            par[i] = i;
    }
    int get(int i) { return (par[i] == i ? i : (par[i] = get(par[i]))); }
    bool same(int i, int j) { return get(i) == get(j); }
    int get_size(int i) { return size[get(i)]; }
    int count() { return c; } // connected components
    int merge(int i, int j) {
        if ((i = get(i)) == (j = get(j)))
            return -1;
        else
            --c;
        if (rnk[i] > rnk[j])
            swap(i, j);
        par[i] = j;
        size[j] += size[i];
        if (rnk[i] == rnk[j])
            rnk[j]++;
        return j;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<array<int, 3>> ed;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        ed.push_back({w, u, v});
    }
    sort(ed.begin(), ed.end());
    int64_t ans = 0;
    dsu d(n);
    for (auto e : ed) {
        int u = e[1], v = e[2], w = e[0];
        if (d.same(u, v))
            continue;
        ans += w;
        d.merge(u, v);
    }
    cout << ans << '\n';
    return 0;
}

// Prim's Algorithm for Minimum Spanning Tree:
// Complexity: O(E * log(V))
// Use: Used to determine the cost for building an MST and the connected vertices
// Note: 1-based index
// const int64_t N = 1e5 + 5;

vector<pair<int64_t, int64_t>> gp[N];
int64_t par[N], vr;
int64_t mst() {
    priority_queue<pair<int64_t, int64_t>, vector<pair<int64_t, int64_t>>, greater<>> pq;
    int64_t src = 1, key[vr + 5], cost = 0;
    bool vis[vr + 5]{}; pq.emplace(0, src);
    memset(par, -1, sizeof par);
    fill(key, key + vr + 5, LLONG_MAX);
    key[src] = 0;
    while (!pq.empty()) {
        int64_t u = pq.top().second; pq.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (auto &[f, s] : gp[u]) {
            if (!vis[f] && key[f] > s) {
                pq.emplace(key[f], f);
                if (key[f] != LLONG_MAX) cost -= key[f];
                key[f] = s; cost += s; par[f] = u;
            }
        }
    }
    return cost;
}

// Operation:
    int eg; cin >> vr >> eg;
    for (i = 0; i < eg; ++i) {
        int u, v, w; cin >> u >> v >> w;
        gp[u].emplace_back(v, w); gp[v].emplace_back(u, w);
    }
    cout << mst() << '\n';
    for (i = 1; i <= vr; ++i) {
        if (par[i] != -1) cout << i << ' ' << par[i] << '\n';
    }

// OR,

#include <bits/stdc++.h>
using namespace std;

const int N = 2020;
int g[N][N], w[N], to[N], selected[N];
int64_t Prims(int n, vector<pair<int, int>> &edges) {
    int64_t ans = 0;
    for (int i = 1; i <= n; i++)
        w[i] = 1e9, selected[i] = 0, to[i] = -1;
    w[1] = 0;
    for (int i = 1; i <= n; i++) {
        int u = -1;
        for (int j = 1; j <= n; j++)
            if (!selected[j] && (u == -1 || w[j] < w[u]))
                u = j;
        if (w[u] == 1e9)
            return -1; // NO MST
        selected[u] = 1;
        ans += w[u];
        if (to[u] != -1)
            edges.emplace_back(u, to[u]); // order of the edges may be changed
        for (int v = 1; v <= n; v++)
            if (g[u][v] < w[v])
                w[v] = g[u][v], to[v] = u;
    }
    return ans;
}
string s[N];
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            g[i][j] = 1e9;
    for (int i = 1; i <= n; i++)
        cin >> s[i];
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int w = 0;
            for (int k = 0; k < m; k++)
                w = max(w, (int)abs(s[i][k] - s[j][k]));
            g[i][j] = min(g[i][j], w);
            g[j][i] = min(g[j][i], w);
        }
    }
    vector<pair<int, int>> ed;
    int64_t ans = Prims(n, ed);
    int res = 0;
    for (auto e : ed)
        res = max(res, g[e.first][e.second]);
    cout << res << '\n';
    return 0;
}
/*
https://www.codechef.com/ICL2016/problems/ICL16A
*/

// Directed MST:

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

const int64_t inf = 1e18;

template <typename T>
struct PQ {
    int64_t sum = 0;
    priority_queue<T, vector<T>, greater<T>> Q;
    void push(T x) {
        x.w -= sum;
        Q.push(x);
    }
    T pop() {
        auto ans = Q.top();
        Q.pop();
        ans.w += sum;
        return ans;
    }
    int size() { return Q.size(); }
    void add(int64_t x) { sum += x; }
    void merge(PQ &&x) {
        if (size() < x.size())
            swap(sum, x.sum), swap(Q, x.Q);
        while (x.size()) {
            auto tmp = x.pop();
            tmp.w -= sum;
            Q.push(tmp);
        }
    }
};
struct edge {
    int u, v;
    int64_t w;
    bool operator>(const edge &rhs) const { return w > rhs.w; }
};
struct DSU {
    vector<int> par;
    DSU(int n) : par(n, -1) {}
    int root(int i) { return par[i] < 0 ? i : par[i] = root(par[i]); }
    void set_par(int c, int p) { par[c] = p; }
};
// returns parents of each vertex
// each edge should be distinct
// it assumes that a solution exists (all vertices are reachable from root)
// 0 indexed
// Takes ~300ms for n = 2e5
vector<int> DMST(int n, int root, const vector<edge> &edges) {
    vector<int> u(2 * n - 1, -1), par(2 * n - 1, -1);
    edge par_edge[2 * n - 1];
    vector<int> child[2 * n - 1];

    PQ<edge> Q[2 * n - 1];
    for (auto e : edges)
        Q[e.v].push(e);
    for (int i = 0; i < n; i++)
        Q[(i + 1) % n].push({i, (i + 1) % n, inf});

    int super = n;
    DSU dsu(2 * n - 1);
    int head = 0;
    while (Q[head].size()) {
        auto x = Q[head].pop();
        int nxt_root = dsu.root(x.u);
        if (nxt_root == head)
            continue;
        u[head] = nxt_root;
        par_edge[head] = x;
        if (u[nxt_root] == -1)
            head = nxt_root;
        else {
            int j = nxt_root;
            do {
                Q[j].add(-par_edge[j].w);
                Q[super].merge(move(Q[j]));
                assert(u[j] != -1);
                child[super].push_back(j);
                j = dsu.root(u[j]);
            } while (j != nxt_root);
            for (auto u : child[super])
                par[u] = super, dsu.set_par(u, super);
            head = super++;
        }
    }
    vector<int> res(2 * n - 1, -1);
    queue<int> q;
    q.push(root);
    while (q.size()) {
        int u = q.front();
        q.pop();
        while (par[u] != -1) {
            for (auto v : child[par[u]]) {
                if (v != u)
                {
                    res[par_edge[v].v] = par_edge[v].u;
                    q.push(par_edge[v].v);
                    par[v] = -1;
                }
            }
            u = par[u];
        }
    }
    res[root] = root;
    res.resize(n);
    return res;
}
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, root;
    cin >> n >> m >> root;
    vector<edge> edges(m);
    for (auto &e : edges)
        cin >> e.u >> e.v >> e.w;
    auto res = DMST(n, root, edges);

    unordered_map<int, int> W[n];
    for (auto u : edges)
        W[u.v][u.u] = u.w;

    int64_t ans = 0;
    for (int i = 0; i < n; i++)
        if (i != root)
            ans += W[i][res[i]];
    cout << ans << '\n';
    for (auto x : res)
        cout << x << ' ';
    cout << '\n';
    return 0;
}
// https://judge.yosupo.jp/problem/directedmst
// http://www.cs.tau.ac.il/~zwick/grad-algo-13/directed-mst.pdf

// Dynamic MST Offline:

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 9;

// credit: koosaga
struct disj {
    int pa[MAXN], rk[MAXN];
    void init(int n) {
        iota(pa, pa + n + 1, 0);
        memset(rk, 0, sizeof(rk));
    }
    int get(int x) {
        return pa[x] == x ? x : get(pa[x]);
    }
    bool uni(int p, int q, vector<pair<int, int>> &snapshot) {
        p = get(p);
        q = get(q);
        if (p == q)
            return 0;
        if (rk[p] < rk[q])
            swap(p, q);
        snapshot.push_back({q, pa[q]});
        pa[q] = p;
        if (rk[p] == rk[q]) {
            snapshot.push_back({p, -1});
            rk[p]++;
        }
        return 1;
    }
    void revert(vector<pair<int, int>> &snapshot) {
        reverse(snapshot.begin(), snapshot.end());
        for (auto &x : snapshot) {
            if (x.second < 0)
                rk[x.first]--;
            else
                pa[x.first] = x.second;
        }
        snapshot.clear();
    }
} disj;

int n, m, q;
int st[MAXN], ed[MAXN], cost[MAXN], chk[MAXN];
pair<int, int> qr[MAXN];

bool cmp(int &a, int &b) { return pair<int, int>(cost[a], a) < pair<int, int>(cost[b], b); }

void contract(int s, int e, vector<int> v, vector<int> &must_mst, vector<int> &maybe_mst) {
    sort(v.begin(), v.end(), cmp);
    vector<pair<int, int>> snapshot;
    for (int i = s; i <= e; i++)
        disj.uni(st[qr[i].first], ed[qr[i].first], snapshot);
    for (auto &i : v)
        if (disj.uni(st[i], ed[i], snapshot))
            must_mst.push_back(i);
    disj.revert(snapshot);
    for (auto &i : must_mst)
        disj.uni(st[i], ed[i], snapshot);
    for (auto &i : v)
        if (disj.uni(st[i], ed[i], snapshot))
            maybe_mst.push_back(i);
    disj.revert(snapshot);
}

void solve(int s, int e, vector<int> v, int64_t int cv) {
    if (s == e) {
        cost[qr[s].first] = qr[s].second;
        if (st[qr[s].first] == ed[qr[s].first]) {
            printf("%lld\n", cv);
            return;
        }
        int minv = qr[s].second;
        for (auto &i : v)
            minv = min(minv, cost[i]);
        printf("%lld\n", minv + cv);
        return;
    }
    int m = (s + e) / 2;
    vector<int> lv = v, rv = v;
    vector<int> must_mst, maybe_mst;
    for (int i = m + 1; i <= e; i++) {
        chk[qr[i].first]--;
        if (chk[qr[i].first] == 0)
            lv.push_back(qr[i].first);
    }
    vector<pair<int, int>> snapshot;
    contract(s, m, lv, must_mst, maybe_mst);
    int64_t int lcv = cv;
    for (auto &i : must_mst)
        lcv += cost[i], disj.uni(st[i], ed[i], snapshot);
    solve(s, m, maybe_mst, lcv);
    disj.revert(snapshot);
    must_mst.clear();
    maybe_mst.clear();
    for (int i = m + 1; i <= e; i++)
        chk[qr[i].first]++;
    for (int i = s; i <= m; i++) {
        chk[qr[i].first]--;
        if (chk[qr[i].first] == 0)
            rv.push_back(qr[i].first);
    }
    int64_t int rcv = cv;
    contract(m + 1, e, rv, must_mst, maybe_mst);
    for (auto &i : must_mst)
        rcv += cost[i], disj.uni(st[i], ed[i], snapshot);
    solve(m + 1, e, maybe_mst, rcv);
    disj.revert(snapshot);
    for (int i = s; i <= m; i++)
        chk[qr[i].first]++;
}

int main() {
    scanf("%d %d", &n, &m);
    vector<int> ve;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &st[i], &ed[i], &cost[i]);
    }
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &qr[i].first, &qr[i].second);
        qr[i].first--;
        chk[qr[i].first]++;
    }
    disj.init(n);
    for (int i = 0; i < m; i++)
        if (!chk[i])
            ve.push_back(i);
    solve(0, q - 1, ve, 0);
}
// https://codeforces.com/problemsets/acmsguru/problem/99999/529

// Manhattan MST:

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 9;

int n;
vector<pair<int, int>> g[N];
struct PT {
    int x, y, id;
    bool operator<(const PT &p) const {
        return x == p.x ? y < p.y : x < p.x;
    }
} p[N];
struct node {
    int val, id;
} t[N];
struct DSU {
    int p[N];
    void init(int n) {
        for (int i = 1; i <= n; i++)
            p[i] = i;
    }
    int get(int u) { return p[u] == u ? u : p[u] = get(p[u]); }
    void merge(int u, int v) { p[get(u)] = get(v); }
} dsu;
struct edge {
    int u, v, w;
    bool operator<(const edge &p) const { return w < p.w; }
};
vector<edge> edges;
int query(int x) {
    int r = 2e9 + 10, id = -1;
    for (; x <= n; x += (x & -x))
        if (t[x].val < r)
            r = t[x].val, id = t[x].id;
    return id;
}
void modify(int x, int w, int id) {
    for (; x > 0; x -= (x & -x))
        if (t[x].val > w)
            t[x].val = w, t[x].id = id;
}
int dist(PT &a, PT &b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}
void add(int u, int v, int w) {
    edges.push_back({u, v, w});
}
int64_t Kruskal() {
    dsu.init(n);
    sort(edges.begin(), edges.end());
    int64_t ans = 0;
    for (edge e : edges) {
        int u = e.u, v = e.v, w = e.w;
        if (dsu.get(u) != dsu.get(v)) {
            ans += w;
            g[u].push_back({v, w});
            // g[v].push_back({u, w});
            dsu.merge(u, v);
        }
    }
    return ans;
}
void Manhattan() {
    for (int i = 1; i <= n; ++i)
        p[i].id = i;
    for (int dir = 1; dir <= 4; ++dir) {
        if (dir == 2 || dir == 4) {
            for (int i = 1; i <= n; ++i)
                swap(p[i].x, p[i].y);
        }
        else if (dir == 3) {
            for (int i = 1; i <= n; ++i)
                p[i].x = -p[i].x;
        }
        sort(p + 1, p + 1 + n);
        vector<int> v;
        static int a[N];
        for (int i = 1; i <= n; ++i)
            a[i] = p[i].y - p[i].x, v.push_back(a[i]);
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        for (int i = 1; i <= n; ++i)
            a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
        for (int i = 1; i <= n; ++i)
            t[i].val = 2e9 + 10, t[i].id = -1;
        for (int i = n; i >= 1; --i) {
            int pos = query(a[i]);
            if (pos != -1) add(p[i].id, p[pos].id, dist(p[i], p[pos]));
            modify(a[i], p[i].x + p[i].y, i);
        }
    }
}
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> p[i].x >> p[i].y;
    Manhattan();
    cout << Kruskal() << '\n';
    for (int u = 1; u <= n; u++) {
        for (auto x : g[u])
            cout << u - 1 << ' ' << x.first - 1 << '\n';
    }
    return 0;
}
// https://judge.yosupo.jp/problem/manhattanmst