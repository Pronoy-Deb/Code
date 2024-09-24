// Complexity: O(V * E)
// Use: Used to determine the shortest distance between source and destination vertex
// Note: Works for negative (-ve) value of weights

bool bmf(auto src, auto &grp, auto &dis) {
    long long V = dis.size(); dis[src] = 0; bool updated;
    do {
        updated = false;
        priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> pq;
        for (int u = 0; u < V; ++u)
            if (dis[u] != LONG_LONG_MAX) pq.emplace(dis[u], u);
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            for (auto &[v, w] : grp[u]) {
                if (dis[u] + w < dis[v]) {
                    dis[v] = dis[u] + w; pq.emplace(dis[v], v); updated = true;
                }
                if (dis[u] != LONG_LONG_MAX && dis[u] + w < dis[v]) return true;
            }
        }
    } while (updated);
    return false;
}

// Operation:
    long long vr, eg; cin >> vr >> eg;
    vector<vector<pair<long long, long long>>> grp(vr + 50);
    vector<long long> dis(vr + 5, LLONG_MAX);
    for (i = 0; i < eg; ++i) {
        long long u, v, w; cin >> u >> v >> w;
        grp[u].emplace_back(v, w);
    }
    long long src; cin >> src;  // specify the source
    if(bmf(src, grp, dis)) { cout << -1 << '\n'; return; } // checking negative cycle
    for (i = 0; i < vr; ++i)  // Vertex distance from Source Vertex
        cout << dis[i] << '\n';

            // OR, Problem: https://cses.fi/problemset/task/1197

    cin >> n >> m;
    vector<tuple<int, int, int>> gp;
    for (i = 1; i <= m; ++i) {
        int u, v, w; cin >> u >> v >> w; gp.emplace_back(u, v, w);
    }
    long long dis[n + 5], par[n + 5];
    fill(dis, dis + n + 5, M * M); int lst; dis[1] = 0;
    for (i = 0; i < n; ++i) {
        lst = -1;
        for (auto &[u, v, w] : gp) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w; par[v] = u; lst = v;
            }
        }
    }
    if (lst == -1) cout << "NO";
    else {
        while (n--) lst = par[lst];
        cout << "YES" << '\n'; vector<int> nc;
        for (int cur = lst; ; cur = par[cur]) {
            nc.push_back(cur);
            if (cur == lst && nc.size() > 1) break;
        }
        for (i = nc.size() - 1; i >= 0; --i) cout << nc[i] << ' ';
    }

                                    // OR,

#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

struct st {
  int a, b, cost;
} e[N];
const int INF = 2e9;
int32_t main() {
  int n, m;
  cin >> n >> m;
  for(int i = 0; i < m; i++) cin >> e[i].a >> e[i].b >> e[i].cost;
  int s;
  cin >> s;//is there any negative cycle which is reachable from s?
  vector<int> d (n, INF);//for finding any cycle(not necessarily from s) set d[i] = 0 for all i
  d[s] = 0;
  vector<int> p (n, -1);
  int x;
  for (int i=0; i<n; ++i) {
    x = -1;
    for (int j=0; j<m; ++j) {
      if (d[e[j].a] < INF) {
        if (d[e[j].b] > d[e[j].a] + e[j].cost) {
          d[e[j].b] = max (-INF, d[e[j].a] + e[j].cost);//for overflow
          p[e[j].b] = e[j].a;
          x = e[j].b;
        }
      }
    }
  }
  if (x == -1) cout << "No negative cycle from "<<s;
  else {
    int y = x; //x can be on any cycle or reachable from some cycle
    for (int i=0; i<n; ++i) y = p[y];

    vector<int> path;
    for (int cur=y; ; cur=p[cur]) {
      path.push_back (cur);
      if (cur == y && path.size() > 1) break;
    }
    reverse (path.begin(), path.end());

    cout << "Negative cycle: ";
    for (int i=0; i<path.size(); ++i) cout << path[i] << ' ';
  }
  return 0;
}