// Dijkstra: O(V + E*log(V))
// Use: Used to determine the shortest distance between source and destination vertex
// Note: Does not work for negative (-ve) value of weights, use Bellman-Ford instead

vector<pair<int, int64_t>> gp[N];
bitset<N> vis; int64_t path[N], dis[N];
void dij(int src) {
    fill(dis, dis + N, LLONG_MAX);
    dis[src] = 0; set<pair<int64_t, int>> st;
    st.emplace(0, src);
    while (!st.empty()) {
        int nd = (*st.begin()).second; st.erase(st.begin());
        if(vis[nd]) continue; vis[nd] = true;
        for (auto &[cld, wt] : gp[nd]) {
            if (dis[nd] + wt < dis[cld]) {
                dis[cld] = dis[nd] + wt; st.emplace(dis[cld], cld);
                path[cld] = nd;
            }
        }
    }
}

// Opration:
    int vr, eg; cin >> vr >> eg;
    for (i = 0; i < eg; ++i) {
        int v1, v2, wt; cin >> v1 >> v2 >> wt;
        gp[v1].emplace_back(v2, wt);
        gp[v2].emplace_back(v1, wt);
    }
    int src; cin >> src;
    dij(src);

    // Printing the shortest distance of vertex vr:
    cout << dis[vr] << '\n';

    // Storing and printing the shortest path:
    vector<int> v = {vr};
    do {
        vr = path[vr];
        if (!vr) {
            cout << -1 << '\n';
            return;
        }
        v.emplace_back(vr);
    } while (vr != 1);
    for (i = v.size() - 1; i >= 0; --i)
        cout << v[i] << ' ';

// Problem: https://atcoder.jp/contests/abc340/tasks/abc340_d

// OR,
/*
 * Find k-th shortest path
 * using Dijkstra's Algo
 * Replace k = 1 to find the shortest path
 * cnt[u] = number of times u is visited
 */

// Operation:
    cin >> n >> m >> k;
    vector<pair<int, int>> gp[n + 5];
    for (i = 1; i <= m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        gp[u].push_back({v, w});
    }
    int cnt[n + 5]{};
    multiset<pair<int64_t, int>> st;
    st.emplace(0, 1);
    while (!st.empty()) {
        auto [d, u] = *st.begin();
        st.erase(st.begin());
        if (++cnt[u] <= k and u == n) cout << d << ' ';
        if (cnt[u] <= k) {
            for (auto &[v, w] : gp[u])
                st.emplace(d + w, v);
        }
    }

// Problem: https://cses.fi/problemset/task/1196/
// https://lightoj.com/problem/not-the-best

// OR,

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9, mod = 998244353;

int n, m;
vector<pair<int, int>> g[N], r[N];
vector<int64_t> dijkstra(int s, int t, vector<int> &cnt) {
    const int64_t inf = 1e18;
    priority_queue<pair<int64_t, int>, vector<pair<int64_t, int>>, greater<pair<int64_t, int>>> q;
    vector<int64_t> d(n + 1, inf);
    vector<bool> vis(n + 1, 0);
    q.push({0, s});
    d[s] = 0;
    cnt.resize(n + 1, 0);  // number of shortest paths
    cnt[s] = 1;
    while (!q.empty()) {
        auto x = q.top();
        q.pop();
        int u = x.second;
        if (vis[u])
            continue;
        vis[u] = 1;
        for (auto y : g[u]) {
            int v = y.first;
            int64_t w = y.second;
            if (d[u] + w < d[v]) {
                d[v] = d[u] + w;
                q.push({d[v], v});
                cnt[v] = cnt[u];
            } else if (d[u] + w == d[v])
                cnt[v] = (cnt[v] + cnt[u]) % mod;
        }
    }
    return d;
}

int u[N], v[N], w[N];
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int s, t;
    cin >> n >> m >> s >> t;
    for (int i = 1; i <= m; i++) {
        cin >> u[i] >> v[i] >> w[i];
        g[u[i]].push_back({v[i], w[i]});
        r[v[i]].push_back({u[i], w[i]});
    }
    vector<int> cnt1, cnt2;
    auto d1 = dijkstra(s, t, cnt1);
    auto d2 = dijkstra(t, s, cnt2);

    int64_t ans = d1[t];
    for (int i = 1; i <= m; i++) {
        int x = u[i], y = v[i];
        int64_t nw = d1[x] + w[i] + d2[y];
        if (nw == ans && 1LL * cnt1[x] * cnt2[y] % mod == cnt1[t])
            cout << "YES\n";
        else if (nw - ans + 1 < w[i])
            cout << "CAN " << nw - ans + 1 << '\n';
        else
            cout << "NO\n";
    }
    return 0;
}

