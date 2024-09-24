// Complexity: O(V + E*log(V))
// Use: Used to determine the shortest distance between source and destination vertex
// Note: Does not work for negative (-ve) value of weights, use Bellman-Ford instead

vector<pair<int, long long>> gp[N];
bool vis[N];
long long path[N], dis[N];
void dij(int src)
{
    fill(dis, dis + N, LLONG_MAX);
    dis[src] = 0;
    set<pair<long long, int>> st;
    st.emplace(0, src);
    while (!st.empty())
    {
        int nd = (*st.top()).second;
        st.erase(st.top());
        Qif(vis[nd]) Qontinue;
        vis[nd] = true;
        for (auto &[cld, wt] : gp[nd])
        {
            if (dis[nd] + wt < dis[cld])
            {
                dis[cld] = dis[nd] + wt;
                st.emplace(dis[cld], cld);
                path[cld] = nd;
            }
        }
    }
}

// Opration:
int vr, eg;
cin >> vr >> eg;
for (i = 0; i < eg; ++i)
{
    long long v1, v2, wt;
    cin >> v1 >> v2 >> wt;
    gp[v1].emplace_back(v2, wt);
    gp[v2].emplace_back(v1, wt);
}
int src;
cin >> src;
dij(src);

// Printing the shortest distance of vertex vr:
cout << dis[vr] << '\n';

