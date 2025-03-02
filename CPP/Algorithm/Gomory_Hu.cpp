// Gomory Hu Tree:

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

const int64_t inf = 1LL << 61;
struct Dinic
{
    struct edge
    {
        int to, rev;
        int64_t flow, w;
        int id;
    };
    int n, s, t, mxid;
    vector<int> d, flow_through;
    vector<int> done;
    vector<vector<edge>> g;
    Dinic() {}
    Dinic(int _n)
    {
        n = _n + 10;
        mxid = 0;
        g.resize(n);
    }
    void add_edge(int u, int v, int64_t w, int id = -1)
    {
        edge a = {v, (int)g[v].size(), 0, w, id};
        edge b = {u, (int)g[u].size(), 0, w, -2}; // for bidirectional edges cap(b) = w
        g[u].emplace_back(a);
        g[v].emplace_back(b);
        mxid = max(mxid, id);
    }
    bool bfs()
    {
        d.assign(n, -1);
        d[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (auto &e : g[u])
            {
                int v = e.to;
                if (d[v] == -1 && e.flow < e.w)
                    d[v] = d[u] + 1, q.push(v);
            }
        }
        return d[t] != -1;
    }
    int64_t dfs(int u, int64_t flow)
    {
        if (u == t)
            return flow;
        for (int &i = done[u]; i < (int)g[u].size(); i++)
        {
            edge &e = g[u][i];
            if (e.w <= e.flow)
                continue;
            int v = e.to;
            if (d[v] == d[u] + 1)
            {
                int64_t nw = dfs(v, min(flow, e.w - e.flow));
                if (nw > 0)
                {
                    e.flow += nw;
                    g[v][e.rev].flow -= nw;
                    return nw;
                }
            }
        }
        return 0;
    }
    int64_t max_flow(int _s, int _t)
    {
        s = _s;
        t = _t;
        int64_t flow = 0;
        while (bfs())
        {
            done.assign(n, 0);
            while (int64_t nw = dfs(s, inf))
                flow += nw;
        }
        flow_through.assign(mxid + 10, 0);
        for (int i = 0; i < n; i++)
            for (auto e : g[i])
                if (e.id >= 0)
                    flow_through[e.id] = e.flow;
        return flow;
    }
};

/*For a given weighted graph, int the Gomory-Hu tree the maximum flow
between vertices u and v in the tree(i.e. minimum edge from u to v)
is equal to the maximum flow in the graph.*/
struct edge
{
    int u, v;
    int64_t w;
};
// all nodes are from 1 to n
// returns edges of the gomory hu tree
vector<edge> gomory_hu_tree(int n, vector<edge> &ed)
{
    vector<edge> ans;
    vector<int> par(n + 1, 1);
    for (int i = 2; i <= n; i++)
    {
        Dinic F(n + 1);
        for (auto &e : ed)
            F.add_edge(e.u, e.v, e.w);
        int s = i, t = par[i];
        ans.push_back({s, t, F.max_flow(s, t)});
        for (int j = i + 1; j <= n; j++)
        {
            if (F.d[j] != -1 and par[j] == par[i])
            {
                par[j] = i;
            }
        }
    }
    return ans;
}

struct dsu
{
    vector<int> par, rank, size;
    int c;
    dsu(int n) : par(n + 1), rank(n + 1, 0), size(n + 1, 1), c(n)
    {
        for (int i = 1; i <= n; ++i)
            par[i] = i;
    }
    int find(int i)
    {
        return (par[i] == i ? i : (par[i] = find(par[i])));
    }
    bool same(int i, int j)
    {
        return find(i) == find(j);
    }
    int get_size(int i)
    {
        return size[find(i)];
    }
    int count()
    {
        return c;
    }
    int merge(int i, int j)
    {
        if ((i = find(i)) == (j = find(j)))
            return -1;
        else
            --c;
        if (rank[i] > rank[j])
            swap(i, j);
        par[i] = j;
        size[j] += size[i];
        if (rank[i] == rank[j])
            rank[j]++;
        return j;
    }
};