// Dijkstra on Segment Tree:

vector<pair<int, int>> g[N * 9];
inline void add_edge(int u, int v, int w) {
    g[u].push_back({v, w});
}
int add;
void build(int n, int b, int e) {
    if (b == e) {
        add_edge(b, n + add, 0);
        add_edge(n + add * 5, b, 0);
        return;
    }
    int mid = b + e >> 1;
    add_edge(2 * n + add, n + add, 0);
    add_edge(2 * n + 1 + add, n + add, 0);
    add_edge(n + 5 * add, 2 * n + 5 * add, 0);
    add_edge(n + 5 * add, 2 * n + 1 + 5 * add, 0);
    build(2 * n, b, mid);
    build(2 * n + 1, mid + 1, e);
}
void upd(int n, int b, int e, int i, int j, int dir, int u, int w) {
    if (j < b || e < i)
        return;
    if (i <= b && e <= j) {
        if (dir)
            add_edge(u, n + 5 * add, w);  // from u to this range
        else
            add_edge(n + add, u, w);  // from this range to u
        return;
    }
    int mid = (b + e) >> 1;
    upd(2 * n, b, mid, i, j, dir, u, w);
    upd(2 * n + 1, mid + 1, e, i, j, dir, u, w);
}

vector<int64_t> dijkstra(int s) {
    const int64_t inf = 1e18;
    priority_queue<pair<int64_t, int>, vector<pair<int64_t, int>>, greater<pair<int64_t, int>>> q;
    vector<int64_t> d(9 * N + 1, inf);
    vector<bool> vis(9 * N + 1, 0);
    q.push({0, s});
    d[s] = 0;
    while (!q.empty()) {
        auto x = q.top();
        q.pop();
        int u = x.second;
        if (vis[u])
            continue;
        vis[u] = 1;
        for (auto y : g[u]) {
            int v = y.first;
            int64_t w = y.second;
            if (d[u] + w < d[v]) {
                d[v] = d[u] + w;
                q.push({d[v], v});
            }
        }
    }
    return d;
}
int64_t ans[N];
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q, s;
    cin >> n >> q >> s;
    add = n;
    build(1, 1, n);
    while (q--) {
        int ty;
        cin >> ty;
        int u, l, r, w;
        if (ty == 1) {
            cin >> u >> l >> w;
            r = l;
        } else {
            cin >> u >> l >> r >> w;
        }
        upd(1, 1, n, l, r, ty <= 2, u, w);
    }
    auto ans = dijkstra(s);
    for (int i = 1; i <= n; i++) {
        if (ans[i] == 1e18)
            ans[i] = -1;
        cout << ans[i] << ' ';
    }
    return 0;
}
// https://codeforces.com/contest/786/problem/B

// Shortest Path that does not pass through each edge:

using ll = int64_t;
const ll inf = 1e18;
using T = pair<ll, int>;

