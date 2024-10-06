// The tree is also known as Kruskal Reconstruction Tree(KST)

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9, L = 21;

struct RT {
    int n, par[N << 1], sp[L + 1][N << 1], val[N << 1], rid[N << 1];
    int T, st[N << 1], en[N << 1];
    vector<int> tre[N << 1]; // reachability tree
    int get(int x) {
        if (par[x] == x) return x;
        return par[x] = get(par[x]);
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
    void make(vector<array<int, 3>> e) { //{w, u, v}
        n = e.size() + 1; sort(e.begin(), e.end());
        for (int x = 1; x < (n << 1); x++) {
            par[x] = x; tre[x].clear(); val[x] = 0; sp[0][x] = 0;
        }
        for (int i = 0; i + 1 < n; i++) {
            int u = e[i][1], v = e[i][2], w = e[i][0], id = n + i + 1;
            u = get(u), v = get(v); par[u] = par[v] = id;
            val[id] = w; tre[id].push_back(u); tre[id].push_back(v);
        }
        val[0] = 1e9; // inf
        T = 0; dfs((n << 1) - 1);
        for (int k = 1; k <= L; k++) {
            for (int u = 1; u < (n << 1); u++)
                sp[k][u] = sp[k - 1][sp[k - 1][u]];
        }
    }
    int lift(int u, int x) { // all nodes reachable from u s.t. edges <= w, returns the cooresponding root of the subtree
        for (int k = L; k >= 0; k--) {
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
    if (l > qr || r < ql)
        return;
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
        for (int i = 0; i + 1 < n; i++) cin >> e[i][1] >> e[i][2] >> e[i][0];
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
// https://www.codechef.com/problems/TULIPS