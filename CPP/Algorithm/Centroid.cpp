// Centroids:

#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9;
vector<int> g[N];
int sz[N];
void dfs(int u, int p = 0) {
	sz[u] = 1;
	for (auto v: g[u]) {
		if (v ^ p) {
			dfs(v, u);
			sz[u] += sz[v];
		}
	}
}
vector<int> get_centroids(int n) {
	int u = 1;
	dfs(u);
	while (1) {
		int tmp = -1;
		for (auto v: g[u]) {
			if (sz[v] > sz[u]) continue;
			if (2 * sz[v] >= n) tmp = v;
		}
		if (tmp == -1) break;
		u = tmp;
	}
	dfs(u);
	for (auto v: g[u]) {
		if (2 * sz[v] == n) {
			return {u, v};
		}
	}
	return {u};
}
int32_t main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		for (int i = 1; i < n; i++) {
		    int u, v; cin >> u >> v;
		    g[u].push_back(v);
		    g[v].push_back(u);
		}
		auto v = get_centroids(n);
		for (auto i: v) cout << i << ' '; cout << '\n';
		for (int i = 1; i <= n; i++) g[i].clear();
	}
  return 0;
}
// similar problem: https://cses.fi/problemset/task/2079

// Centroid Decomposition:
// Problem: https://cses.fi/problemset/task/2080/

vector<int> gp[N];
long long n, k, ans = 0, sz[N], cnt[N]{1}, mxdep; bool vis[N];
int dfs(int u, int p = 0) {
    sz[u] = 1;
    for (auto &i : gp[u]) if (!vis[i] && i != p) sz[u] += dfs(i, u);
    return sz[u];
}
int centroid(int u, int p, int mx) {
    for (auto &v : gp[u])
        if (!vis[v] && v != p && (sz[v] << 1) > mx) return centroid(v, u, mx);
    return u;
}
void go(int u, int p, int dep, bool fil) {
    if (dep > k) return;
    if (dep > mxdep) mxdep = dep;
    if (fil) cnt[dep]++; else ans += cnt[k - dep];
    for (auto &v : gp[u]) if (!vis[v] && v != p) go(v, u, dep + 1, fil);
}
void dcom(int u) {
    int mx = dfs(u, u), c = centroid(u, u, mx);
    vis[c] = true, mxdep = 0;
    for (auto &i : gp[c]) {
        if (!vis[i]) {
            go(i, c, 1, false); go(i, c, 1, true);
        }
    }
    fill(cnt + 1, cnt + mxdep + 1, 0);
    for (auto &v : gp[c]) if (!vis[v]) dcom(v);
}

// Operation:
    cin >> n >> k;
    for (i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        gp[u].push_back(v); gp[v].push_back(u);
    }
    dcom(1);
    cout << ans;

// OR,
vector<int> g[N]; int sz[N], tot = 0, done[N], cenpar[N];
void calc_sz(int u, int p) {
    ++tot; sz[u] = 1;
    for (auto &v : g[u]) {
        if(v == p || done[v]) continue;
        calc_sz(v, u); sz[u] += sz[v];
    }
}
int find_cen(int u, int p) {
    for (auto &v : g[u]) {
        if(v == p || done[v]) continue;
        else if(sz[v] > (tot >> 1)) return find_cen(v, u);
    }
    return u;
}
void dcom(int u, int pre) {
    calc_sz(u, pre); int cen = find_cen(u, pre);
    cenpar[cen] = pre; done[cen] = 1;
    for(auto &v : g[cen]) {
        if(v == pre || done[v]) continue;
        dcom(v, cen);
    }
}
int dep[N];
void dfs(int u, int p = 0) {
    for(auto &v : g[u]) {
        if(v == p) continue;
        dep[v] = dep[u] + 1; dfs(v, u);
    }
}

// Operation:
    cin >> n;
    for(i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        g[u].push_back(v); g[v].push_back(u);
    }
    dcom(1);
    for(i = 1; i <= n; ++i) g[i].clear();
    int rt = 1;
    for(i = 1; i <= n; ++i) {
        g[cenpar[i]].push_back(i);
        g[i].push_back(cenpar[i]);
        if (cenpar[i] == 0) rt = i;
    }
    dfs(rt);
    for(i = 1; i <= n; ++i) cout << char(dep[i] + 'A') << ' ';