vector<array<int, 3>> g[N];
ll d[N], rd[N], f[N];
vector<array<int, 2>> S[N], R[N];  // shortest path graph, reverse shortest path graph
bool sp_edge[N];                   // if edge is in the main shortest path
int path_id[N], l[N], r[N], u[N], v[N], w[N], edge[N];
vector<T> event[N];
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, Q;
    cin >> n >> m >> Q;
    for (int i = 1; i <= m; i++) {
        cin >> u[i] >> v[i] >> w[i];
        g[u[i]].push_back({v[i], w[i], i});
        g[v[i]].push_back({u[i], w[i], i});
    }
    priority_queue<T, vector<T>, greater<T>> q;
    for (int i = 1; i <= n; i++) {
        d[i] = inf;
    }
    d[1] = 0;
    q.push({0, 1});
    while (!q.empty()) {
        auto [x, u] = q.top();
        q.pop();
        for (auto [v, w, i] : g[u]) {
            if (d[u] + w < d[v]) {
                d[v] = d[u] + w;
                edge[v] = i;
                q.push({d[v], v});
            }
        }
    }
    q = priority_queue<T, vector<T>, greater<T>>();
    for (int i = 1; i <= n; i++) {
        rd[i] = inf;
    }
    rd[n] = 0;
    q.push({0, n});
    while (!q.empty()) {
        auto [x, u] = q.top();
        q.pop();
        for (auto [v, w, i] : g[u]) {
            if (rd[u] + w < rd[v]) {
                rd[v] = rd[u] + w;
                q.push({rd[v], v});
            }
        }
    }
    for (int u = 1; u <= n; u++) {
        for (auto [v, w, i] : g[u]) {
            if (d[u] + w == d[v]) {
                S[u].push_back({v, i});
            }
        }
        for (auto [v, w, i] : g[u]) {
            if (rd[u] + w == rd[v]) {
                R[u].push_back({v, i});
            }
        }
    }
    int cur = n;
    vector<int> path;
    while (cur != 1) {
        int i = edge[cur];
        path.push_back(i);
        sp_edge[i] = true;
        int up = cur ^ u[i] ^ v[i];
        cur = up;
    }
    reverse(path.begin(), path.end());
    for (int i = 0; i < path.size(); i++) {
        path_id[path[i]] = i;
    }

    vector<T> vec;
    for (int i = 1; i <= n; i++) {
        vec.push_back({d[i], i});
    }
    sort(vec.begin(), vec.end());
    for (int i = 1; i <= n; i++) {
        l[i] = path.size();
    }
    l[1] = -1;
    for (auto [_, u] : vec) {
        for (auto [v, i] : S[u]) {
            if (sp_edge[i]) {
                l[v] = min(l[v], path_id[i]);
            } else {
                l[v] = min(l[v], l[u]);
            }
        }
    }

    vec.clear();
    for (int i = 1; i <= n; i++) {
        vec.push_back({rd[i], i});
    }
    sort(vec.begin(), vec.end());
    for (int i = 1; i <= n; i++) {
        r[i] = -1;
    }
    r[n] = path.size();
    for (auto [_, u] : vec) {
        for (auto [v, i] : R[u]) {
            if (sp_edge[i]) {
                r[v] = max(r[v], path_id[i]);
            } else {
                r[v] = max(r[v], r[u]);
            }
        }
    }

    for (int u = 1; u <= n; u++) {
        for (auto [v, w, _] : g[u]) {
            if (sp_edge[_])
                continue;
            ll cur = d[u] + rd[v] + w;
            if (l[u] + 1 <= r[v] - 1) {
                event[l[u] + 1].push_back({cur, +1});
                event[r[v] - 1 + 1].push_back({cur, -1});
            }
        }
    }
    multiset<ll> se;
    for (int i = 0; i < path.size(); i++) {
        for (auto [cur, add] : event[i]) {
            if (add == 1) {
                se.insert(cur);
            } else {
                se.erase(se.find(cur));
            }
        }
        if (se.empty()) {
            f[i] = inf;
        } else {
            f[i] = *se.begin();
        }
    }

    while (Q--) {
        int i, x;
        cin >> i >> x;

        ll ans = d[u[i]] + rd[v[i]] + x;
        ans = min(ans, d[v[i]] + rd[u[i]] + x);

        // shortest path from 1 to n that doesn't pass through edge i
        ll except_i = inf;
        if (sp_edge[i]) {
            // for (int u = 1; u <= n; u++) {
            //   for (auto [v, w, _]: g[u]) {
            //     if (!sp_edge[_] and l[u] < path_id[i] and path_id[i] < r[v]) {
            //       except_i = min(except_i, d[u] + rd[v] + w);
            //     }
            //   }
            // }
            except_i = f[path_id[i]];
        } else {
            except_i = min(except_i, d[n]);
        }
        ans = min(ans, except_i);
        cout << ans << '\n';
    }
    return 0;
}
// https://codeforces.com/contest/1163/problem/F

// Bellman Ford (Single Source Shortest Distance with (-ve) Cost): O(V * E)

bool bmf(auto src, auto &gp, auto &dis) {
    int64_t V = dis.size();
    dis[src] = 0;
    bool updated;
    do {
        updated = false;
        priority_queue<pair<int64_t, int64_t>, vector<pair<int64_t, int64_t>>, greater<pair<int64_t, int64_t>>> pq;
        for (int u = 0; u < V; ++u)
            if (dis[u] != LONG_LONG_MAX) pq.emplace(dis[u], u);
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            for (auto &[v, w] : gp[u]) {
                if (dis[u] + w < dis[v]) {
                    dis[v] = dis[u] + w;
                    pq.emplace(dis[v], v);
                    updated = true;
                }
                if (dis[u] != LONG_LONG_MAX && dis[u] + w < dis[v]) return true;
            }
        }
    } while (updated);
    return false;
}

