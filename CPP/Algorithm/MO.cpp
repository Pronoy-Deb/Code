https://cses.fi/problemset/task/1734/

uint64_t hilbertOrder(uint64_t x, uint64_t y) {
    const uint64_t logn = __lg((max(x, y) << 1) + 1) | 1, maxn = (1ull << logn) - 1;
    uint64_t res = 0;
    for (uint64_t s = 1ull << (logn - 1); s; s >>= 1) {
        bool rx = x & s, ry = y & s;
        res = (res << 2) | (rx ? ry ? 2 : 1 : ry ? 3 : 0);
        if (!rx) {
            if (ry) x ^= maxn, y ^= maxn; swap(x, y);
        }
    }
    return res;
}
struct Query {
    int l, r, id; int64_t ord;
    void order() { ord = hilbertOrder(l, r); }
    bool operator<(const Query &x) const { return ord < x.ord; }
} Q[N];
long long ar[N], ans[N], cnt[N];
void mo(int q) {
    sort(Q + 1, Q + q + 1); int l = 1, r = 0, res = 0;
    auto add = [&](int i){
        res += (++cnt[ar[i]] == 1);
    };
    auto rem = [&](int i) {
        res -= (--cnt[ar[i]] == 0);
    };
    for (int i = 1; i <= q; ++i) {
        int L = Q[i].l, R = Q[i].r;
        if (R < l) {
            while (l > L) add(--l);
            while (l < L) rem(l++);
            while (r < R) add(++r);
            while (r > R) rem(r--);
        }
        else {
            while (r < R) add(++r);
            while (r > R) rem(r--);
            while (l > L) add(--l);
            while (l < L) rem(l++);
        }
        ans[Q[i].id] = res;
    }
}

// Operation:
    cin >> n >> q;
    unordered_map<int, int> mp;
    for (i = 1; i <= n; ++i) {
        cin >> ar[i];
        auto it = mp.find(ar[i]);
        if (it == mp.end()) {
            mp[ar[i]] = ++c; ar[i] = c;
        }
        else ar[i] = it->second;
    }
    for (i = 1; i <= q; ++i) {
        cin >> Q[i].l >> Q[i].r; Q[i].id = i;
        Q[i].order();
    }
    mo(q);
    for (i = 1; i <= q; ++i) cout << ans[i] << '\n';

https://codeforces.com/contest/86/problem/D

const int B = 440;

long long sum, cnt[N], ar[N], ans[N];
struct query {
    int l, r, id;
    bool operator < (const query &x) const {
        if (l / B == x.l / B) return ((l / B) & 1) ? r > x.r : r < x.r;
        return l / B < x.l / B;
    }
} Q[N];
inline void add(int i) {
    sum += ((cnt[ar[i]]++ << 1) + 1) * ar[i];
}
inline void rem(int i) {
    sum -= ((cnt[ar[i]]-- << 1) - 1) * ar[i];
}
void mo(int q) {
    sort(Q + 1, Q + q + 1); int l = 1, r = 0;
    for (int i = 1; i <= q; ++i) {
        int L = Q[i].l, R = Q[i].r;
        if (R < l) {
            while (l > L) add(--l);
            while (l < L) rem(l++);
            while (r < R) add(++r);
            while (r > R) rem(r--);
        }
        else {
            while (r < R) add(++r);
            while (r > R) rem(r--);
            while (l > L) add(--l);
            while (l < L) rem(l++);
        }
        ans[Q[i].id] = sum;
    }
}

// Operation:
    cin >> n >> q;
    for (i = 1; i <= n; ++i) cin >> ar[i];
    for (i = 1; i <= q; ++i) {
        cin >> Q[i].l >> Q[i].r; Q[i].id = i;
    }
    mo(q);
    for (i = 1; i <= q; ++i) cout << ans[i] << '\n';

// MO Online:

const int N = 1e5 + 1, B = 4500, C = N / B + 1;

