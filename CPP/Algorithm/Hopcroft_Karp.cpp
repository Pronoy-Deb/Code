/**
    Hopcroft Karp Bipartite Matching Algorithm
    Complexity: E sqrt(V)   (much better in practice)
    Source: Foreverbell ICPC cheat sheet
    1-indexed. Left and Right independently numbered.
    ml, mr contain matches for left and right parts.

    1. You may pre-calculate a greedy-matching to speed up further
    2. In order to convert to Kuhn remove bfs in matching()
       and (lvl[u] < lvl[v]) condition in dfs()

    Source: Folklore, Anachor
*/
#include <bits/stdc++.h>
using namespace std;

namespace HopcroftKarp {
    const int64_t maxN = 1e5 + 7, maxM = 1e5 + 7;     ///Check
    int64_t n, m, match, lvl[maxN], ml[maxN], mr[maxM]; bool vis[maxN];
    vector<int64_t> edge[maxN];   /// constructing edges for left part only
    void init(int N, int M) {      /// N = nodes in left part, M = nodes in right part
        n = N, m = M;
        for (int i = 1; i <= n; ++i) edge[i].clear(), ml[i] = -1;
        for (int i = 1; i <= m; ++i) mr[i] = -1; match = 0;
    }
    void add(int64_t u, int64_t v) {
        edge[u].push_back(v);
        if (ml[u] == -1 && mr[v] == -1) ml[u] = v, mr[v] = u, match++;
    }
    bool dfs(int64_t u) {
        vis[u] = true;
        for (auto &x: edge[u]) {
            int64_t v = mr[x];
            if (v == -1 || (!vis[v] && lvl[u] < lvl[v] && dfs(v))) {
                ml[u] = x; mr[x] = u; return true;
            }
        }
        return false;
    }
    int64_t matching() {
        while (true) {
            queue<int64_t> q;
            for (int i = 1; i <= n; ++i) {
                if (ml[i] == -1)    lvl[i] = 0, q.push(i);
                else                lvl[i] = -1;
            }
            while (!q.empty()) {
                int64_t u = q.front(); q.pop();
                for (auto &x : edge[u]) {
                    int64_t v = mr[x];
                    if (v != -1 && lvl[v] < 0) {
                        lvl[v] = lvl[u] + 1; q.push(v);
                    }
                }
            }
            for (int i = 1; i <= n; ++i) vis[i] = false;
            int d = 0;
            for (int i = 1; i <= n; ++i) if (ml[i] == -1 && dfs(i)) ++d;
            if (d == 0) return match;
            match += d;
        }
    }
}

/// Solves https://judge.yosupo.jp/problem/bipartitematching

// Operation:
    cin >> n >> m >> k;
    HopcroftKarp::init(n, m);
    while (k--) {
        int64_t a, b; cin >> a >> b;
        HopcroftKarp::add(++a, ++b);
    }
    cout << HopcroftKarp::matching() << '\n';
    for (i = 1; i <= n; ++i)
        if (HopcroftKarp::ml[i] != -1)
            cout << i - 1 << " " << HopcroftKarp::ml[i] - 1 << "\n";

// OR,

#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

struct HopcroftKarp {
static const int inf = 1e9;
int n;
vector<int> l, r, d;
vector<vector<int>> g;
HopcroftKarp(int _n, int _m) {
    n = _n;
    int p = _n + _m + 1;
    g.resize(p);
    l.resize(p, 0);
    r.resize(p, 0);
    d.resize(p, 0);
}
void add_edge(int u, int v) {
    g[u].push_back(v + n); //right id is increased by n, so is l[u]
}
bool bfs() {
    queue<int> q;
    for (int u = 1; u <= n; u++) {
    if (!l[u]) d[u] = 0, q.push(u);
    else d[u] = inf;
    }
    d[0] = inf;
    while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : g[u]) {
        if (d[r[v]] == inf) {
        d[r[v]] = d[u] + 1;
        q.push(r[v]);
        }
    }
    }
    return d[0] != inf;
}
bool dfs(int u) {
    if (!u) return true;
    for (auto v : g[u]) {
    if(d[r[v]] == d[u] + 1 && dfs(r[v])) {
        l[u] = v;
        r[v] = u;
        return true;
    }
    }
    d[u] = inf;
    return false;
}
int maximum_matching() {
    int ans = 0;
    while (bfs()) {
    for(int u = 1; u <= n; u++) if (!l[u] && dfs(u)) ans++;
    }
    return ans;
}
};
int32_t main() {
ios_base::sync_with_stdio(0);
cin.tie(0);
int n, m, q;
cin >> n >> m >> q;
HopcroftKarp M(n, m);
while (q--) {
    int u, v;
    cin >> u >> v;
    M.add_edge(u, v);
}
cout << M.maximum_matching() << '\n';
return 0;
}