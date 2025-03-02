// Determining Centroid(s):
https://cses.fi/problemset/task/2079

vector<int> gp[N]; int sz[N];
void dfs(int u = 1, int p = 0) {
	sz[u] = 1;
	for (auto v : gp[u]) {
		if (v ^ p) {
			dfs(v, u); sz[u] += sz[v];
		}
	}
}
vector<int> cen(int n) {
	dfs(); int u = 1;
	while (1) {
		int tmp = -1;
		for (auto v : gp[u]) {
			if (sz[v] > sz[u]) continue;
			if ((sz[v] << 1) >= n) tmp = v;
		}
		if (tmp == -1) break; u = tmp;
	}
	dfs(u);
	for (auto v : gp[u]) {
		if ((sz[v] << 1) == n) return {u, v};
	}
	return {u};
}

// Operation:
    cin >> n;
    for (i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        gp[u].push_back(v); gp[v].push_back(u);
    }
    auto v = cen(n);
    cout << v.front();

// Centroid Decomposition:
https://cses.fi/problemset/task/2080/

vector<int> gp[N]; bitset<N> vis;
int64_t n, k, ans, sz[N], cnt[N]{1}, mxDep;
int subSize(int u, int p) {
    sz[u] = 1;
    for (auto i : gp[u]) if (!vis[i] && i != p) sz[u] += subSize(i, u);
    return sz[u];
}
int centroid(int u, int p, int mx) {
    for (auto &v : gp[u]) if (!vis[v] && v != p && (sz[v] << 1) > mx) return centroid(v, u, mx);
    return u;
}
void go(int u, int p, int dep, bool fil) {
    if (dep > k) return; if (dep > mxDep) mxDep = dep;
    if (fil) ++cnt[dep]; else ans += cnt[k - dep];
    for (auto &v : gp[u]) if (!vis[v] && v != p) go(v, u, dep + 1, fil);
}
void dcom(int u = 1) {
    int mx = subSize(u, u), c = centroid(u, u, mx);
    vis[c] = true, mxDep = 0;
    for (auto &i : gp[c]) {
        if (!vis[i]) {
            go(i, c, 1, false); go(i, c, 1, true);
        }
    }
    fill(cnt + 1, cnt + mxDep + 1, 0);
    for (auto &v : gp[c]) if (!vis[v]) dcom(v);
}

// Operation:
    cin >> n >> k;
    for (i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        gp[u].push_back(v); gp[v].push_back(u);
    }
    dcom(); cout << ans;

https://cses.fi/problemset/task/2081

vector<int> gp[N]; bitset<N> vis;
int64_t k1, k2, ans, sz[N], cnt[N]{1}, ct[N], mxDep, subDep, n;
int subSize(int u, int p) {
    sz[u] = 1;
    for (auto i : gp[u]) if (!vis[i] && i != p) sz[u] += subSize(i, u);
    return sz[u];
}
int centroid(int u, int p, int size) {
    for (auto v : gp[u]) if (!vis[v] && v != p && (sz[v] << 1) > size) return centroid(v, u, size);
    return u;
}
void go(int u, int p, int64_t dep = 1) {
    if (dep > k2) return; subDep = max(subDep, dep); ++ct[dep];
    for (auto &v : gp[u]) if (!vis[v] && v != p) go(v, u, dep + 1);
}
void dcom(int u = 1) {
    int size = subSize(u, u), c = centroid(u, u, size);
    vis[c] = true, mxDep = 0; int64_t tot = (k1 == 1);
    for (auto i : gp[c]) {
        if (!vis[i]) {
            subDep = 0; go(i, c); int64_t sum = tot;
            for (int d = 1; d <= subDep; ++d) {
                ans += sum * ct[d]; int d1 = k2 - d, d2 = k1 - d - 1;
                if (d1 >= 0) sum -= cnt[d1];
                if (d2 >= 0) sum += cnt[d2];
            }
            for (int d = k1 - 1, l = min(k2 - 1, subDep); d <= l; ++d) tot += ct[d];
            for (int d = 1; d <= subDep; ++d) cnt[d] += ct[d];
            mxDep = max(mxDep, subDep); fill(ct, ct + subDep + 1, 0);
        }
    }
    fill(cnt + 1, cnt + mxDep + 1, 0);
    for (auto v : gp[c]) if (!vis[v]) dcom(v);
}