// Problem: https://codeforces.com/contest/321/problem/C

// Centroid Decompostion Persistent:
const int N = 2e5 + 9, M = (N << 1) + N * 19 * 2;

vector<pair<int, int>> g[N << 1], G[N];
inline void add(int u, int v, int w) {
    g[u].push_back({v, w});
}
int T;
void binarize(int u, int p = 0) {
    int last = 0, tmp = 0;
    for (auto &[v, w] : G[u]) {
        if (v == p) continue;
        if (++tmp == 1) {
            add(u, v, w); add(v, u, w); last = u;
        }
        else if (tmp == ((int) G[u].size()) - (u != 1)) {
            add(last, v, w); add(v, last, w);
        }
        else {
            add(last, ++T, 0); add(T, last, 0);
            last = T; add(T, v, w); add(v, T, w);
        }
    }
    for (auto &[v, w] : G[u]) {
        if (v == p) continue; binarize(v, u);
    }
}
int sz[N << 1], tot, done[N << 1], cenpar[N << 1];
void calc_sz(int u, int p) {
    ++tot; sz[u] = 1;
    for (auto &[v, w] : g[u]) {
        if(v == p || done[v]) continue;
        calc_sz(v, u); sz[u] += sz[v];
    }
}
int find_cen(int u, int p) {
    for (auto &[v, w] : g[u]) {
        if(v == p || done[v]) continue;
        else if(sz[v] > (tot >> 1)) return find_cen(v, u);
    }
    return u;
}
long long d[20][N << 1];
void yo(int u, int p, long long nw, int l) {
    d[l][u] = nw;
    for(auto &[v, w] : g[u]) {
        if (v == p || done[v]) continue;
        yo(v, u, nw + w, l);
    }
}
int st[N << 1], en[N << 1], DT;
struct node {
    vector<int> ct; // adjacent edges in centroid tree
    long long sum = 0, parsum = 0, level = 0, id = 0, cnt = 0;
} t[M];
int dcom(int u, int p = 0, int l = 0) {
    tot = 0; calc_sz(u, p); int cen = find_cen(u, p);
    cenpar[cen] = p; done[cen] = 1;
    u = cen; st[u] = ++DT; t[u].id = u;
    t[u].level = l; yo(u, p, 0, l);
    for (auto &[v, w] : g[u]) {
        if(v == p || done[v]) continue;
        int x = dcom(v, u, l + 1);
        t[u].ct.push_back(x);
    }
    en[u] = DT; return u;
}
bool insub(int r, int c) {
    r = t[r].id, c = t[c].id;
    return (st[r] <= st[c] && en[c] <= en[r]);
}
int up(int cur, int u) { //update node u in cur tree
    ++T; assert(T < M);
    t[T] = t[cur]; cur = T;
    t[cur].cnt++; t[cur].sum += d[t[cur].level][u];
    for(auto &v : t[cur].ct) {
        if(insub(v, u)) {
            v = up(v, u); t[v].parsum += d[t[cur].level][u];
        }
    }
    return cur;
}
long long query(int cur, int u) { // query on cur tree
    long long ans = 0;
    while (t[cur].id != t[u].id) {
        int v = 0;
        for (auto x : t[cur].ct) if(insub(x, u)) v = x;
        assert(v);
        ans += d[t[cur].level][t[u].id] * (t[cur].cnt - t[v].cnt);
        ans += t[cur].sum - t[v].parsum; cur = v;
    }
    ans += t[cur].sum; return ans;
}
int ar[N], rt[N];

// Operation:
    cin >> n >> q;
    for(int i = 1; i <= n; ++i) cin >> ar[i];
    for (int i = 1; i < n; ++i) {
        int u, v, w; cin >> u >> v >> w;
        G[u].push_back({v, w}); G[v].push_back({u, w});
    }
    T = n; binarize(1); rt[0] = dcom(1);
    for(int i = 1; i <= n; ++i) rt[i] = up(rt[i - 1], a[i]);
    long long ans = 0; const int mod = 1 << 30;
    while(q--) {
        int ty; cin >> ty;
        if(ty == 1) {
            int l, r, u; cin >> l >> r >> u;
            l ^= ans; r ^= ans; u ^= ans;
            ans = query(rt[r], u) - query(rt[l - 1], u);
            cout << ans << '\n'; ans %= mod;
        }
        else {
        int x;
        cin >> x;
        x ^= ans;
        rt[x] = up(rt[x - 1], a[x + 1]);
        swap(a[x], a[x + 1]);
        }
    }

