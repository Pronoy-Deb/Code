// Note: The tree is also known as Kruskal Reconstruction Tree (KST) or DSU-tree

int64_t par[N], n; vector<int> gp[N];
void make() {
    for (int i = 0; i < n; ++i) par[i] = i;
}
int get(int i) {
    return (par[i] == i ? i : par[i] = get(par[i]));
}
void merge(int u, int v) {
    u = get(u); v = get(v);
    par[n] = n; par[u] = par[v] = n;
    gp[n].push_back(u);
    if (u != v) gp[n].push_back(v);
    ++n;
}
void build() {
    for (int i = 0; i < m; ++i) merge(U[i], V[i]);
}

https://www.codechef.com/problems/TULIPS
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9, L = 21;

struct RT {
    int n, par[N << 1], sp[L + 1][N << 1], val[N << 1], rid[N << 1];
    int T, st[N << 1], en[N << 1];
    vector<int> tre[N << 1]; // reachability tree
    int get(int x) {
        return (par[x] == x ? x : par[x] = get(par[x]));
    }
    void dfs(int u) {
        st[u] = T + 1;
        for (int v : tre[u]) {
            sp[0][v] = u; dfs(v);
        }
        if (st[u] == T + 1) {
            rid[T + 1] = u; // real id of this node
            T++;
        }
        en[u] = T;
    }
    void make(vector<array<int, 3>> e) { // {w, u, v}
        n = e.size() + 1; sort(e.begin(), e.end());
        for (int x = 1; x < (n << 1); x++) {
            par[x] = x; tre[x].clear(); val[x] = 0; sp[0][x] = 0;
        }
        for (int i = 0; i + 1 < n; ++i) {
            int u = e[i][1], v = e[i][2], w = e[i][0], id = n + i + 1;
            u = get(u), v = get(v); par[u] = par[v] = id;
            val[id] = w; tre[id].push_back(u); tre[id].push_back(v);
        }
        val[0] = 1e9; // inf
        T = 0; dfs((n << 1) - 1);
        for (int k = 1; k <= L; ++k) {
            for (int u = 1; u < (n << 1); ++u)
                sp[k][u] = sp[k - 1][sp[k - 1][u]];
        }
    }
    int lift(int u, int x) { // all nodes reachable from u s.t. edges <= w, returns the cooresponding root of the subtree
        for (int k = L; k >= 0; --k) {
            if (val[sp[k][u]] <= x) u = sp[k][u];
        }
        return u;
    }
} rt;

pair<int, int> t[N << 3]; int lz[N << 3];
inline void make(int n, int l, int r) {
    lz[n] = 0; t[n] = make_pair(0, r - l + 1); if (l == r) return;
    int mid = l + r >> 1, lc = (n << 1), rc = lc + 1;
    make(lc, l, mid); make(rc, mid + 1, r);
}
inline void push(int n, int l, int r) {
    if (lz[n]) {
        t[n].first += lz[n];
        if (l != r) {
            lz[n << 1] += lz[n]; lz[(n << 1) + 1] += lz[n];
        }
        lz[n] = 0;
    }
}
inline pair<int, int> com(pair<int, int> a, pair<int, int> b) {
    if (a.first != b.first) return min(a, b);
    return make_pair(a.first, a.second + b.second);
}
inline void up(int n, int l, int r, int ql, int qr, int val) {
    push(n, l, r);
    if (l > qr || r < ql) return;
    if (l >= ql && r <= qr) {
        lz[n] += val;
        push(n, l, r);
        return;
    }
    int mid = l + r >> 1, lc = (n << 1), rc = lc + 1;
    up(lc, l, mid, ql, qr, val); up(rc, mid + 1, r, ql, qr, val);
    t[n] = com(t[lc], t[rc]);
}
inline pair<int, int> get(int n, int l, int r, int ql, int qr) {
    push(n, l, r); if (l > qr || r < ql) return make_pair(1e9, 0);
    if (l >= ql && r <= qr) return t[n];
    int mid = l + r >> 1, lc = (n << 1), rc = lc + 1;
    auto left = get(lc, l, mid, ql, qr), rght = get(rc, mid + 1, r, ql, qr);
    return com(left, rght);
}
queue<pair<int, int>> Q;

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        while (!Q.empty()) Q.pop();
        int n; cin >> n;
        vector<array<int, 3>> e(n - 1);
        for (int i = 0; i + 1 < n; ++i) cin >> e[i][1] >> e[i][2] >> e[i][0];
        rt.make(e); make(1, 1, n);
        int q, x; cin >> q >> x;
        while (q--) {
            int d, u, k; cin >> d >> u >> k;
            u = rt.lift(u, k);
            while (!Q.empty() and Q.front().first <= d) {
                up(1, 1, n, rt.st[Q.front().second], rt.en[Q.front().second], -1);
                Q.pop();
            }
            pair<int, int> ans = get(1, 1, n, rt.st[u], rt.en[u]);
            if (ans.first == 0) cout << ans.second << "\n";
            else cout << "0\n";
            up(1, 1, n, rt.st[u], rt.en[u], 1);
            Q.push(make_pair(d + x, u));
        }
    }
    return 0;
}