// Operation:
    cin >> n >> k1 >> k2;
    for (i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        gp[u].push_back(v); gp[v].push_back(u);
    }
    dcom(); cout << ans;

https://codeforces.com/contest/321/problem/C

vector<int> gp[N]; bitset<N> vis; int sz[N], cPar[N], dep[N], siz;
void subSize(int u, int p) {
    ++siz; sz[u] = 1;
    for (auto v : gp[u]) {
        if (v == p || vis[v]) continue; subSize(v, u); sz[u] += sz[v];
    }
}
int centroid(int u, int p) {
    for (auto v : gp[u]) {
        if (v == p || vis[v]) continue;
        if (sz[v] > (siz >> 1)) return centroid(v, u);
    }
    return u;
}
void dcom(int u = 1, int p = 0) {
    siz = 0; subSize(u, p); int c = centroid(u, p); cPar[c] = p; vis[c] = 1;
    for (auto v : gp[c]) {
        if (v == p || vis[v]) continue; dcom(v, c);
    }
}
void dfs(int u, int p = 0) {
    for (auto v : gp[u]) {
        if (v == p) continue; dep[v] = dep[u] + 1; dfs(v, u);
    }
}

// Operation:
    cin >> n;
    for (i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        gp[u].push_back(v); gp[v].push_back(u);
    }
    dcom();
    for (i = 1; i <= n; ++i) gp[i].clear();
    int rt = 1;
    for (i = 1; i <= n; ++i) {
        gp[cPar[i]].push_back(i); gp[i].push_back(cPar[i]);
        if (cPar[i] == 0) rt = i;
    }
    dfs(rt);
    for (i = 1; i <= n; ++i) cout << char(dep[i] + 'A') << ' ';

// Persistent Centroid Decompostion:
https://codeforces.com/contest/757/problem/G