// Operation:
    int vr, eg; cin >> vr >> eg;
    vector<vector<pair<int64_t, int64_t>>> gp(vr + 50);
    vector<int64_t> dis(vr + 5, LLONG_MAX);
    for (i = 0; i < eg; ++i) {
        int64_t u, v, w;
        cin >> u >> v >> w;
        gp[u].emplace_back(v, w);
    }
    int64_t src;
    cin >> src;  // specify the source
    if (bmf(src, gp, dis)) {
        cout << -1 << '\n';
        return;
    }  // checking negative cycle
    for (i = 0; i < vr; ++i)  // Vertex distance from Source Vertex
        cout << dis[i] << '\n';

https://cses.fi/problemset/task/1197

    cin >> n >> m;
    vector<tuple<int, int, int>> gp;
    for (i = 1; i <= m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        gp.emplace_back(u, v, w);
    }
    int64_t dis[n + 5], par[n + 5];
    fill(dis, dis + n + 5, M * M);
    int lst;
    dis[1] = 0;
    for (i = 0; i < n; ++i) {
        lst = -1;
        for (auto &[u, v, w] : gp) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                par[v] = u;
                lst = v;
            }
        }
    }
    if (lst == -1) cout << "NO";
    else {
        while (n--) lst = par[lst];
        cout << "YES" << '\n';
        vector<int> nc;
        for (int cur = lst;; cur = par[cur]) {
            nc.push_back(cur);
            if (cur == lst && nc.size() > 1) break;
        }
        for (i = nc.size() - 1; i >= 0; --i) cout << nc[i] << ' ';
    }

// OR,

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

struct st {
    int a, b, cost;
} e[N];
const int INF = 2e9;
int32_t main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) cin >> e[i].a >> e[i].b >> e[i].cost;
    int s;
    cin >> s;               // is there any negative cycle which is reachable from s?
    vector<int> d(n, INF);  // for finding any cycle(not necessarily from s) set d[i] = 0 for all i
    d[s] = 0;
    vector<int> p(n, -1);
    int x;
    for (int i = 0; i < n; ++i) {
        x = -1;
        for (int j = 0; j < m; ++j) {
            if (d[e[j].a] < INF) {
                if (d[e[j].b] > d[e[j].a] + e[j].cost) {
                    d[e[j].b] = max(-INF, d[e[j].a] + e[j].cost);  // for overflow
                    p[e[j].b] = e[j].a; x = e[j].b;
                }
            }
        }
    }
    if (x == -1) cout << "No negative cycle from " << s;
    else {
        int y = x;  // x can be on any cycle or reachable from some cycle
        for (int i = 0; i < n; ++i) y = p[y];
        vector<int> path;
        for (int cur = y;; cur = p[cur]) {
            path.push_back(cur);
            if (cur == y && path.size() > 1) break;
        }
        reverse(path.begin(), path.end());
        cout << "Negative cycle: ";
        for (int i = 0, sz = path.size(); i < sz; ++i) cout << path[i] << ' ';
    }
    return 0;
}

// Floyd Warshall (All pair shortest distance): O(n^3)
https://atcoder.jp/contests/abc375/tasks/abc375_f

const ll N = 3e2 + 5, M = 1e12;
int64_t dis[N][N], n;
void reset() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) dis[i][j] = (i == j ? 0 : M);
    }
}
void pre() {
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
        }
    }
}
void add(int a, int b, int64_t c) { // add a new edge from a <--> b with cost c
    dis[a][b] = min(dis[a][b], c); dis[b][a] = min(dis[b][a], c);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            dis[i][j] = min(dis[i][j], dis[i][a] + dis[b][j] + dis[a][b]);
            dis[i][j] = min(dis[i][j], dis[i][b] + dis[a][j] + dis[b][a]);
        }
    }
}