//https://codeforces.com/contest/757/problem/G

// Centroid Decomposition Tree:

const long long K = 22, INF = 1e9 + 7;
vector<long long> gp[N]; long long sub[N], par[N], anc[N][K], lvl[N], ans[N];
bool vis[N];
void dfs(long long u, long long p) {
    lvl[u] = lvl[p] + 1; anc[u][0] = p;
    for (long long k = 1; k < K; ++k) anc[u][k] = anc[anc[u][k - 1]][k - 1];
    for (auto &v : gp[u]) if (v ^ p) dfs(v, u);
}
long long lca(long long u, long long v) {
    if (lvl[u] > lvl[v]) swap(u, v);
    for (long long k = K - 1; k >= 0; --k)
        if (lvl[u] + (1 << k) <= lvl[v]) v = anc[v][k];
    if (u == v) return u;
    for (long long k = K - 1; k >= 0; --k)
        if (anc[u][k] != anc[v][k]) u = anc[u][k], v = anc[v][k];
    return anc[u][0];
}
long long getanc(long long u, long long d) {
    for (long long k = 0; k < K; ++k)
        if (d & (1 << k)) u = anc[u][k];
    return u;
}
long long dis(long long u, long long v) {
    long long g = lca(u, v);
    return lvl[u] + lvl[v] - (lvl[g] << 1);
}
void getsub(long long u, long long p) {
    sub[u] = 1;
    for (auto &v : gp[u])
        if (!vis[v] && v ^ p) getsub(v, u), sub[u] += sub[v];
}
long long centroid(long long u, long long p, long long r) {
    for (auto &v : gp[u])
        if (!vis[v] && v ^ p)
            if (sub[v] > r) return centroid(v, u, r);
    return u;
}
void dcom(long long u, long long p) {
    getsub(u, u);
    long long c = centroid(u, u, sub[u] >> 1);
    vis[c] = 1, par[c] = p;
    for (auto &v : gp[c]) if (!vis[v]) dcom(v, c);
}
// update ans for all ancin the centroid tree
void update(long long u) {
    for (long long v = u; v > 0; v = par[v]) {
        ans[v] = min(ans[v], dis(v, u));
    }
}
// query through all the anc in the centroid tree
long long query(long long u) {
    long long ret = INF;
    for (long long v = u; v > 0; v = par[v]) {
        ret = min(ret, ans[v] + dis(u, v));
    }
    return ret;
}

// Operation:
    cin >> n >> m;
    for (i = 1; i < n; ++i) {
        long long u, v; cin >> u >> v;
        gp[u].push_back(v); gp[v].push_back(u);
    }
    dfs(1, 0); dcom(1, 0);
    for (i = 1; i <= n; ++i) ans[i] = INF;
    update(1);
    while (m--) {
        long long tp, u; cin >> tp >> u;
        if (tp == 1) update(u);
        else cout << query(u) << "\n";
    }

// OR,

#define remover(vec, v) vec.erase(find(vec.begin(), vec.end(), v))

// Rooted tree
struct arborescence {
    vector<vector<long long>> cld;
    long long rt;
};
arborescence cdt(vector<vector<long long>> graph) {
    long long n = graph.size(); vector<long long> subtree_size(n);
    auto dfs = [&](long long u, auto&& self) -> long long {
        for (auto v : graph[u]) {
            remover(graph[v], u); subtree_size[u] += self(v, self);
        }
        return ++subtree_size[u];
    };
    dfs(0, dfs);
    vector<vector<long long>> d_tre(n);
    auto c_re = [&](long long u, auto&& self) -> long long {
        long long N = subtree_size[u];
        for (bool found = 0; !found;) {
            found = 1;
            for (auto v : graph[u]) {
                if (subtree_size[v] > N / 2) {
                    found = 0; subtree_size[u] = N - subtree_size[v];
                    remover(graph[u], v); graph[v].push_back(u);
                    u = v; break;
                }
            }
        }
        for (auto v : graph[u]) d_tre[u].push_back(self(v, self));
        return u;
    };
    long long d_rt = c_re(0, c_re);
    return {move(d_tre), d_rt};
}