const int N = 2e5 + 9, M = (N << 1) + N * 19 * 2;
vector<pair<int, int>> gp[N << 1], gp[N];
inline void add(int u, int v, int w) {
    gp[u].push_back({v, w});
}
int T;
void binarize(int u, int p = 0) {
    int last = 0, tmp = 0;
    for (auto &[v, w] : gp[u]) {
        if (v == p) continue;
        if (++tmp == 1) {
            add(u, v, w); add(v, u, w); last = u;
        }
        else if (tmp == ((int) gp[u].size()) - (u != 1)) {
            add(last, v, w); add(v, last, w);
        }
        else {
            add(last, ++T, 0); add(T, last, 0);
            last = T; add(T, v, w); add(v, T, w);
        }
    }
    for (auto &[v, w] : gp[u]) {
        if (v == p) continue; binarize(v, u);
    }
}
int sz[N << 1], tot, done[N << 1], cenpar[N << 1];
void calc_sz(int u, int p) {
    ++tot; sz[u] = 1;
    for (auto &[v, w] : gp[u]) {
        if(v == p || done[v]) continue;
        calc_sz(v, u); sz[u] += sz[v];
    }
}
int find_cen(int u, int p) {
    for (auto &[v, w] : gp[u]) {
        if(v == p || done[v]) continue;
        else if(sz[v] > (tot >> 1)) return find_cen(v, u);
    }
    return u;
}
int64_t d[20][N << 1];
void yo(int u, int p, int64_t nw, int l) {
    d[l][u] = nw;
    for(auto &[v, w] : gp[u]) {
        if (v == p || done[v]) continue;
        yo(v, u, nw + w, l);
    }
}
int st[N << 1], en[N << 1], DT;
struct node {
    vector<int> ct; // adjacent edges in centroid tree
    int64_t sum = 0, parsum = 0, level = 0, id = 0, cnt = 0;
} t[M];
int dcom(int u, int p = 0, int l = 0) {
    tot = 0; calc_sz(u, p); int cen = find_cen(u, p);
    cenpar[cen] = p; done[cen] = 1;
    u = cen; st[u] = ++DT; t[u].id = u;
    t[u].level = l; yo(u, p, 0, l);
    for (auto &[v, w] : gp[u]) {
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
int64_t query(int cur, int u) { // query on cur tree
    int64_t ans = 0;
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
        gp[u].push_back({v, w}); gp[v].push_back({u, w});
    }
    T = n; binarize(1); rt[0] = dcom(1);
    for(int i = 1; i <= n; ++i) rt[i] = up(rt[i - 1], a[i]);
    int64_t ans = 0; const int mod = 1 << 30;
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

// Centroid Decomposition Tree:

const int64_t K = 22, INF = 1e9 + 7;
vector<int64_t> gp[N]; int64_t sub[N], par[N], anc[N][K], lvl[N], ans[N];
bool vis[N];
void dfs(int64_t u, int64_t p) {
    lvl[u] = lvl[p] + 1; anc[u][0] = p;
    for (int64_t k = 1; k < K; ++k) anc[u][k] = anc[anc[u][k - 1]][k - 1];
    for (auto &v : gp[u]) if (v ^ p) dfs(v, u);
}
int64_t lca(int64_t u, int64_t v) {
    if (lvl[u] > lvl[v]) swap(u, v);
    for (int64_t k = K - 1; k >= 0; --k)
        if (lvl[u] + (1 << k) <= lvl[v]) v = anc[v][k];
    if (u == v) return u;
    for (int64_t k = K - 1; k >= 0; --k)
        if (anc[u][k] != anc[v][k]) u = anc[u][k], v = anc[v][k];
    return anc[u][0];
}
int64_t getanc(int64_t u, int64_t d) {
    for (int64_t k = 0; k < K; ++k)
        if (d & (1 << k)) u = anc[u][k];
    return u;
}
int64_t dis(int64_t u, int64_t v) {
    int64_t g = lca(u, v);
    return lvl[u] + lvl[v] - (lvl[g] << 1);
}
void getsub(int64_t u, int64_t p) {
    sub[u] = 1;
    for (auto &v : gp[u])
        if (!vis[v] && v ^ p) getsub(v, u), sub[u] += sub[v];
}
int64_t centroid(int64_t u, int64_t p, int64_t r) {
    for (auto &v : gp[u])
        if (!vis[v] && v ^ p)
            if (sub[v] > r) return centroid(v, u, r);
    return u;
}
void dcom(int64_t u, int64_t p) {
    getsub(u, u);
    int64_t c = centroid(u, u, sub[u] >> 1);
    vis[c] = 1, par[c] = p;
    for (auto &v : gp[c]) if (!vis[v]) dcom(v, c);
}
// update ans for all ancin the centroid tree
void update(int64_t u) {
    for (int64_t v = u; v > 0; v = par[v]) {
        ans[v] = min(ans[v], dis(v, u));
    }
}
// query through all the anc in the centroid tree
int64_t query(int64_t u) {
    int64_t ret = INF;
    for (int64_t v = u; v > 0; v = par[v]) {
        ret = min(ret, ans[v] + dis(u, v));
    }
    return ret;
}

// Operation:
    cin >> n >> m;
    for (i = 1; i < n; ++i) {
        int64_t u, v; cin >> u >> v;
        gp[u].push_back(v); gp[v].push_back(u);
    }
    dfs(1, 0); dcom(1, 0);
    for (i = 1; i <= n; ++i) ans[i] = INF;
    update(1);
    while (m--) {
        int64_t tp, u; cin >> tp >> u;
        if (tp == 1) update(u);
        else cout << query(u) << "\n";
    }

// OR,

#define remover(vec, v) vec.erase(find(vec.begin(), vec.end(), v))

// Rooted tree
struct arborescence {
    vector<vector<int64_t>> cld;
    int64_t rt;
};
arborescence cdt(vector<vector<int64_t>> graph) {
    int64_t n = graph.size(); vector<int64_t> subtree_size(n);
    auto dfs = [&](int64_t u, auto&& self) -> int64_t {
        for (auto v : graph[u]) {
            remover(graph[v], u); subtree_size[u] += self(v, self);
        }
        return ++subtree_size[u];
    };
    dfs(0, dfs);
    vector<vector<int64_t>> d_tre(n);
    auto c_re = [&](int64_t u, auto&& self) -> int64_t {
        int64_t N = subtree_size[u];
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
    int64_t d_rt = c_re(0, c_re);
    return {move(d_tre), d_rt};
}