https://codeforces.com/contest/1416/problem/D

int st[N], en[N], ar[N], par[N], rid[N], root[N];
struct ST {
    pair<int, int> t[N << 2];
    void make(int n, int b, int e) {
        if(b == e) {
            t[n] = {0, b}; return;
        }
        int mid = (b + e) >> 1, l = n << 1, r = l | 1;
        make(l, b, mid); make(r, mid + 1, e);
        t[n] = max(t[l], t[r]);
    }
    void up(int n, int b, int e, int i, int x) {
        if(b > i || e < i) return;
        if(b == e && b == i) {
            t[n] = {x, b}; return;
        }
        int mid = (b + e) >> 1, l = n << 1, r = l | 1;
        up(l, b, mid, i, x); up(r, mid + 1, e, i, x);
        t[n] = max(t[l], t[r]);
    }
    pair<int, int> get(int n, int b, int e, int i, int j) {
        if(b > j || e < i) return {0, 0};
        if(b >= i && e <= j) return t[n];
        int mid = (b + e) >> 1,  l = n << 1,  r = l | 1;
        auto L = get(l, b, mid, i, j);
        auto R = get(r, mid + 1, e, i, j);
        return max(L, R);
    }
} t;

int find(int u) {
    return par[u] == u ? u : par[u] = find(par[u]);
}
int T, I; vector<int> gp[N];
void uni(int u, int v) {
	u = find(u); v = find(v);
	if (u == v) return; ++T;
	gp[T].push_back(u); gp[T].push_back(v);
	par[u] = par[v] = T; return;
}
bitset<N> vis;
void dfs(int u) {
	vis[u] = 1; st[u] = I + 1;
	for (auto v: gp[u]) dfs(v);
	if (st[u] == I + 1) {
		++I; rid[I] = u;
	}
	en[u] = I;
}

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> m >> q; T = n;
	for (i = 1; i <= n; ++i) {
        cin >> ar[i]; par[i] = i;
    }
    for (i = n + 1; i <= 2 * n; ++i) par[i] = i;
    pair<int, int> ed[m + 5]; set<int> se;
	for (i = 1; i <= m; ++i) {
		int u, v; cin >> u >> v; ed[i] = {u, v};
        se.insert(i);
	}
    int ty[q + 5], x[q + 5];
	for (i = 1; i <= q; ++i) {
		cin >> ty[i] >> x[i];
		if (ty[i] == 2) se.erase(x[i]);
	}
	for (auto x : se) uni(ed[x].first, ed[x].second);
	for (i = q; i >= 1; --i) {
		if (ty[i] == 2) uni(ed[x[i]].first, ed[x[i]].second);
		else root[i] = find(x[i]);
	}
	for (i = T; i >= 1; i--) {
		if (!vis[i]) dfs(i);
	}
	t.make(1, 1, n);
	for (i = 1; i <= n; ++i) t.up(1, 1, n, i, ar[rid[i]]);
	for (i = 1; i <= q; ++i) {
		if (ty[i] == 1) {
			auto f = t.get(1, 1, n, st[root[i]], en[root[i]]);
			t.up(1, 1, n, f.second, 0); cout << f.first << '\n';
		}
	}
}