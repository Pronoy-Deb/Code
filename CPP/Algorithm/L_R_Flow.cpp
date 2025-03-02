// L R Flow with Dinic's Algorithm:

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
        edge b = {u, (int)g[u].size(), 0, 0, -1}; // for bidirectional edges cap(b) = w
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
// flow_through[i] = extra flow beyond 'low' sent through edge i
struct LR_Flow
{
    Dinic F;
    int n, s, t;
    struct edge
    {
        int u, v, l, r, id;
    };
    vector<edge> edges;
    LR_Flow() {}
    LR_Flow(int _n)
    {
        n = _n + 10;
        s = n - 2, t = n - 1;
        ;
        edges.clear();
    }
    void add_edge(int u, int v, int l, int r, int id = -1)
    {
        assert(0 <= l && l <= r);
        edges.push_back({u, v, l, r, id});
    }
    bool feasible(int _s = -1, int _t = -1, int L = -1, int R = -1)
    {
        if (L != -1)
            edges.push_back({_t, _s, L, R, -1});
        F = Dinic(n);
        int64_t target = 0;
        for (auto e : edges)
        {
            int u = e.u, v = e.v, l = e.l, r = e.r, id = e.id;
            if (l != 0)
            {
                F.add_edge(s, v, l);
                F.add_edge(u, t, l);
                target += l;
            }
            F.add_edge(u, v, r - l, id);
        }
        auto ans = F.max_flow(s, t);
        if (L != -1)
            edges.pop_back();
        if (ans < target)
            return 0; // not feasible
        return 1;
    }
    int max_flow(int _s, int _t)
    { //-1 means flow is not feasible
        int mx = 1e5 + 9;
        if (!feasible(_s, _t, 0, mx))
            return -1;
        return F.max_flow(_s, _t);
    }
    int min_flow(int _s, int _t)
    { //-1 means flow is not feasible
        int mx = 1e9;
        int ans = -1, l = 0, r = mx;
        while (l <= r)
        {
            int mid = l + r >> 1;
            if (feasible(_s, _t, 0, mid))
                ans = mid, r = mid - 1;
            else
                l = mid + 1;
        }
        return ans;
    }
};
int get_id(map<int, int> &mp, int k)
{
    if (mp.find(k) == mp.end())
        mp[k], mp[k] = mp.size();
    return mp[k];
}
int Lx[N], Rx[N], Ly[N], Ry[N], degx[N], degy[N];
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    LR_Flow F(2 * n + 10);
    int r, b;
    cin >> r >> b;
    int sp = r > b;
    if (sp)
        swap(r, b);
    map<int, int> mx, my;
    for (int i = 1; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        if (sp)
            swap(x, y);
        F.add_edge(get_id(mx, x), get_id(my, y) + n, 0, 1, i);
        degx[mx[x]]++;
        degy[my[y]]++;
    }
    for (int i = 1; i <= mx.size(); i++)
        Lx[i] = 0, Rx[i] = degx[i];
    for (int i = 1; i <= my.size(); i++)
        Ly[i] = 0, Ry[i] = degy[i];
    while (m--)
    {
        int ty, x, d;
        cin >> ty >> x >> d;
        ty--;
        ty ^= sp;
        if (ty == 0)
        {
            if (mx.find(x) != mx.end())
            {
                int i = mx[x];
                int p = degx[i];
                int l = (p - d + 1) / 2, r = (p + d) / 2;
                l = max(0, l);
                r = min(p, r);
                Lx[i] = max(Lx[i], l);
                Rx[i] = min(Rx[i], r);
            }
        }
        else
        {
            if (my.find(x) != my.end())
            {
                int i = my[x];
                int p = degy[i];
                int l = (p - d + 1) / 2, r = (p + d) / 2;
                l = max(0, l);
                r = min(p, r);
                Ly[i] = max(Ly[i], l);
                Ry[i] = min(Ry[i], r);
            }
        }
    }
    int s = 2 * n + 2, t = s + 1;
    for (int i = 1; i <= mx.size(); i++)
    {
        if (Lx[i] > Rx[i])
            return cout << -1 << '\n', 0;
        F.add_edge(s, i, Lx[i], Rx[i]);
    }
    for (int i = 1; i <= my.size(); i++)
    {
        if (Ly[i] > Ry[i])
            return cout << -1 << '\n', 0;
        F.add_edge(i + n, t, Ly[i], Ry[i]);
    }
    int c = F.max_flow(s, t);
    if (c == -1)
        return cout << -1 << '\n', 0;
    int64_t ans = 1LL * c * r + 1LL * (n - c) * b;
    cout << ans << '\n';
    for (int i = 1; i <= n; i++)
    {
        cout << "br"[F.F.flow_through[i] ^ sp];
    }
    cout << '\n';
    return 0;
}
// https://codeforces.com/contest/704/problem/D