struct MEX {
int cnt[N << 1], f[N << 1];
MEX() {
    memset(cnt, 0, sizeof cnt); memset(f, 0, sizeof f);
}
void add(int x) {
    --f[cnt[x]], ++cnt[x], ++f[cnt[x]];
}
void del(int x) {
    --f[cnt[x]], --cnt[x], ++f[cnt[x]];
}
int get() {
    int ans = 1; while(f[ans] > 0) ++ans; return ans;
}
} t[(C * (C + 1) >> 1) + 10], ds;

int st[C], en[C], BC = 0, ar[N], I[N];
int query(int l, int r) {
    int L = l / B, R = r / B;
    if (r != en[R]) R--; if (l != st[L]) L++;
    if (R < L) {
        for (int i = l; i <= r; ++i) ds.add(ar[i]);
        int ans = ds.get();
        for (int i = l; i <= r; ++i) ds.del(ar[i]);
        return ans;
    }
    int id = I[L * BC + R];
    for (int i = l; i < st[L]; ++i) t[id].add(ar[i]);
    for (int i = en[R] + 1; i <= r; ++i) t[id].add(ar[i]);
    int ans = t[id].get();
    for (int i = l; i < st[L]; ++i) t[id].del(ar[i]);
    for (int i = en[R] + 1; i <= r; ++i) t[id].del(ar[i]);
    return ans;
}
inline void up(int id, int in, int val) {
    t[id].del(ar[in]); t[id].add(val);
}
map <int, int> mp; int nxt = 0;
int get(int x) {
    return mp.count(x) ? mp[x] : mp[x] = ++nxt;
}

// Operation:
    cin >> n >> q;
    for (i = 0; i < n; ++i) {
        cin >> ar[i]; ar[i] = get(ar[i]);
    }
    for (i = 0; i < n; ++i) {
        if (i % B == 0) st[i / B] = i, BC++;
        if (i % B == B - 1 || i == n - 1) en[i / B] = i;
    }
    int nw = 0;
    for (i = 0; i < BC; ++i) {
        for (j = i; j < BC; ++j) {
            int id = nw; I[i * BC + j] = nw++;
            for (k = st[i]; k <= en[j]; ++k) t[id].add(ar[k]);
        }
    }
    while(q--) {
        int ty; cin >> ty;
        if (ty == 1) {
            int l, r; cin >> l >> r; --l; --r;
            cout << query(l, r) << '\n';
        }
        else {
            int in, val; cin >> in >> val; --in;
            val = get(val);
            for (i = 0; i < BC; ++i) {
                for (j = i; j < BC; ++j) {
                    if (st[i] <= in && in <= en[j]) up(I[i * BC + j], in, val);
                }
            }
            ar[in] = val;
        }
    }

// https://codeforces.com/contest/940/problem/F

// MO on Tree:

// unique elements on the path from u to v
vector<int> g[N]; int st[N], en[N], T, par[N][20], dep[N], id[N << 1];
void dfs(int u, int p = 0) {
    st[u] = ++T; id[T] = u; dep[u] = dep[p] + 1; par[u][0] = p;
    for (int k = 1; k < 20; ++k) par[u][k] = par[par[u][k - 1]][k - 1];
    for (auto v : g[u]) if (v != p) dfs(v, u);
    en[u] = ++T; id[T] = u;
}
int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int k = 19; k >= 0; --k) if (dep[par[u][k]] >= dep[v]) u = par[u][k];
    if (u == v) return u;
    for (int k = 19; k >= 0; --k) if (par[u][k] != par[v][k]) u = par[u][k], v = par[v][k];
    return par[u][0];
}
int cnt[N], ar[N], ans;
inline void add(int u) {
    int x = ar[u]; if (cnt[x]++ == 0) ans++;
}
inline void rem(int u) {
    int x = ar[u]; if (--cnt[x] == 0) ans--;
}
bool vis[N];
inline void yo(int u) {
    if (!vis[u]) add(u); else rem(u); vis[u] ^= 1;
}
const int B = 320;
struct query {
int l, r, id;
bool operator < (const query &x) const {
    if (l / B == x.l / B) return r < x.r; return l / B < x.l / B;
}
} Q[N];
int res[N];

