// Complexity:
// Work: Checks if there is any cycle in the graph

vector<long long> gp[N]; bool vis[N];
bool dfs(auto rt, auto par) {
    vis[rt] = true; bool loop = false;
    for (auto &cld : gp[rt]) {
        if (vis[cld] && cld == par) continue;
        if (vis[cld]) return true;
        loop |= dfs(cld, rt);
    }
    return loop;
}
bool cycle(auto v) {
    bool loop = false;
    for (int i = 1; i <= v; ++i) {
        if (vis[i]) continue;
        if (dfs(i, -1)) return true;
    }
    return loop;
}

// Operation:
    long long eg, vr; cin >> eg >> vr;
    for (i = 0; i < eg; ++i) {
        long long v1, v2; cin >> v1 >> v2;
        gp[v1].emplace_back(v2); gp[v2].emplace_back(v1);
    }

// OR,

vector<long long> adj[N];
long long par[N], st, en, vis[N];

void dfs(long long u, long long p = 0) {
    if (st) return;
    for (auto &v : adj[u]) {
        if (vis[v] == 0) {
            par[v] = u; vis[v] = true;
            dfs(v, u); if (st) return;
        }
        else if (vis[v] == 1) {
            st = v, en = u; return;
        }
    }
    vis[u] = 2;
}

// Operation:
    cin >> n >> m;
    for (i = 1; i <= m; ++i) {
        long long u, v; cin >> u >> v;
        adj[u].push_back(v);
    }
    for (i = 1; i <= n; ++i) {
        if (st) break;
        if (vis[i] == 1) continue;
        vis[i] = true; dfs(i);
    }
    long long cur = en; vector<long long> ans;
    while (cur) {
        ans.push_back(cur);
        if (cur == st) break; cur = par[cur];
    }
    if (ans.empty()) cout << "IMPOSSIBLE" << '\n';
    else {
        ans.push_back(ans[0]);
        cout << ans.size() << '\n';
        reverse(ans.begin(), ans.end());
        for (auto &e : ans) cout << e << ' ';
        cout << '\n';
    }

// Cycle in Directed Graph:

vector<long long> adj[N]; long long par[N], st, en; bool vis[N];
void dfs(long long u, long long p = 0) {
    if (st) return;
    for (auto &v : adj[u]) {
        if (vis[v] == 0) {
            par[v] = u, vis[v] = true;
            dfs(v, u); if (st) return;
        }
        else if (vis[v]) {
            st = v, en = u; return;
        }
    }
    vis[u] = 2;  // marked as a visited component
}

// Operation:
    cin >> n >> m;
    for (i = 1; i <= m; ++i) {
        long long u, v; cin >> u >> v;
        adj[u].push_back(v);
    }
    for (i = 1; i <= n; ++i) {
        if (st) break;
        if (vis[i] == 1) continue;
        vis[i] = true; dfs(i);
    }
    long long cur = en; vector<long long> ans;
    while (cur) {
        ans.push_back(cur);
        if (cur == st) break;
        cur = par[cur];
    }
    if (ans.empty()) cout << "NO cycle detected" << '\n';
    else {
        ans.push_back(ans[0]);
        cout << ans.size() << '\n';
        reverse(ans.begin(), ans.end());
        for (auto &e : ans) cout << e << ' ';
        cout << '\n';
    }

// OR, Cycle Detection:

#include<bits/stdc++.h>
using namespace std;

const int N = 5e5 + 9;

vector<pair<int, int>> g[N];
int vis[N], par[N], e_id[N];
vector<int> cycle; // simple cycle, contains edge ids

bool dfs(int u) {
  if (!cycle.empty()) return 1;
  vis[u] = 1;
  for (auto [v, id] : g[u]) {
    if (v != par[u]) {
      if (vis[v] == 0) {
        par[v] = u;
        e_id[v] = id;
        if (dfs(v)) return 1;
      }
      else if (vis[v] == 1) {
        // cycle here
        cycle.push_back(id);
        for (int x = u; x != v; x = par[x]) {
          cycle.push_back(e_id[x]);
        }
        return 1;
      }
    }
  }
  vis[u] = 2;
  return 0;
}

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, m; cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int u, v; cin >> u >> v;
    ++u; ++v;
    g[u].push_back({v, i});
  }
  for (int u = 1; u <= n; u++) {
    if (vis[u] == 0 and dfs(u)) {
      cout << cycle.size() << '\n';
      for (auto x: cycle) cout << x - 1 << '\n';
      return 0;
    }
  }
  cout << -1 << '\n';
  return 0;
}
// https://judge.yosupo.jp/problem/cycle_detection