// find a permutation such that sum of max flow(p[i],p[i+1]) is maximum
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<edge> ed(m);
    for (edge &e : ed)
        cin >> e.u >> e.v >> e.w;
    auto t = gomory_hu_tree(n, ed);
    sort(t.begin(), t.end(), [](const edge &l, const edge &r)
         { return l.w > r.w; });
    dsu d(n);
    vector<vector<int>> perm(n + 1);
    int64_t ans = 0LL;
    for (int i = 1; i <= n; ++i)
        perm[i].push_back(i);
    for (const auto &e : t)
    {
        int l = d.find(e.u), r = d.find(e.v);
        if (l != d.merge(l, r))
            swap(l, r);
        ans += e.w;
        for (int j : perm[r])
            perm[l].push_back(j);
        perm[r].clear();
    }
    cout << ans << endl;
    for (int i = 0; i < n; ++i)
        cout << perm[d.find(1)][i] << " \n"[i + 1 == n];
    return 0;
}
// https://codeforces.com/contest/343/problem/E

// Gomory Hu Tree of Planar Graph:

#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
const int mod = 998244353;
struct EDGE
{
    int from, to, rev;
    int64_t w;
} E[N * 4];
int n, m, bel[N * 4];
bool vis[N * 4];
vector<int> G[N];
vector<vector<int>> plr;
set<pair<int64_t, int>> st;
vector<pair<pair<int, int>, int64_t>> tr;
int fa[N], sz[N];
int Find(int x)
{
    return x == fa[x] ? x : fa[x] = Find(fa[x]);
}
// credit: Misaka-Mikoto-
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d%lld", &E[i * 2].from, &E[i * 2].to, &E[i * 2].w);
        E[i * 2].from--, E[i * 2].to--;
        E[i * 2 + 1] = E[i * 2];
        swap(E[i * 2 + 1].from, E[i * 2 + 1].to);
    }
    for (int i = 0; i < m * 2; i++)
    {
        G[E[i].from].push_back(i);
        if ((E[i].from + 1) % n == E[i].to)
            vis[i] = true;
        else
            vis[i] = false;
    }
    for (int i = 0; i < n; i++)
    {
        sort(G[i].begin(), G[i].end(), [&](int e1, int e2)
             { return (E[e1].to - i + n) % n < (E[e2].to - i + n) % n; });
        for (int j = 0; j < (int)G[i].size(); j++)
        {
            int e = G[i][j];
            E[e ^ 1].rev = j;
        }
    }
    for (int i = 0; i < m * 2; i++)
        if (!vis[i])
        {
            int e = i;
            vector<int> ve;
            while (!vis[e])
            {
                ve.push_back(e);
                vis[e] = true;
                int v = E[e].to;
                int ne = G[v][(E[e].rev + 1) % G[v].size()];
                e = ne;
            }
            plr.push_back(ve);
            for (int x : ve)
                bel[x] = plr.size() - 1;
        }
    for (int i = 0; i < m * 2; i++)
    {
        if ((E[i].from + 1) % n == E[i].to)
            vis[i] = true;
        else
            vis[i] = false;
    }
    for (int i = 0; i < m; i++)
    {
        int x = E[i * 2].from, y = E[i * 2].to;
        if ((x + 1) % n == y || (y + 1) % n == x)
        {
            st.insert(make_pair(E[i * 2].w, i));
        }
    }
    while (!st.empty())
    {
        int e = st.begin()->second;
        st.erase(st.begin());
        if (vis[e * 2] && vis[e * 2 + 1])
        {
            tr.push_back(make_pair(make_pair(E[e * 2].from, E[e * 2].to), E[e * 2].w));
            continue;
        }
        if (!vis[e * 2])
            e *= 2;
        else
            e = e * 2 + 1;
        int b = bel[e];
        for (int x : plr[b])
        {
            vis[x] = true;
            if (x == e)
                continue;
            st.erase(make_pair(E[x].w, x >> 1));
            E[x].w += E[e].w;
            E[x ^ 1].w += E[e].w;
            st.insert(make_pair(E[x].w, x >> 1));
        }
    }
    reverse(tr.begin(), tr.end()); // edges of GHT
    int ans = 0;
    for (int i = 0; i < n; i++)
        fa[i] = i, sz[i] = 1;
    for (int i = 0; i < n - 1; i++)
    {
        int x = Find(tr[i].first.first), y = Find(tr[i].first.second), w = tr[i].second % mod;
        ans = (ans + 1ll * sz[x] * sz[y] % mod * w) % mod;
        if (sz[x] < sz[y])
            swap(x, y);
        fa[y] = x;
        sz[x] += sz[y];
    }
    printf("%d\n", ans);
    return 0;
}
// https://codeforces.com/gym/102471/submission/71744464