// Operation:
    while(cin >> n >> q) {
        for (i = 1; i <= n; ++i) cin >> ar[i];
        map<int, int> mp;
        for (i = 1; i <= n; ++i) {
            if (mp.find(ar[i]) == mp.end()) mp[ar[i]], mp[ar[i]] = mp.size();
            ar[i] = mp[ar[i]];
        }
        for (int i = 1; i < n; ++i) {
            int u, v; cin >> u >> v;
            g[u].push_back(v); g[v].push_back(u);
        }
        T = 0; dfs(1);
        for (i = 1; i <= q; ++i) {
            int u, v ; cin >> u >> v;
            if (st[u] > st[v]) swap(u, v);
            int lc = lca(u, v);
            if (lc == u) Q[i].l = st[u], Q[i].r = st[v];
            else Q[i].l = en[u], Q[i].r = st[v];
            Q[i].id = i;
        }
        sort(Q + 1, Q + q + 1);
        ans = 0; int l = 1, r = 0;
        for (i = 1; i <= q; ++i) {
            int L = Q[i].l, R = Q[i].r;
            if (R < l) {
                while (l > L) yo(id[--l]);
                while (l < L) yo(id[l++]);
                while (r < R) yo(id[++r]);
                while (r > R) yo(id[r--]);
            }
            else {
                while (r < R) yo(id[++r]);
                while (r > R) yo(id[r--]);
                while (l > L) yo(id[--l]);
                while (l < L) yo(id[l++]);
            }
            int u = id[l], v = id[r], lc = lca(u, v);
            if (lc != u && lc != v) yo(lc); //take care of the lca separately
            res[Q[i].id] = ans;
            if (lc != u && lc != v) yo(lc);
        }
        for (i = 1; i <= q; ++i) cout << res[i] << '\n';
        for (i = 0; i <= n; ++i) {
            g[i].clear(); vis[i] = cnt[i] = 0;
            for (k = 0; k < 20; ++k) par[i][k] = 0;
        }
    }

// https://www.spoj.com/problems/COT2/

// MO with DSU:
// Given n vertices and m edges perform q queries of type (l,r)
// output the number of connected components if we added edges i such that l<=i<=r
// This code runs for 1 <= n, m, q <= 2e5 in 2 seconds
struct query {
int l, r, idx;
query() { l = r = idx = 0; }
query(int _l, int _r, int _idx) { l = _l; r = _r; idx = _idx; }
};
struct persistent_dsu {
struct state {
    int u, ru, v, rv;
    state() { u = ru = v = rv = 0; }
    state(int _u, int _ru, int _v, int _rv) {
        u = _u; ru = _ru; v = _v; rv = _rv;
    }
};
int cnt, depth[N], par[N];
stack<state> st;
persistent_dsu() {
    cnt = 0; memset(depth, 0, sizeof(depth));
    memset(par, 0, sizeof(par)); while(!st.empty()) st.pop();
}
void init(int _sz) {
    cnt = _sz;
    for (int i = 0; i <= _sz; ++i) par[i] = i, depth[i] = 1;
}
int root(int x) {
    if (x == par[x]) return x; return root(par[x]);
}
bool connected(int x, int y) { return root(x) == root(y); }

void unite(int x, int y) {
    int rx = root(x), ry = root(y);
    if (rx == ry) return;
    if (depth[rx] < depth[ry]) par[rx] = ry;
    else if (depth[ry] < depth[rx]) par[ry] = rx;
    else par[rx] = ry, depth[ry]++;
    cnt--; st.push(state(rx, depth[rx], ry, depth[ry]));
}
void snapshot() { st.push(state(-1, -1, -1, -1)); }
void rollback() {
    while(!st.empty()) {
        if (st.top().u == -1) return;
        ++cnt;
        par[st.top().u] = st.top().u;
        par[st.top().v] = st.top().v;
        depth[st.top().u] = st.top().ru;
        depth[st.top().v] = st.top().rv;
        st.pop();
    }
}
};
struct edge {
int u, v; edge() { u = v = 0; }
edge(int _u, int _v) { u = _u; v = _v; }
};
int n, ed, m; edge ar[N]; query q[N];
void read() {
    cin >> n >> ed >> m;
    for (int i = 1; i <= ed; ++i) {
        int u, v; cin >> u >> v; ar[i] = edge(u, v);
    }
}
int rt, cnt_q; persistent_dsu d;
bool cmp(query fir, query sec) {
    if (fir.l / rt != sec.l / rt) return fir.l / rt < sec.l / rt;
    return fir.r < sec.r;
}
int answer[N];
void add(int idx) { d.unite(ar[idx].u, ar[idx].v); }