// L R Flow with MCMF:

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

// Works for both directed, undirected and with negative cost too
// doesn't work for negative cycles
// for undirected edges just make the directed flag false
// Complexity: O(min(E^2 * V log V, E logV * flow))
using T = int64_t;
const T inf = 1LL << 61;
struct MCMF
{
    struct edge
    {
        int u, v;
        T cap, cost;
        int id;
        edge(int _u, int _v, T _cap, T _cost, int _id)
        {
            u = _u;
            v = _v;
            cap = _cap;
            cost = _cost;
            id = _id;
        }
    };
    int n, s, t, mxid;
    T flow, cost;
    vector<vector<int>> g;
    vector<edge> e;
    vector<T> d, potential, flow_through;
    vector<int> par;
    bool neg;
    MCMF() {}
    MCMF(int _n)
    { // 0-based indexing
        n = _n + 10;
        g.assign(n, vector<int>());
        neg = false;
        mxid = 0;
    }
    void add_edge(int u, int v, T cap, T cost, int id = -1, bool directed = true)
    {
        if (cost < 0)
            neg = true;
        g[u].push_back(e.size());
        e.push_back(edge(u, v, cap, cost, id));
        g[v].push_back(e.size());
        e.push_back(edge(v, u, 0, -cost, -1));
        mxid = max(mxid, id);
        if (!directed)
            add_edge(v, u, cap, cost, -1, true);
    }
    bool dijkstra()
    {
        par.assign(n, -1);
        d.assign(n, inf);
        priority_queue<pair<T, T>, vector<pair<T, T>>, greater<pair<T, T>>> q;
        d[s] = 0;
        q.push(pair<T, T>(0, s));
        while (!q.empty())
        {
            int u = q.top().second;
            T nw = q.top().first;
            q.pop();
            if (nw != d[u])
                continue;
            for (int i = 0; i < (int)g[u].size(); i++)
            {
                int id = g[u][i];
                int v = e[id].v;
                T cap = e[id].cap;
                T w = e[id].cost + potential[u] - potential[v];
                if (d[u] + w < d[v] && cap > 0)
                {
                    d[v] = d[u] + w;
                    par[v] = id;
                    q.push(pair<T, T>(d[v], v));
                }
            }
        }
        for (int i = 0; i < n; i++)
        {
            if (d[i] < inf)
                d[i] += (potential[i] - potential[s]);
        }
        for (int i = 0; i < n; i++)
        {
            if (d[i] < inf)
                potential[i] = d[i];
        }
        // return d[t] != inf; // for max flow min cost
        return d[t] <= 0; // for min cost flow
    }
    T send_flow(int v, T cur)
    {
        if (par[v] == -1)
            return cur;
        int id = par[v];
        int u = e[id].u;
        T w = e[id].cost;
        T f = send_flow(u, min(cur, e[id].cap));
        cost += f * w;
        e[id].cap -= f;
        e[id ^ 1].cap += f;
        return f;
    }
    // returns {maxflow, mincost}
    pair<T, T> solve(int _s, int _t, T goal = inf)
    {
        s = _s;
        t = _t;
        flow = 0, cost = 0;
        potential.assign(n, 0);
        if (neg)
        {
            // run Bellman-Ford to find starting potential
            d.assign(n, inf);
            d[s] = 0;
            bool relax = true;
            for (int i = 0; i < n && relax; i++)
            {
                relax = false;
                for (int u = 0; u < n; u++)
                {
                    for (int k = 0; k < (int)g[u].size(); k++)
                    {
                        int id = g[u][k];
                        int v = e[id].v;
                        T cap = e[id].cap, w = e[id].cost;
                        if (d[v] > d[u] + w && cap > 0)
                        {
                            d[v] = d[u] + w;
                            relax = true;
                        }
                    }
                }
            }
            for (int i = 0; i < n; i++)
                if (d[i] < inf)
                    potential[i] = d[i];
        }
        while (flow < goal && dijkstra())
            flow += send_flow(t, goal - flow);
        flow_through.assign(mxid + 10, 0);
        for (int u = 0; u < n; u++)
        {
            for (auto v : g[u])
            {
                if (e[v].id >= 0)
                    flow_through[e[v].id] = e[v ^ 1].cap;
            }
        }
        return make_pair(flow, cost);
    }
};
// flow_through[i] = extra flow beyond 'low' sent through edge i
// it finds the feasible solution with minimum cost
struct LR_Flow
{
    MCMF F;
    static const T INF = 1e12;
    // sum of cost should be < INF / 2
    // flow * INF must not overflow in data type
    int n;
    T target;
    LR_Flow() {}
    LR_Flow(int _n)
    {
        n = _n + 10;
        target = 0;
        F = MCMF(n);
    }
    void add_edge(int u, int v, T l, T r, T cost = 0, int id = -1, bool directed = true)
    {
        assert(0 <= l && l <= r);
        target += l;
        F.add_edge(u, v, l, -INF + cost, -1, directed); // will try to take this edge first
        F.add_edge(u, v, r - l, cost, id, directed);
    }
    pair<T, T> solve(int s, int t, T goal = inf)
    {
        auto ans = F.solve(s, t, goal);
        ans.second += INF * target;
        if (abs(ans.second) >= INF / 2)
            return {-1, -1}; // not feasible
        return ans;
    }
};

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n1, n2, m, r, b;
    cin >> n1 >> n2 >> m >> r >> b;
    string s1, s2;
    cin >> s1 >> s2;
    int s = n1 + n2 + 10, t = s + 1;
    LR_Flow F(t);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        F.add_edge(u, v + n1, 0, 1, r, i);
        F.add_edge(v + n1, u, 0, 1, b, i + m);
    }
    for (int i = 0; i < n1; i++)
    {
        if (s1[i] == 'R')
            F.add_edge(s, i, 1, inf, 0);
        else if (s1[i] == 'B')
            F.add_edge(i, t, 1, inf, 0);
        else
            F.add_edge(s, i, 0, inf, 0), F.add_edge(i, t, 0, inf, 0);
    }
    for (int i = 0; i < n2; i++)
    {
        if (s2[i] == 'B')
            F.add_edge(s, i + n1, 1, inf, 0);
        else if (s2[i] == 'R')
            F.add_edge(i + n1, t, 1, inf, 0);
        else
            F.add_edge(s, i + n1, 0, inf, 0), F.add_edge(i + n1, t, 0, inf, 0);
    }
    auto ans = F.solve(s, t);
    if (ans.first == -1)
        cout << -1 << '\n';
    else
    {
        cout << ans.second << '\n';
        for (int i = 0; i < m; i++)
        {
            if (F.F.flow_through[i])
                cout << "R";
            else if (F.F.flow_through[i + m])
                cout << "B";
            else
                cout << "U";
        }
        cout << '\n';
    }
    return 0;
}
// https://codeforces.com/contest/1288/problem/F