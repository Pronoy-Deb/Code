#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9;
//edges weights must need to be non-negative

// f[x] = distance from root to x
// x <= y <= z
// max{f[x] - 2f[y] + f[z]}
// a --> f[x]
// b --> -2f[y]
// c --> f[x] - 2f[y]
// d --> -2f[y] + f[z]
// e --> f[x] - 2f[y] + f[z]
struct node {
    int64_t a = 0, b = 0, c = 0, d = 0, e = 0;
    node operator + (const node &oth) const {
        node ret;
        ret.a = max(a, oth.a); ret.b = max(b, oth.b);
        ret.c = max(max(c, oth.c), a + oth.b);
        ret.d = max(max(d, oth.d), b + oth.a);
        ret.e = max(max(e, oth.e), max(c + oth.a, a + oth.d));
        return ret;
    }
};
struct ST {
    #define lc (n << 1)
    #define rc ((n << 1) | 1)
    int64_t lz[N << 3];
    node t[N << 3];
    ST() {
        memset(lz, 0, sizeof lz);
    }
    inline void push(int n, int b, int e) {
        if(lz[n] == 0) return;
        int64_t v = lz[n];
        t[n].a += v, t[n].b -= v + v, t[n].c -= v, t[n].d -= v;
        if (b != e) lz[lc] += v, lz[rc] += v;
        lz[n] = 0;
    }
    inline void pull(int n) {
        t[n] = t[lc] + t[rc];
    }
    void up(int n, int b, int e, int i, int j, int64_t v) {
        push(n, b, e);
        if(j < b || e < i) return;
        if(i <= b && e <= j) {
            lz[n] += v; push(n, b, e);
            return;
        }
        int mid = (b + e) >> 1;
        up(lc, b, mid, i, j, v); up(rc, mid + 1, e, i, j, v);
        pull(n);
    }
}t;

vector<pair<int, int>> g[N];
int64_t W[N], T, st[n << 1], en[n << 1], pos[N];
void dfs (int u, int p = 0) {
    st[u] = ++T;
    for (auto e : g[u]) {
        int v = e.first, i = e.second;
        if (v == p) continue;
        pos[i] = v; dfs(v, u); ++T;
    }
    en[u] = T;
}
int32_t main() {
    int n, q; int64_t mod; cin >> n >> q >> mod;
    for (int i = 1; i < n; ++i) {
        int u, v; int64_t w; cin >> u >> v >> w;
        g[u].push_back({v, i});  g[v].push_back({u, i});
        W[i] = w;
    }
    dfs(1);
    for (int i = 1; i < n; ++i) t.up(1, 1, T, st[pos[i]], en[pos[i]], W[i]);
    int64_t last = 0;
    while (q--) {
        int d; int64_t e; cin >> d >> e;
        d = 1 + (d + last) % (n - 1); e = (e + last) % mod;
        t.up(1, 1, T, st[pos[d]], en[pos[d]], e - W[d]);
        last = t.t[1].e, W[d] = e; cout << last << '\n';
    }
    return 0;
}

//https://codeforces.com/contest/1192/problem/B