// Operation:
    read();
    d.init(n); d.snapshot();
    rt = sqrt(ed); cnt_q = 0; int fm = m;
    for (i = 0; i < m; ++i) {
        int l, r; cin >> l >> r;
        if (r - l + 1 <= rt) {
            for (k = l; k <= r; ++k) add(k);
            answer[i] = d.cnt; d.rollback(); continue;
        }
        q[cnt_q++] = query(l, r, i);
    }
    m = cnt_q; sort(q, q + m, cmp);
    int lst, border, lstblk = -1, bs;
    for (i = 0; i < m; ++i) {
        bs = q[i].l / rt;
        if (lstblk != bs) {
            d.init(n); border = rt * (bs + 1); lst = border;
        }
        lstblk = bs;
        for (k = lst + 1; k <= q[i].r; ++k) add(k);
        d.snapshot();
        for (k = q[i].l; k <= border; ++k) add(k);
        answer[q[i].idx] = d.cnt; d.rollback(); lst = q[i].r;
    }
    for (i = 0; i < fm; ++i) cout << answer[i] << '\n';

// https://www.codechef.com/problems/GERALD07

// MO with Update:

const int N = 2e5 + 9, B = 2500;
struct query {
int l, r, t, id;
bool operator < (const query &x) const {
    if (l / B == x.l / B) {
        if (r / B == x.r / B) return t < x.t;
        return r / B < x.r / B;
    }
    return l / B < x.l / B;
}
} Q[N];
struct upd { int pos, old, cur; } U[N];
int ar[N], cnt[N], f[N], ans[N], l, r, t;
inline void add(int x) {
    f[cnt[x]]--, ++cnt[x], f[cnt[x]]++;
}
inline void del(int x) {
    f[cnt[x]]--, --cnt[x], f[cnt[x]]++;
}
inline void up(int pos, int x) {
    if (l <= pos && pos <= r) {
        add(x); del(ar[pos]);
    }
    ar[pos] = x;
}
map <int, int> mp; int nxt = 0;
int get(int x) {
    return mp.count(x) ? mp[x] : mp[x] = ++nxt;
}

// Operation:
    cin >> n >> q;
    for (i = 1; i <= n; ++i) {
        cin >> ar[i]; ar[i] = get(ar[i]);
    }
    int nq = 0, nu = 0;
    for (i = 1; i <= q; ++i) {
        int ty, l, r; cin >> ty >> l >> r;
        if (ty == 1) ++nq, Q[nq] = {l, r, nu, nq};
        else ++nu, U[nu].pos = l, U[nu].old = ar[l], ar[l] = get(r), U[nu].cur = ar[l];
    }
    sort(Q + 1, Q + nq + 1); t = nu, l = 1, r = 0;
    for (i = 1; i <= nq; ++i) {
        int L = Q[i].l, R = Q[i].r, T = Q[i].t;
        while(t < T) t++, up(U[t].pos, U[t].cur);
        while(t > T) up(U[t].pos, U[t].old), t--;
        if (R < l) {
            while(l > L) add(ar[--l]);
            while(l < L) del(ar[l++]);
            while(r < R) add(ar[++r]);
            while(r > R) del(ar[r--]);
        }
        else {
            while(r < R) add(ar[++r]);
            while(r > R) del(ar[r--]);
            while(l > L) add(ar[--l]);
            while(l < L) del(ar[l++]);
        }
        int cur = 1; while(f[cur] > 0) cur++;
        ans[Q[i].id] = cur;
    }
    for (i = 1; i <= nq; ++i) cout << ans[i] << '\n';

