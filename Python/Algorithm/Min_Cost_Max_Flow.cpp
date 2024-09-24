// Min Cost Max Flow:

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

// Works for both directed, undirected and with negative cost too
// doesn't work for negative cycles
// for undirected edges just make the directed flag false
// Complexity: O(min(E^2 *V log V, E logV * flow))
using T = long long;
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
        return d[t] != inf; // for max flow min cost
                            // return d[t] <= 0; // for min cost flow
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
            // Run Bellman-Ford to find starting potential on the starting graph
            // If the starting graph (before pushing flow in the residual graph) is a DAG,
            // then this can be calculated in O(V + E) using DP:
            // potential(v) = min({potential[u] + cost[u][v]}) for each u -> v and potential[s] = 0
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
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    assert(n <= 10);
    MCMF F(2 * n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int k;
            cin >> k;
            F.add_edge(i, j + n, 1, k, i * 20 + j);
        }
    }
    int s = 2 * n + 1, t = s + 1;
    for (int i = 0; i < n; i++)
    {
        F.add_edge(s, i, 1, 0);
        F.add_edge(i + n, t, 1, 0);
    }
    auto ans = F.solve(s, t).second;
    long long w = 0;
    set<int> se;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int p = i * 20 + j;
            if (F.flow_through[p] > 0)
            {
                se.insert(j);
                w += F.flow_through[p];
            }
        }
    }
    assert(se.size() == n && w == n);
    cout << ans << '\n';
    return 0;
}

// Min Cost Max Flow with Negative Cycles:

// Push-Relabel implementation of the cost-scaling algorithm
// Runs in O( <max_flow> * log(V * max_edge_cost)) = O( V^3 * log(V * C))
// Really fast in practice, 3e4 edges are fine.
// Operates on integers, costs are multiplied by N!!

#include <bits/stdc++.h>
using namespace std;

// source: dacin21
template <typename flow_t = int, typename cost_t = int>
struct mcSFlow
{
    struct Edge
    {
        cost_t c;
        flow_t f;
        int to, rev;
        Edge(int _to, cost_t _c, flow_t _f, int _rev) : c(_c), f(_f), to(_to), rev(_rev) {}
    };
    static constexpr cost_t INFCOST = numeric_limits<cost_t>::max() / 2;
    cost_t eps;
    int N, S, T;
    vector<vector<Edge>> G;
    vector<unsigned int> isq, cur;
    vector<flow_t> ex;
    vector<cost_t> h;
    mcSFlow(int _N, int _S, int _T) : eps(0), N(_N), S(_S), T(_T), G(_N) {}
    void add_edge(int a, int b, cost_t cost, flow_t cap)
    {
        assert(cap >= 0);
        assert(a >= 0 && a < N && b >= 0 && b < N);
        if (a == b)
        {
            assert(cost >= 0);
            return;
        }
        cost *= N;
        eps = max(eps, abs(cost));
        G[a].emplace_back(b, cost, cap, G[b].size());
        G[b].emplace_back(a, -cost, 0, G[a].size() - 1);
    }
    void add_flow(Edge &e, flow_t f)
    {
        Edge &back = G[e.to][e.rev];
        if (!ex[e.to] && f)
            hs[h[e.to]].push_back(e.to);
        e.f -= f;
        ex[e.to] += f;
        back.f += f;
        ex[back.to] -= f;
    }
    vector<vector<int>> hs;
    vector<int> co;
    flow_t max_flow()
    {
        ex.assign(N, 0);
        h.assign(N, 0);
        hs.resize(2 * N);
        co.assign(2 * N, 0);
        cur.assign(N, 0);
        h[S] = N;
        ex[T] = 1;
        co[0] = N - 1;
        for (auto &e : G[S])
            add_flow(e, e.f);
        if (hs[0].size())
            for (int hi = 0; hi >= 0;)
            {
                int u = hs[hi].back();
                hs[hi].pop_back();
                while (ex[u] > 0)
                { // discharge u
                    if (cur[u] == G[u].size())
                    {
                        h[u] = 1e9;
                        for (unsigned int i = 0; i < G[u].size(); ++i)
                        {
                            auto &e = G[u][i];
                            if (e.f && h[u] > h[e.to] + 1)
                            {
                                h[u] = h[e.to] + 1, cur[u] = i;
                            }
                        }
                        if (++co[h[u]], !--co[hi] && hi < N)
                            for (int i = 0; i < N; ++i)
                                if (hi < h[i] && h[i] < N)
                                {
                                    --co[h[i]];
                                    h[i] = N + 1;
                                }
                        hi = h[u];
                    }
                    else if (G[u][cur[u]].f && h[u] == h[G[u][cur[u]].to] + 1)
                        add_flow(G[u][cur[u]], min(ex[u], G[u][cur[u]].f));
                    else
                        ++cur[u];
                }
                while (hi >= 0 && hs[hi].empty())
                    --hi;
            }
        return -ex[S];
    }
    void push(Edge &e, flow_t amt)
    {
        if (e.f < amt)
            amt = e.f;
        e.f -= amt;
        ex[e.to] += amt;
        G[e.to][e.rev].f += amt;
        ex[G[e.to][e.rev].to] -= amt;
    }
    void relabel(int vertex)
    {
        cost_t newHeight = -INFCOST;
        for (unsigned int i = 0; i < G[vertex].size(); ++i)
        {
            Edge const &e = G[vertex][i];
            if (e.f && newHeight < h[e.to] - e.c)
            {
                newHeight = h[e.to] - e.c;
                cur[vertex] = i;
            }
        }
        h[vertex] = newHeight - eps;
    }
    static constexpr int scale = 2;
    pair<flow_t, cost_t> minCostMaxFlow()
    {
        cost_t retCost = 0;
        for (int i = 0; i < N; ++i)
            for (Edge &e : G[i])
                retCost += e.c * (e.f);
        // find max-flow
        flow_t retFlow = max_flow();
        h.assign(N, 0);
        ex.assign(N, 0);
        isq.assign(N, 0);
        cur.assign(N, 0);
        queue<int> q;
        for (; eps; eps >>= scale)
        {
            // refine
            fill(cur.begin(), cur.end(), 0);
            for (int i = 0; i < N; ++i)
                for (auto &e : G[i])
                    if (h[i] + e.c - h[e.to] < 0 && e.f)
                        push(e, e.f);
            for (int i = 0; i < N; ++i)
            {
                if (ex[i] > 0)
                {
                    q.push(i);
                    isq[i] = 1;
                }
            }
            // make flow feasible
            while (!q.empty())
            {
                int u = q.front();
                q.pop();
                isq[u] = 0;
                while (ex[u] > 0)
                {
                    if (cur[u] == G[u].size())
                        relabel(u);
                    for (unsigned int &i = cur[u], max_i = G[u].size(); i < max_i; ++i)
                    {
                        Edge &e = G[u][i];
                        if (h[u] + e.c - h[e.to] < 0)
                        {
                            push(e, ex[u]);
                            if (ex[e.to] > 0 && isq[e.to] == 0)
                            {
                                q.push(e.to);
                                isq[e.to] = 1;
                            }
                            if (ex[u] == 0)
                                break;
                        }
                    }
                }
            }
            if (eps > 1 && eps >> scale == 0)
            {
                eps = 1 << scale;
            }
        }
        for (int i = 0; i < N; ++i)
        {
            for (Edge &e : G[i])
            {
                retCost -= e.c * (e.f);
            }
        }
        return make_pair(retFlow, retCost / 2 / N);
    }
    flow_t getFlow(Edge const &e)
    {
        return G[e.to][e.rev].f;
    }
};