// Operation:
    cin >> n >> m >> q;
    reset(); vector<int> eg[m];
    for (i = 0; i < m; ++i) {
        cin >> a >> b >> c; eg[i] = {a, b, c};
        dis[a][b] = dis[b][a] = c;
    }
    vector<int> qr[q];
    for (i = 0; i < q; ++i) {
        int tp; cin >> tp;
        if (tp == 1) {
            int x; cin >> x; --x; qr[i] = {1, x};
            dis[eg[x][0]][eg[x][1]] = M;
            dis[eg[x][1]][eg[x][0]] = M;
        }
        else {
            int x, y; cin >> x >> y; qr[i] = {2, x, y};
        }
    }
    pre(); vector<int64_t> ans;
    for (i = q - 1; i >= 0; --i) {
        if (qr[i][0] == 2) {
            int x = qr[i][1], y = qr[i][2];
            if (dis[x][y] >= M) ans.push_back(-1);
            else ans.push_back(dis[x][y]);
        }
        else {
            int in = qr[i][1], a = eg[in][0], b = eg[in][1];
            int64_t c = eg[in][2]; add(a, b, c);
        }
    }
    for (i = ans.size() - 1; i >= 0; --i) cout << ans[i] << '\n';

// Distance: cout << (dis[a][b] == M ? -1 : dis[a][b]) << '\n';

// Johnson's algorithm for all pair shortest paths with negative edges
// Complexity: O(N * M) + O(N * M * log(N))

const int64_t INF = 1e18;

struct edge {
    int u, v;
    int64_t w;
    edge() {}
    edge(int u, int v, int64_t w) : u(u), v(v), w(w) {}
};

bool bellman_ford(int n, int s, vector<struct edge> ed, vector<int64_t> &d) {
    d[s] = 0;
    for (int i = 0; i <= n; i++) {
        int flag = 0;
        for (auto e : ed) {
            if (d[e.u] + e.w < d[e.v]) {
                flag = 1;
                d[e.v] = d[e.u] + e.w;
            }
        }
        if (flag == 0)
            return 1;
    }
    return 0;
}

vector<int64_t> dijkstra(int n, int s, vector<struct edge> ed, vector<int64_t> &h) {
    vector<pair<int, int64_t>> g[n + 1];
    priority_queue<pair<int64_t, int>, vector<pair<int64_t, int>>, greater<pair<int64_t, int>>> q;
    for (auto e : ed) {
        g[e.u].push_back({e.v, e.w + h[e.u] - h[e.v]});
    }
    vector<int64_t> d(n + 1, INF);
    vector<bool> vis(n + 1, 0);
    q.push({0, s});
    d[s] = 0;
    while (!q.empty()) {
        auto x = q.top();
        q.pop();
        int u = x.second;
        if (vis[u])
            continue;
        vis[u] = 1;
        for (auto e : g[u]) {
            int v = e.first;
            int64_t w = e.second;
            if (d[u] + w < d[v]) {
                d[v] = d[u] + w;
                q.push({d[v], v});
            }
        }
    }
    for (int i = 1; i <= n; i++)
        if (d[i] < INF)
            d[i] -= h[s] - h[i];
    return d;
}

int64_t ans[N][N];
int johnson(int n, vector<struct edge> ed) {
    vector<int64_t> potential(n + 1, INF);
    for (int i = 1; i <= n; i++)
        ed.push_back(edge(0, i, 0));
    if (bellman_ford(n, 0, ed, potential) == 0)
        return 0;
    cout << "yes\n\n";
    for (int i = 1; i <= n; i++) {
        if (i > 1)
            cout << ' ';
        cout << potential[i];
    }
    cout << ' ' << potential[0] << "\n\n";
    for (int i = 1; i <= n; i++)
        ed.pop_back();
    for (int i = 1; i <= n; i++) {
        vector<int64_t> d = dijkstra(n, i, ed, potential);
        for (int j = 1; j <= n; j++)
            ans[i][j] = d[j];
    }
    return 1;
}
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t, cs = 0;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<edge> ed;
        while (m--) {
            int u, v, w;
            cin >> u >> v >> w;
            ed.push_back({u, v, w});
        }
        cout << "graph " << ++cs << ' ';
        int ok = johnson(n, ed);
        if (!ok) {
            cout << "no\n";
            continue;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (j > 1)
                    cout << ' ';
                if (ans[i][j] < INF)
                    cout << ans[i][j];
                else
                    cout << "#";
            }
            cout << '\n';
        }
    }
    return 0;
}
// https://www.spoj.com/problems/JHNSN/