// https://codeforces.com/contest/940/problem/F

// 4D MO:

struct ST { // add, del and query for the element that occurs the maximum number of times
static const int B = 1000;
int c[N], cc[N / B + 2][N], mx[N / B + 2];
ST() {
    memset(c, 0, sizeof c);
    memset(cc, 0, sizeof cc);
    memset(mx, 0, sizeof mx);
}
void add(int x) {
    cc[x / B][c[x]]--; c[x]++; cc[x / B][c[x]]++;
    mx[x / B] = max(mx[x / B], c[x]);
}
void del(int x) {
    if (mx[x / B] == c[x] and cc[x / B][c[x]] == 1) mx[x / B]--;
    cc[x / B][c[x]]--; c[x]--; cc[x / B][c[x]]++;
}
int query() {
    int mx_oc = 0;
    for (int i = 0; i <= N / B; ++i) mx_oc = max(mx_oc, mx[i]);
    for (int i = 0; i <= N / B; ++i) {
        if (mx[i] == mx_oc) {
            for (int j = 0; j < B; ++j) {
                if (c[i * B + j] == mx_oc) return i * B + j;
            }
            assert(0);
        }
    }
    return 0;
}
};

const int B = 5000;
struct query {
int l1, r1, l2, r2, id;
bool operator < (const query &x) const {
    array<int, 7> a({l1 / B, r1 / B, l2 / B, r2, l1, r1, l2});
    array<int, 7> b({x.l1 / B, x.r1 / B, x.l2 / B, x.r2, x.l1, x.r1, x.l2});
    return a < b;
}
} Q[N];

int st[N], en[N], T, ar[N], b[N]; vector<int> g[N];
void dfs(int u, int p = 0) {
    st[u] = ++T; ar[T] = b[u];
    for (auto v: g[u]) {
        if (v ^ p) dfs(v, u);
    }
    en[u] = T;
}

ST t;
void add(int i) {
    t.add(ar[i]);
}
void del(int i) {
    t.del(ar[i]);
}
int ans[N];

// Operation:
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> b[i];
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        g[u].push_back(v); g[v].push_back(u);
    }
    dfs(1);
    int q; cin >> q;
    for (int i = 1; i <= q; ++i) {
        int u, v; cin >> u >> v;
        int l1 = st[u], r1 = en[u], l2 = st[v], r2 = en[v];
        Q[i] = {l1, r1, l2, r2, i};
    }
    sort(Q + 1, Q + q + 1);
    int cl1 = 1, cr1 = 1, cl2 = 1, cr2 = 1;
    add(cl1); add(cl2);
    for (int i = 1; i <= q; ++i) {
        auto [l1, r1, l2, r2, id] = Q[i];
        while (cr1 < r1) {
            ++cr1; add(cr1);
        }
        while (cl1 > l1) {
            --cl1; add(cl1);
        }
        while (cr1 > r1) {
            del(cr1); --cr1;
        }
        while (cl1 < l1) {
            del(cl1); ++cl1;
        }
        while (cr2 < r2) {
            ++cr2; add(cr2);
        }
        while (cl2 > l2) {
            --cl2; add(cl2);
        }
        while (cr2 > r2) {
            del(cr2); --cr2;
        }
        while (cl2 < l2) {
            del(cl2); ++cl2;
        }
        ans[id] = t.query();
    }
    for (int i = 1; i <= q; ++i)
        cout << ans[i] << '\n';

// Problem: https://codeforces.com/contest/1767/problem/F