// Storing and printing the shortest path:
vector<int> v = {vr};
do
{
    vr = path[vr];
    if (!vr)
    {
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
for (i = 1; i <= m; ++i)
{
    int u, v, w;
    cin >> u >> v >> w;
    gp[u].push_back({v, w});
}
int cnt[n + 5]{};
multiset<pair<long long, int>> st;
st.emplace(0, 1);
while (!st.empty())
{
    auto [d, u] = *st.begin();
    st.erase(st.begin());
    if (++cnt[u] <= k and u == n)
        cout << d << ' ';
    if (cnt[u] <= k)
    {
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
vector<long long> dijkstra(int s, int t, vector<int> &cnt)
{
    const long long inf = 1e18;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;
    vector<long long> d(n + 1, inf);
    vector<bool> vis(n + 1, 0);
    q.push({0, s});
    d[s] = 0;
    cnt.resize(n + 1, 0); // number of shortest paths
    cnt[s] = 1;
    while (!q.empty())
    {
        auto x = q.top();
        q.pop();
        int u = x.second;
        if (vis[u])
            continue;
        vis[u] = 1;
        for (auto y : g[u])
        {
            int v = y.first;
            long long w = y.second;
            if (d[u] + w < d[v])
            {
                d[v] = d[u] + w;
                q.push({d[v], v});
                cnt[v] = cnt[u];
            }
            else if (d[u] + w == d[v])
                cnt[v] = (cnt[v] + cnt[u]) % mod;
        }
    }
    return d;
}

int u[N], v[N], w[N];
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int s, t;
    cin >> n >> m >> s >> t;
    for (int i = 1; i <= m; i++)
    {
        cin >> u[i] >> v[i] >> w[i];
        g[u[i]].push_back({v[i], w[i]});
        r[v[i]].push_back({u[i], w[i]});
    }
    vector<int> cnt1, cnt2;
    auto d1 = dijkstra(s, t, cnt1);
    auto d2 = dijkstra(t, s, cnt2);

    long long ans = d1[t];
    for (int i = 1; i <= m; i++)
    {
        int x = u[i], y = v[i];
        long long nw = d1[x] + w[i] + d2[y];
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

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9;

vector<pair<int, int>> g[N * 9];
inline void add_edge(int u, int v, int w)
{
    g[u].push_back({v, w});
}
int add;
void build(int n, int b, int e)
{
    if (b == e)
    {
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
void upd(int n, int b, int e, int i, int j, int dir, int u, int w)
{
    if (j < b || e < i)
        return;
    if (i <= b && e <= j)
    {
        if (dir)
            add_edge(u, n + 5 * add, w); // from u to this range
        else
            add_edge(n + add, u, w); // from this range to u
        return;
    }
    int mid = (b + e) >> 1;
    upd(2 * n, b, mid, i, j, dir, u, w);
    upd(2 * n + 1, mid + 1, e, i, j, dir, u, w);
}

vector<long long> dijkstra(int s)
{
    const long long inf = 1e18;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;
    vector<long long> d(9 * N + 1, inf);
    vector<bool> vis(9 * N + 1, 0);
    q.push({0, s});
    d[s] = 0;
    while (!q.empty())
    {
        auto x = q.top();
        q.pop();
        int u = x.second;
        if (vis[u])
            continue;
        vis[u] = 1;
        for (auto y : g[u])
        {
            int v = y.first;
            long long w = y.second;
            if (d[u] + w < d[v])
            {
                d[v] = d[u] + w;
                q.push({d[v], v});
            }
        }
    }
    return d;
}
long long ans[N];
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q, s;
    cin >> n >> q >> s;
    add = n;
    build(1, 1, n);
    while (q--)
    {
        int ty;
        cin >> ty;
        int u, l, r, w;
        if (ty == 1)
        {
            cin >> u >> l >> w;
            r = l;
        }
        else
        {
            cin >> u >> l >> r >> w;
        }
        upd(1, 1, n, l, r, ty <= 2, u, w);
    }
    auto ans = dijkstra(s);
    for (int i = 1; i <= n; i++)
    {
        if (ans[i] == 1e18)
            ans[i] = -1;
        cout << ans[i] << ' ';
    }
    return 0;
}
// https://codeforces.com/contest/786/problem/B

// Shortest Path tat does not pass through each edge:

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 9;
using ll = long long;
const ll inf = 1e18;
using T = pair<ll, int>;

vector<array<int, 3>> g[N];
ll d[N], rd[N], f[N];
vector<array<int, 2>> S[N], R[N]; // shortest path graph, reverse shortest path graph
bool sp_edge[N];                  // if edge is in the main shortest path
int path_id[N], l[N], r[N], u[N], v[N], w[N], edge[N];
vector<T> event[N];
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, Q;
    cin >> n >> m >> Q;
    for (int i = 1; i <= m; i++)
    {
        cin >> u[i] >> v[i] >> w[i];
        g[u[i]].push_back({v[i], w[i], i});
        g[v[i]].push_back({u[i], w[i], i});
    }
    priority_queue<T, vector<T>, greater<T>> q;
    for (int i = 1; i <= n; i++)
    {
        d[i] = inf;
    }
    d[1] = 0;
    q.push({0, 1});
    while (!q.empty())
    {
        auto [x, u] = q.top();
        q.pop();
        for (auto [v, w, i] : g[u])
        {
            if (d[u] + w < d[v])
            {
                d[v] = d[u] + w;
                edge[v] = i;
                q.push({d[v], v});
            }
        }
    }
    q = priority_queue<T, vector<T>, greater<T>>();
    for (int i = 1; i <= n; i++)
    {
        rd[i] = inf;
    }
    rd[n] = 0;
    q.push({0, n});
    while (!q.empty())
    {
        auto [x, u] = q.top();
        q.pop();
        for (auto [v, w, i] : g[u])
        {
            if (rd[u] + w < rd[v])
            {
                rd[v] = rd[u] + w;
                q.push({rd[v], v});
            }
        }
    }
    for (int u = 1; u <= n; u++)
    {
        for (auto [v, w, i] : g[u])
        {
            if (d[u] + w == d[v])
            {
                S[u].push_back({v, i});
            }
        }
        for (auto [v, w, i] : g[u])
        {
            if (rd[u] + w == rd[v])
            {
                R[u].push_back({v, i});
            }
        }
    }
    int cur = n;
    vector<int> path;
    while (cur != 1)
    {
        int i = edge[cur];
        path.push_back(i);
        sp_edge[i] = true;
        int up = cur ^ u[i] ^ v[i];
        cur = up;
    }
    reverse(path.begin(), path.end());
    for (int i = 0; i < path.size(); i++)
    {
        path_id[path[i]] = i;
    }

    vector<T> vec;
    for (int i = 1; i <= n; i++)
    {
        vec.push_back({d[i], i});
    }
    sort(vec.begin(), vec.end());
    for (int i = 1; i <= n; i++)
    {
        l[i] = path.size();
    }
    l[1] = -1;
    for (auto [_, u] : vec)
    {
        for (auto [v, i] : S[u])
        {
            if (sp_edge[i])
            {
                l[v] = min(l[v], path_id[i]);
            }
            else
            {
                l[v] = min(l[v], l[u]);
            }
        }
    }

    vec.clear();
    for (int i = 1; i <= n; i++)
    {
        vec.push_back({rd[i], i});
    }
    sort(vec.begin(), vec.end());
    for (int i = 1; i <= n; i++)
    {
        r[i] = -1;
    }
    r[n] = path.size();
    for (auto [_, u] : vec)
    {
        for (auto [v, i] : R[u])
        {
            if (sp_edge[i])
            {
                r[v] = max(r[v], path_id[i]);
            }
            else
            {
                r[v] = max(r[v], r[u]);
            }
        }
    }

    for (int u = 1; u <= n; u++)
    {
        for (auto [v, w, _] : g[u])
        {
            if (sp_edge[_])
                continue;
            ll cur = d[u] + rd[v] + w;
            if (l[u] + 1 <= r[v] - 1)
            {
                event[l[u] + 1].push_back({cur, +1});
                event[r[v] - 1 + 1].push_back({cur, -1});
            }
        }
    }
    multiset<ll> se;
    for (int i = 0; i < path.size(); i++)
    {
        for (auto [cur, add] : event[i])
        {
            if (add == 1)
            {
                se.insert(cur);
            }
            else
            {
                se.erase(se.find(cur));
            }
        }
        if (se.empty())
        {
            f[i] = inf;
        }
        else
        {
            f[i] = *se.begin();
        }
    }

    while (Q--)
    {
        int i, x;
        cin >> i >> x;

        ll ans = d[u[i]] + rd[v[i]] + x;
        ans = min(ans, d[v[i]] + rd[u[i]] + x);

        // shortest path from 1 to n that doesn't pass through edge i
        ll except_i = inf;
        if (sp_edge[i])
        {
            // for (int u = 1; u <= n; u++) {
            //   for (auto [v, w, _]: g[u]) {
            //     if (!sp_edge[_] and l[u] < path_id[i] and path_id[i] < r[v]) {
            //       except_i = min(except_i, d[u] + rd[v] + w);
            //     }
            //   }
            // }
            except_i = f[path_id[i]];
        }
        else
        {
            except_i = min(except_i, d[n]);
        }
        ans = min(ans, except_i);
        cout << ans << '\n';
    }
    return 0;
}
// https://codeforces.com/contest/1163/problem/F