// Complexity: O(E * V^2)
// Use: Used to determine the maximum flow from source to sink

long long ecnt = 1, eg, src, snk, head[N], dep[N], cur[N];
struct Edge { long long to, cap, next; } edge[N];
void add(auto from, auto to, auto cap) {
    edge[++ecnt].to = to; edge[ecnt].cap = cap;
    edge[ecnt].next = head[from]; head[from] = ecnt;
    edge[++ecnt].to = from; edge[ecnt].cap = 0;
    edge[ecnt].next = head[to]; head[to] = ecnt;
}
long long bfs() {
    queue<long long> q; q.emplace(src); dep[src] = 1;
    while (!q.empty()) {
        long long u = q.front(); q.pop();
        for (long long i = head[u]; i; i = edge[i].next) {
            long long v = edge[i].to;
            if (edge[i].cap > 0 && !dep[v]) {
                dep[v] = dep[u] + 1; q.emplace(v);
            }
        }
    }
    return dep[snk];
}
long long dinic(auto u, auto lim) {
    if (u == snk) return lim;
    long long flow = 0, i = cur[u];
    while(i) {
        long long v = edge[i].to;
        if (dep[v] == dep[u] + 1 && edge[i].cap > 0) {
            long long f = dinic(v, min(lim - flow, edge[i].cap));
            if (f) {
                edge[i].cap -= f; edge[i ^ 1].cap += f;
                flow += f; if (flow == lim) break;
            }
        }
        i = edge[i].next;
    }
    return flow;
}
auto mflo() {
    long long flow = 0;
    while (bfs()) {
        memcpy(cur, head, sizeof head);
        flow += dinic(src, LLONG_MAX);
        memset(dep, 0, sizeof dep);
    }
    return flow;
}

// Operation:
    cin >> eg >> src >> snk;
    for (i = 0; i < eg; ++i) {
        long long u, v, w; cin >> u >> v >> w;
        add(u, v, w);
    }
    cout << mflo();

// OR,

#include<bits/stdc++.h>
using namespace std;

const int N = 5010;

const long long inf = 1LL << 61;
struct Dinic {
  struct edge {
    int to, rev;
    long long flow, w;
    int id;
  };
  int n, s, t, mxid;
  vector<int> d, flow_through;
  vector<int> done;
  vector<vector<edge>> g;
  Dinic() {}
  Dinic(int _n) {
    n = _n + 10;
    mxid = 0;
    g.resize(n);
  }
  void add_edge(int u, int v, long long w, int id = -1) {
    edge a = {v, (int)g[v].size(), 0, w, id};
    edge b = {u, (int)g[u].size(), 0, 0, -2};//for bidirectional edges cap(b) = w
    g[u].emplace_back(a);
    g[v].emplace_back(b);
    mxid = max(mxid, id);
  }
  bool bfs() {
    d.assign(n, -1);
    d[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto &e : g[u]) {
        int v = e.to;
        if (d[v] == -1 && e.flow < e.w) d[v] = d[u] + 1, q.push(v);
      }
    }
    return d[t] != -1;
  }
  long long dfs(int u, long long flow) {
    if (u == t) return flow;
    for (int &i = done[u]; i < (int)g[u].size(); i++) {
      edge &e = g[u][i];
      if (e.w <= e.flow) continue;
      int v = e.to;
      if (d[v] == d[u] + 1) {
        long long nw = dfs(v, min(flow, e.w - e.flow));
        if (nw > 0) {
          e.flow += nw;
          g[v][e.rev].flow -= nw;
          return nw;
        }
      }
    }
    return 0;
  }
  long long max_flow(int _s, int _t) {
    s = _s;
    t = _t;
    long long flow = 0;
    while (bfs()) {
      done.assign(n, 0);
      while (long long nw = dfs(s, inf)) flow += nw;
    }
    flow_through.assign(mxid + 10, 0);
    for(int i = 0; i < n; i++) for(auto e : g[i]) if(e.id >= 0) flow_through[e.id] = e.flow;
    return flow;
  }
};
int main() {
  int n, m;
  cin >> n >> m;
  Dinic F(n + 1);
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    F.add_edge(u, v, w);
  }
  cout << F.max_flow(1, n) << '\n';
  return 0;
}

// OR,

struct FlowEdge {
    long long v, u, cap, flow = 0;
    FlowEdge(long long v, long long u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    const long long flow_inf = 1e18;
    vector<FlowEdge> edg; vector<vector<long long>> gp;
    long long n, m = 0, s, t;
    vector<long long> lvl, ptr; queue<long long> q;
    // number of nodes, source, sink
    Dinic(long long n, long long s, long long t) : n(n), s(s), t(t) {
        gp.resize(n + 100), lvl.resize(n + 100), ptr.resize(n + 100);
    }
    //directed edge from v  to u (not u to v)
    void add_edge(long long v, long long u, long long cap) {
        edg.emplace_back(v, u, cap); edg.emplace_back(u, v, 0);
        gp[v].push_back(m++); gp[u].push_back(m++);
    }
    bool bfs() {
        while (!q.empty()) {
            long long v = q.front();  q.pop();
            for (auto &id : gp[v]) {
                if (edg[id].cap - edg[id].flow < 1) continue;
                if (lvl[edg[id].u] != -1) continue;
                lvl[edg[id].u] = lvl[v] + 1, q.push(edg[id].u);
            }
        }
        return lvl[t] != -1;
    }
    long long dfs(long long v, long long pushed) {
        if (pushed == 0) return 0;
        if (v == t) return pushed;
        for (long long& cid = ptr[v]; cid < gp[v].size(); ++cid) {
            long long id = gp[v][cid], u = edg[id].u;
            if (lvl[v] + 1 != lvl[u] || edg[id].cap - edg[id].flow < 1) continue;
            long long tr = dfs(u, min(pushed, edg[id].cap - edg[id].flow));
            if (tr == 0) continue;
            edg[id].flow += tr, edg[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }
    long long flow() {
        long long f = 0;
        while (true) {
            fill(lvl.begin(), lvl.end(), -1);
            lvl[s] = 0, q.push(s); if (!bfs()) break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) f += pushed;
        }
        return f;
    }
};

/*
 **directed edge from v  to u (not u to v)
 ** to find matching edges go over all edges  where s!=u && s !=v && t!=u && t!=v and find flow of 1
*/