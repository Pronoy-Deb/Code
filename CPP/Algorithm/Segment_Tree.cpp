// WITHOUT lazy Propagation:
// Complexity: Constructing the tree: O(n), Update & Query: O(log(n))

long long tre[N << 1], ar[N], n;
long long com(long long x, long long y) { return x + y; }
void make() {
    for (int i = 0; i < n; ++i) tre[i + n] = ar[i];
    for (int i = n - 1; i > 0; --i) tre[i] = com(tre[i << 1], tre[i << 1 | 1]);
}
void up(int in, long long val) {
    for (tre[in += n] = val; in > 1; in >>= 1) tre[in >> 1] = com(tre[in], tre[in ^ 1]);
}
long long get(int l, int r) {
    long long res = 0;
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = com(res, tre[l++]); if (r & 1) res = com(res, tre[--r]);
    }
    return res;
}

// WITH lazy Propagation: O(n)

long long tre[N << 1], lz[N], ar[N], n;
long long com(long long x, long long y) { return x + y; }
void make() {
    for (int i = 0; i < n; ++i) tre[i + n] = ar[i];
    for (int i = n - 1; i > 0; --i) tre[i] = com(tre[i << 1], tre[i << 1 | 1]);
}
void apply(int in, long long val, int k) {
    tre[in] += val * k; if (in < n) lz[in] += val;
}
void push(int l, int r) {
    int s = (sizeof(int) << 3) - __builtin_clz(n), k = 1 << (s - 1);
    for (l += n, r += n - 1; s > 0; --s, k >>= 1) {
        for (int i = l >> s; i <= r >> s; ++i) {
            if (lz[i]) {
                apply(i << 1, lz[i], k); apply(i << 1 | 1, lz[i], k); lz[i] = 0;
            }
        }
    }
}
void rebuild(int l, int r) {
    int k = 2;
    for (l += n, r += n - 1; l > 1; k <<= 1) {
        l >>= 1, r >>= 1;
        for (int i = r; i >= l; --i) tre[i] = com(tre[i << 1], tre[i << 1 | 1]) + lz[i] * k;
    }
}
void add(int l, int r, long long val) {
    push(l, l + 1); push(r, ++r); int l0 = l, r0 = r, k = 1;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1) {
        if (l & 1) apply(l++, val, k); if (r & 1) apply(--r, val, k);
    }
    rebuild(l0, l0 + 1); rebuild(r0 - 1, r0);
}
long long get(int l, int r) {
    push(l, l + 1); push(r, ++r); long long res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = com(res, tre[l++]); if (r & 1) res = com(res, tre[--r]);
    }
    return res;
}

// OR,

long long tre[N << 2], lz[N << 2], ar[N], n;
long long com(long long x, long long y) { return x + y; }
void make(int nd = 1, int s = 0, int e = n - 1) {
    if (s >= e) { if (s == e) tre[nd] = ar[s]; return; }
    int m = (s + e) >> 1, lc = nd << 1, rc = lc | 1;
    make(lc, s, m); make(rc, m + 1, e); tre[nd] = com(tre[lc], tre[rc]);
}
void propagate(int nd, int s, int e) {
    if (lz[nd]) {
        tre[nd] += (e - s + 1) * lz[nd];
        if (s != e) { lz[nd << 1] += lz[nd]; lz[nd << 1 | 1] += lz[nd]; }
        lz[nd] = 0;
    }
}
void add(int l, int r, long long val, int nd = 1, int s = 0, int e = n - 1) {
    propagate(nd, s, e); if (s > e || s > r || e < l) return;
    int m = (s + e) >> 1, lc = nd << 1, rc = lc | 1;
    if (s >= l && e <= r) { lz[nd] += val; propagate(nd, s, e); return; }
    add(l, r, val, lc, s, m); add(l, r, val, rc, m + 1, e);
    tre[nd] = com(tre[lc], tre[rc]);
}
long long get(int l, int r, int nd = 1, int s = 0, int e = n - 1) {
    propagate(nd, s, e); if (s > e || s > r || e < l) return 0;
    if (s >= l && e <= r) return tre[nd];
    int m = (s + e) >> 1, lc = nd << 1, rc = lc | 1;
    return com(get(l, r, lc, s, m), get(l, r, rc, m + 1, e));
}
void reset() { for (int i = 0; i < (n << 2) + 5; ++i) tre[i] = lz[i] = 0; }

// Persistent Segment Tree:
// Problem: https://www.spoj.com/problems/MKTHNUM/

struct node {
    long long l = 0, r = 0, val = 0;
} tre[N * 20];
int ptr = 0, n;
int make(int s = 1, int e = n) {
    int cur = ++ptr; if (s == e) return cur;
    long long m = s + e >> 1, &lc = tre[cur].l, &rc = tre[cur].r;
    lc = make(s, m); rc = make(m + 1, e);
    tre[cur].val = tre[lc].val + tre[rc].val;
    return cur;
}
int up(int pre, int i, int v, int s = 1, int e = n) {
    int cur = ++ptr; tre[cur] = tre[pre];
    if (s == e) { tre[cur].val += v; return cur; }
    long long m = s + e >> 1, &lc = tre[cur].l, &rc = tre[cur].r;
    if (i <= m) { rc = tre[pre].r; lc = up(tre[pre].l, i, v, s, m); }
    else { lc = tre[pre].l; rc = up(tre[pre].r, i, v, m + 1, e); }
    tre[cur].val = tre[lc].val + tre[rc].val;
    return cur;
}
// Finding the k-th number in a range l to r if the range were sorted
long long get(int pre, int cur, int k, int s = 1, int e = n) {
    if (s == e) return s;
    long long m = s + e >> 1, lc = tre[cur].l, rc = tre[cur].r, cnt = tre[lc].val - tre[tre[pre].l].val;
    if (cnt >= k) return get(tre[pre].l, lc, k, s, m);
    return get(tre[pre].r, rc, k - cnt, m + 1, e);
}

// Operation:
    cin >> n >> q;
    long long ar[n + 5], root[n + 5]; map<long long, long long> mp, V;
    for (i = 1; i <= n; ++i) cin >> ar[i], mp[ar[i]];
    for (auto &x : mp) mp[x.first] = ++c, V[c] = x.first;
    root[0] = make();
    for (i = 1; i <= n; ++i) root[i] = up(root[i - 1], mp[ar[i]], 1);
    while (q--) {
        int l, r, k; cin >> l >> r >> k;
        cout << V[get(root[l - 1], root[r], k)] << '\n';
    }

// Persistent Segment Tree with Lazy Propagation:
// https://www.codechef.com/problems/SUBINVER

template <const int32_t MOD>
struct modint {
    int32_t val; modint() = default;
    modint(int32_t value) : val(value) {} // make sure value is less than M
    inline modint<MOD> operator+(modint<MOD> other) const { int32_t c = this->val + other.val; return modint<MOD>(c >= MOD ? c - MOD : c); }
    inline modint<MOD> operator-(modint<MOD> other) const { int32_t c = this->val - other.val; return modint<MOD>(c < 0 ? c + MOD : c); }
    inline modint<MOD> operator*(modint<MOD> other) const { int32_t c = (int64_t)this->val * other.val % MOD; return modint<MOD>(c < 0 ? c + MOD : c); }
    inline modint<MOD> &operator+=(modint<MOD> other) { this->val += other.val; if (this->val >= MOD) this->val -= MOD; return *this; }
    inline modint<MOD> &operator-=(modint<MOD> other) { this->val -= other.val; if (this->val < 0) this->val += MOD; return *this; }
    inline modint<MOD> &operator*=(modint<MOD> other) { this->val = (int64_t)this->val * other.val % MOD; if (this->val < 0) this->val += MOD; return *this; }
    inline modint<MOD> operator-() const { return modint<MOD>(this->val ? MOD - this->val : 0); }
    modint<MOD> pow(uint64_t k) const { modint<MOD> x = *this, y = 1; for (; k; k >>= 1) { if (k & 1) y *= x; x *= x; } return y; }
    modint<MOD> inv() const { return pow(MOD - 2); } // M must be a prime
    inline modint<MOD> operator/(modint<MOD> other) const { return *this * other.inv(); }
    inline modint<MOD> operator/=(modint<MOD> other) { return *this *= other.inv(); }
    inline bool operator==(modint<MOD> other) const { return val == other.val; }
    inline bool operator!=(modint<MOD> other) const { return val != other.val; }
    inline bool operator<(modint<MOD> other) const { return val < other.val; }
    inline bool operator>(modint<MOD> other) const { return val > other.val; }
};
template <int32_t MOD> modint<MOD> operator*(int64_t val, modint<MOD> n) { return modint<MOD>(val) * n; }
template <int32_t MOD> modint<MOD> operator*(int32_t val, modint<MOD> n) { return modint<MOD>(val % MOD) * n; }
template <int32_t MOD> istream &operator>>(istream &in, modint<MOD> &n) { return in >> n.val; }
template <int32_t MOD> ostream &operator<<(ostream &out, modint<MOD> n) { return out << n.val; }
using mint = modint<M>;

mint ar[N], P = 37;
struct node {
    int l = 0, r = 0, lz = 0, p = 0; mint val = 0;
} tre[N * 300];
int T = 0;
int make(int s, int e) {
    int cur = ++T; if (s == e) return cur;
    int m = s + e >> 1, &lc = tre[cur].l, &rc = tre[cur].r;
    lc = make(s, m); rc = make(m + 1, e); return cur;
}
int push(int pre, int s, int e, int x = 0) {
    int cur = ++T; tre[cur] = tre[pre]; tre[cur].lz ^= x;
    if (tre[cur].lz) {
        tre[cur].val = ar[e] - ar[s - 1] - tre[cur].val;
        tre[cur].p ^= 1;
        if (s != e) {
            auto &lc = tre[cur].l, &rc = tre[cur].r;
            lc = ++T; rc = ++T;
            tre[lc] = tre[tre[pre].l];
            tre[rc] = tre[tre[pre].r];
            tre[lc].lz ^= 1, tre[rc].lz ^= 1;
        }
    }
    tre[cur].lz = 0; return cur;
}
int up(int pre, int s, int e, int i, int j) {
    int cur = push(pre, s, e);
    if (s > j || e < i) return cur;
    if (i <= s && e <= j) { cur = push(cur, s, e, 1); return cur; }
    int m = s + e >> 1, &lc = tre[cur].l, &rc = tre[cur].r;
    lc = up(lc, s, m, i, j); rc = up(rc, m + 1, e, i, j);
    tre[cur].val = tre[lc].val + tre[rc].val; return cur;
}
int cmp(int cur, int oth, int s, int e) {
    cur = push(cur, s, e); oth = push(oth, s, e);
    if (tre[cur].val == tre[oth].val) return 0;
    if (s == e) {
        int x = tre[cur].p, y = tre[oth].p; return (x == y ? 0 : x > y ? 1 : 2);
    }
    int m = s + e >> 1, lc = tre[cur].l, rc = tre[cur].r, p = cmp(lc, tre[oth].l, s, m);
    if (p) return p; return cmp(rc, tre[oth].r, m + 1, e);
}
void print(int cur, int s, int e) {
    cur = push(cur, s, e);
    if (s == e) { cout << tre[cur].p; return; }
    int m = s + e >> 1, lc = tre[cur].l, rc = tre[cur].r;
    print(lc, s, m); print(rc, m + 1, e);
}
int root[N];

// Operation:
    for (i = 1; i < N; ++i) ar[i] = ar[i - 1] + P.pow(i);
    cin >> n >> q;
    root[0] = make(1, n); int ans = 0;
    for (i = 1; i <= q; ++i) {
        int l, r; cin >> l >> r;
        root[i] = up(root[i - 1], 1, n, l, r);
        if (cmp(root[ans], root[i], 1, n) == 2) ans = i;
    }
    print(root[ans], 1, n);

// 2D Segment Tree:

int tre[N << 2][N << 2], ar[N][N], n;
void make(int X, int xs, int xe, int Y, int ys, int ye) {
    if (ys == ye) tre[X][Y] = (xs == xe ? ar[xs][ys] : tre[(X << 1)][Y] + tre[(X << 1) + 1][Y]);
    else {
        int m = (ys + ye) >> 1, lc = (Y << 1), rc = lc + 1;
        make(X, xs, xe, lc, ys, m); make(X, xs, xe, rc, m + 1, ye);
        tre[X][Y] = tre[X][lc] + tre[X][rc];
    }
}
void make(int X, int xs, int xe) {
    if (xs != xe) {
        int m = (xs + xe) >> 1, lc = (X << 1), rc = lc + 1;
        make(lc, xs, m); make(rc, m + 1, xe);
    }
    make(X, xs, xe, 1, 1, n);
}
void up(int X, int xs, int xe, int Y, int ys, int ye, int x, int y, long long val) {
    if (ys == ye) tre[X][Y] = (xs == xe ? val : tre[(X << 1)][Y] + tre[(X << 1) + 1][Y]);
    else {
        int m = (ys + ye) >> 1, lc = (Y << 1), rc = lc + 1;
        if (y <= m) up(X, xs, xe, lc, ys, m, x, y, val);
        else up(X, xs, xe, rc, m + 1, ye, x, y, val);
        tre[X][Y] = tre[X][lc] + tre[X][rc];
    }
}
void up(int X, int xs, int xe, int x, int y, long long val) {
    if (xs != xe) {
        int m = (xs + xe) >> 1, lc = (X << 1), rc = lc + 1;
        if (x <= m) up(lc, xs, m, x, y, val);
        else up(rc, m + 1, xe, x, y, val);
    }
    up(X, xs, xe, 1, 1, n, x, y, val);
}
long long get(int X, int Y, int ys, int ye, int y1, int y2) {
    if (y2 < ys || ye < y1) return 0;
    if (y1 <= ys && ye <= y2) return tre[X][Y];
    int m = (ys + ye) >> 1, lc = (Y << 1), rc = lc + 1;
    return get(X, lc, ys, m, y1, y2) + get(X, rc, m + 1, ye, y1, y2);
}
long long get(int X, int xs, int xe, int x1, int x2, int y1, int y2) {
    if (x2 < xs || xe < x1) return 0;
    if (x1 <= xs && xe <= x2) return get(X, 1, 1, n, y1, y2);
    int m = (xs + xe) >> 1, lc = (X << 1), rc = lc + 1;
    return get(lc, xs, m, x1, x2, y1, y2) + get(rc, m + 1, xe, x1, x2, y1, y2);
}

// Operation:
    cin >> n >> q;
    for (i = 1; i <= n; ++i) {
        string row; cin >> row;
        for (j = 1; j <= n; ++j) ar[i][j] = (row[j - 1] == '*');
    }
    make(1, 1, n);
    while (q--) {
        int ty; cin >> ty;
        if (ty == 1) {
            int x, y; cin >> x >> y;
            if (ar[x][y] == 1) {
                up(1, 1, n, x, y, 0); ar[x][y] = 0;
            }
            else {
                up(1, 1, n, x, y, 1); ar[x][y] = 1;
            }
        }
        else {
            int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
            cout << get(1, 1, n, x1, x2, y1, y2) << '\n';
        }
    }


// Dynamic Segment Tree:
// Problem: https://cses.fi/problemset/task/1144

class ST {
public:
    vector<int> tree; int sz;
    ST(int n) {
        sz = n; tree.resize((n << 2), 0);
    }
    void add(int nd, int s, int e, int sz, int val) {
        if (s == e) tree[nd] += val;
        else {
            int mid = (s + e) >> 1, lc = (nd << 1), rc = lc + 1;
            if (sz <= mid) add(lc, s, mid, sz, val);
            else add(rc, mid + 1, e, sz, val);
            tree[nd] = tree[lc] + tree[rc];
        }
    }
    int get(int nd, int s, int e, int L, int R) {
        if (s > R || e < L) return 0;
        if (s >= L && e <= R) return tree[nd];
        int mid = (s + e) >> 1, lc = (nd << 1), rc = lc + 1;
        return get(lc, s, mid, L, R) + get(rc, mid + 1, e, L, R);
    }
};

// Operation:
    int n, q; cin >> n >> q;
    vector<int> sal(n); map<int, int> mp;
    for (int i = 0; i < n; ++i) {
        cin >> sal[i]; mp[sal[i]];
    }
    vector<pair<char, pair<int, int>>> query(q);
    for (int i = 0; i < q; ++i) {
        char tp; int a, b; cin >> tp >> a >> b;
        query[i] = {tp, {a, b}};
        if (tp == '?') mp[a]; mp[b];
    }
    int sz = 0; for (auto& e : mp) e.second = ++sz;
    ST tre(sz);
    for (int i = 0; i < n; ++i) tre.add(1, 1, sz, mp[sal[i]], 1);
    for (auto& e : query) {
        char tp = e.first; int a = e.second.first, b = e.second.second;
        if (tp == '!') {
            tre.add(1, 1, sz, mp[sal[--a]], -1);
            tre.add(1, 1, sz, mp[b], 1); sal[a] = b;
        }
        else cout << tre.get(1, 1, sz, mp[a], mp[b]) << '\n';
    }

// Segment Tree 2D Dynamic:

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct node {
    node *l, *r;
    int pos, key, mn, mx;
    long long val, g;
    node(int position, long long value) {
        l = r = nullptr;
        mn = mx = pos = position;
        key = rnd();
        val = g = value;
    }
    void pull()
    {
        g = val;
        if (l)
            g = __gcd(g, l->g);
        if (r)
            g = __gcd(g, r->g);
        mn = (l ? l->mn : pos);
        mx = (r ? r->mx : pos);
    }
};
// memory O(n)
struct treap
{
    node *root;
    treap()
    {
        root = nullptr;
    }
    void split(node *t, int pos, node *&l, node *&r)
    {
        if (t == nullptr)
        {
            l = r = nullptr;
            return;
        }
        if (t->pos < pos)
        {
            split(t->r, pos, l, r);
            t->r = l;
            l = t;
        }
        else
        {
            split(t->l, pos, l, r);
            t->l = r;
            r = t;
        }
        t->pull();
    }
    node *com(node *l, node *r)
    {
        if (!l || !r)
            return l ? l : r;
        if (l->key < r->key)
        {
            l->r = com(l->r, r);
            l->pull();
            return l;
        }
        r->l = com(l, r->l);
        r->pull();
        return r;
    }
    bool find(int pos)
    {
        node *t = root;
        while (t)
        {
            if (t->pos == pos)
                return true;
            if (t->pos > pos)
                t = t->l;
            else
                t = t->r;
        }
        return false;
    }
    void up(node *t, int pos, long long val)
    {
        if (t->pos == pos)
        {
            t->val = val;
            t->pull();
            return;
        }
        if (t->pos > pos)
            up(t->l, pos, val);
        else
            up(t->r, pos, val);
        t->pull();
    }
    void insert(int pos, long long val)
    { // set a_pos = val
        if (find(pos))
            up(root, pos, val);
        else
        {
            node *l, *r;
            split(root, pos, l, r);
            root = com(com(l, new node(pos, val)), r);
        }
    }
    long long get(node *t, int st, int en)
    {
        if (t->mx < st || en < t->mn)
            return 0;
        if (st <= t->mn && t->mx <= en)
            return t->g;
        long long ans = (st <= t->pos && t->pos <= en ? t->val : 0);
        if (t->l)
            ans = __gcd(ans, get(t->l, st, en));
        if (t->r)
            ans = __gcd(ans, get(t->r, st, en));
        return ans;
    }
    long long get(int l, int r)
    { // gcd of a_i such that l <= i <= r
        if (!root)
            return 0;
        return get(root, l, r);
    }
    void print(node *t)
    {
        if (!t)
            return;
        print(t->l);
        cout << t->val << " ";
        print(t->r);
    }
};
// total memory along with treap = nlogn
struct ST
{
    ST *l, *r;
    treap t;
    int b, e;
    ST()
    {
        l = r = nullptr;
    }
    ST(int st, int en)
    {
        l = r = nullptr;
        b = st, e = en;
    }
    void fix(int pos)
    {
        long long val = 0;
        if (l)
            val = __gcd(val, l->t.get(pos, pos));
        if (r)
            val = __gcd(val, r->t.get(pos, pos));
        t.insert(pos, val);
    }
    void up(int x, int y, long long val)
    { // set ar[x][y] = val
        if (e < x || x < b)
            return;
        if (b == e)
        {
            t.insert(y, val);
            return;
        }
        if (b != e)
        {
            if (x <= (b + e) / 2)
            {
                if (!l)
                    l = new ST(b, (b + e) / 2);
                l->up(x, y, val);
            }
            else
            {
                if (!r)
                    r = new ST((b + e) / 2 + 1, e);
                r->up(x, y, val);
            }
        }
        fix(y);
    }
    long long get(int i, int j, int st, int en)
    { // gcd of ar[x][y] such that i <= x <= j && st <= y <= en
        if (e < i || j < b)
            return 0;
        if (i <= b && e <= j)
            return t.get(st, en);
        long long ans = 0;
        if (l)
            ans = __gcd(ans, l->get(i, j, st, en));
        if (r)
            ans = __gcd(ans, r->get(i, j, st, en));
        return ans;
    }
};

int32_t main()
{
    int n, m;
    cin >> n >> m;
    ST t(0, n - 1);
    int q;
    cin >> q;
    while (q--)
    {
        int ty;
        cin >> ty;
        if (ty == 1)
        {
            int x, y, v;
            cin >> x >> y >> v;
            t.up(x, y, v);
        }
        else
        {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << t.get(x1, x2, y1, y2) << '\n';
        }
    }
    return 0;
}

// https://oj.uz/problem/view/IOI13_game

// Segment Tree Beats:
// https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum
// https://codeforces.com/problemset/problem/438/D

long long ar[N], n;
struct Node {
    long long sum, mx1, mx2, mxc, mn1, mn2, mnc, lz;
} tre[N << 2];
void com(int nd) {
    int lc = nd << 1, rc = lc | 1;
    tre[nd].sum = tre[lc].sum + tre[rc].sum;
    if (tre[lc].mx1 == tre[rc].mx1) {
    	tre[nd].mx1 = tre[lc].mx1;
    	tre[nd].mx2 = max(tre[lc].mx2, tre[rc].mx2);
    	tre[nd].mxc = tre[lc].mxc + tre[rc].mxc;
    }
    else {
    	if (tre[lc].mx1 > tre[rc].mx1) {
    		tre[nd].mx1 = tre[lc].mx1;
    		tre[nd].mx2 = max(tre[lc].mx2, tre[rc].mx1);
    		tre[nd].mxc = tre[lc].mxc;
    	}
        else {
    		tre[nd].mx1 = tre[rc].mx1;
    		tre[nd].mx2 = max(tre[lc].mx1, tre[rc].mx2);
    		tre[nd].mxc = tre[rc].mxc;
    	}
    }
    if (tre[lc].mn1 == tre[rc].mn1) {
    	tre[nd].mn1 = tre[lc].mn1;
    	tre[nd].mn2 = min(tre[lc].mn2, tre[rc].mn2);
    	tre[nd].mnc = tre[lc].mnc + tre[rc].mnc;
    }
    else {
    	if (tre[lc].mn1 < tre[rc].mn1) {
    		tre[nd].mn1 = tre[lc].mn1;
    		tre[nd].mn2 = min(tre[lc].mn2, tre[rc].mn1);
    		tre[nd].mnc = tre[lc].mnc;
    	}
        else {
    		tre[nd].mn1 = tre[rc].mn1;
    		tre[nd].mn2 = min(tre[lc].mn1, tre[rc].mn2);
    		tre[nd].mnc = tre[rc].mnc;
    	}
    }
}
void make(int nd = 1, int s = 0, int e = n - 1) {
    tre[nd].lz = 0;
    if (s == e) {
    	tre[nd].sum = tre[nd].mx1 = tre[nd].mn1 = ar[s];
    	tre[nd].mxc = tre[nd].mnc = 1;
    	tre[nd].mx2 = LLONG_MIN; tre[nd].mn2 = LLONG_MAX; return;
    }
    int m = (s + e) >> 1, lc = nd << 1, rc = lc | 1;
    make(lc, s, m); make(rc, m + 1, e); com(nd);
}
void push_add(int nd, int s, int e, long long v) {
    if (v == 0) return;
    tre[nd].sum += (e - s + 1) * v; tre[nd].mx1 += v;
    if (tre[nd].mx2 != LLONG_MIN) tre[nd].mx2 += v; tre[nd].mn1 += v;
    if (tre[nd].mn2 != LLONG_MAX) tre[nd].mn2 += v; tre[nd].lz += v;
}
void push_max(int nd, long long v, bool l) {
    if (v >= tre[nd].mx1) return;
    tre[nd].sum -= tre[nd].mx1 * tre[nd].mxc; tre[nd].mx1 = v;
    tre[nd].sum += tre[nd].mx1 * tre[nd].mxc;
    if (l) tre[nd].mn1 = tre[nd].mx1;
    else {
    	if (v <= tre[nd].mn1) tre[nd].mn1 = v;
        else if (v < tre[nd].mn2) tre[nd].mn2 = v;
    }
}
void push_min(int nd, long long v, bool l) {
    if (v <= tre[nd].mn1) return;
    tre[nd].sum -= tre[nd].mn1 * tre[nd].mnc; tre[nd].mn1 = v;
    tre[nd].sum += tre[nd].mn1 * tre[nd].mnc;
    if (l) tre[nd].mx1 = tre[nd].mn1;
    else {
    	if (v >= tre[nd].mx1) tre[nd].mx1 = v;
        else if (v > tre[nd].mx2) tre[nd].mx2 = v;
    }
}
void pushdown(int nd, int s, int e) {
    if (s == e) return; int m = (s + e) >> 1, lc = nd << 1, rc = lc | 1;
    push_add(lc, s, m, tre[nd].lz); push_add(rc, m + 1, e, tre[nd].lz); tre[nd].lz = 0;
    push_max(lc, tre[nd].mx1, s == m); push_max(rc, tre[nd].mx1, m + 1 == e);
    push_min(lc, tre[nd].mn1, s == m); push_min(rc, tre[nd].mn1, m + 1 == e);
}
void stmn(int l, int r, long long v, int nd = 1, int s = 0, int e = n - 1) {
    if (r < s || e < l || v >= tre[nd].mx1) return;
    if (l <= s && e <= r && v > tre[nd].mx2) { push_max(nd, v, s == e); return; }
    pushdown(nd, s, e); int m = (s + e) >> 1, lc = nd << 1, rc = lc | 1;
    stmn(l, r, v, lc, s, m); stmn(l, r, v, rc, m + 1, e); com(nd);
}
void stmx(int l, int r, long long v, int nd = 1, int s = 0, int e = n - 1) {
    if (r < s || e < l || v <= tre[nd].mn1) return;
    if (l <= s && e <= r && v < tre[nd].mn2) { push_min(nd, v, s == e); return; }
    pushdown(nd, s, e); int m = (s + e) >> 1, lc = nd << 1, rc = lc | 1;
    stmx(l, r, v, lc, s, m); stmx(l, r, v, rc, m + 1, e); com(nd);
}
void add(int l, int r, long long v, int nd = 1, int s = 0, int e = n - 1) {
    if (r < s || e < l) return;
    if (l <= s && e <= r) { push_add(nd, s, e, v); return; }
    pushdown(nd, s, e); int m = (s + e) >> 1, lc = nd << 1, rc = lc | 1;
    add(l, r, v, lc, s, m); add(l, r, v, rc, m + 1, e); com(nd);
}
long long get(int l, int r, int nd = 1, int s = 0, int e = n - 1) {
    if (r < s || e < l) return 0; if (l <= s && e <= r) return tre[nd].sum;
    pushdown(nd, s, e); int m = (s + e) >> 1, lc = nd << 1, rc = lc | 1;
    return get(l, r, lc, s, m) + get(l, r, rc, m + 1, e);
}

// Segment Tree Merging:

// works for multiple values too
struct STM
{
#define lc tre[cur].l
#define rc tre[cur].r
    struct node
    {
        int l, r, sz;
    } tre[N * 30];
    int T;
    int id[N * 30];
    STM()
    {
        T = 0;
        for (int i = 1; i < N * 30; ++i)
            id[i] = i;
    }
    inline int new_node()
    {
        int cur = id[++T];
        tre[cur].l = tre[cur].r = tre[cur].sz = 0;
        return cur;
    }
    inline void save_memory(int x)
    {
        id[T--] = x;
    }
    // create a segment tree with only node i
    int make(int b, int e, int i)
    {
        int cur = new_node();
        if (b == e)
        {
            tre[cur].sz = 1;
            return cur;
        }
        int m = b + e >> 1;
        if (i <= m)
            lc = make(b, m, i);
        else
            rc = make(m + 1, e, i);
        tre[cur].sz = tre[lc].sz + tre[rc].sz;
        return cur;
    }
    // merge segment tree a and b
    int com(int a, int b)
    {
        if (!a || !b)
            return a ^ b;
        tre[a].l = com(tre[a].l, tre[b].l);
        tre[a].r = com(tre[a].r, tre[b].r);
        tre[a].sz += tre[b].sz;
        save_memory(b);
        return a;
    }
    // split cur into cur and b so that cur contains k smallest elements
    void split(int cur, int &b, int k)
    {
        if (tre[cur].sz < k)
            return;
        b = new_node();
        int lsz = tre[lc].sz;
        if (k > lsz)
            split(rc, tre[b].r, k - lsz);
        else
            swap(rc, tre[b].r);
        if (k < lsz)
            split(lc, tre[b].l, k);
        tre[b].sz = tre[cur].sz - k;
        tre[cur].sz = k;
    }
    // k -th sorted element in cur segment tree
    int get(int cur, int b, int e, int k)
    {
        if (b == e)
            return b;
        int lsz = tre[lc].sz;
        int m = b + e >> 1;
        if (k > lsz)
            return get(rc, m + 1, e, k - lsz);
        return get(lc, b, m, k);
    }
} t;
bool ty[N]; // 0 - inc; 1 - dec
// i-th pos store a substr (l, r) such that l = i (if exists)
// roots[i] stores the root, rb[i] stores the right border
int root[N], rb[N];
set<int> cur; // maintains the left borders of ordered substrs
int n, q, ar[N];
// split (l, ...) so that rb[l] = r
void split(int l, int r)
{
    if (r >= rb[l] || r < l)
        return;
    if (!ty[l])
        t.split(root[l], root[r + 1], r - l + 1);
    else
    {
        root[r + 1] = root[l];
        t.split(root[r + 1], root[l], rb[l] - r); // checkmate
    }
    rb[r + 1] = rb[l];
    rb[l] = r;
    cur.insert(r + 1);
    ty[r + 1] = ty[l];
}
// merge adjacent substr a and b to a (ty[a] should be edited manually)
void com(int a, int b)
{
    if (a == b)
        return;
    cur.erase(b);
    root[a] = t.com(root[a], root[b]);
    rb[a] = rb[b];
}
// query for ar[k] on substr (l, ...)
int get(int l, int k)
{
    k -= l - 1;
    if (!ty[l])
        return t.get(root[l], 1, n, k);
    return t.get(root[l], 1, n, rb[l] - l + 1 - k + 1);
}
int main()
{
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &ar[i]);
        root[i] = t.make(1, n, ar[i]);
        cur.insert(i);
        rb[i] = i;
    }

    while (q--)
    {
        // sort range [l, r]
        // type: 0 - inc  1 - dec
        int type, l, r;
        scanf("%d %d %d", &type, &l, &r);
        // split l and r
        set<int>::iterator it = cur.upper_bound(l);
        split(*(--it), l - 1);
        it = cur.upper_bound(r);
        split(*(--it), r);
        // get the range
        set<int>::iterator L = cur.lower_bound(l), R = cur.upper_bound(r);
        --R;
        int nw = *L;
        vector<int> v;
        while (L != R)
        {
            ++L;
            int k = *L;
            v.push_back(k);
            if (L == R)
                break;
        }
        for (int i = 0; i < v.size(); ++i)
            com(nw, v[i]);
        ty[nw] = type;
    }
    int i;
    scanf("%d", &i); // query for the i-th position of the sequence
    set<int>::iterator it = cur.upper_bound(i);
    int l = *(--it);
    printf("%d\n", get(l, i));
    return 0;
}
// https://codeforces.com/blog/entry/49446
// http://www.lydsy.com:808/JudgeOnline/problem.php?id=4552

/*
The problem is maintaing a permutation of 1~n,
supporting range sorting (increasing or decreasing),
query the value of **one** position **after all sortings**.
*/

// Segment Tree with Arithmetic Progression:

const int N = 1010, mod = 1e9 + 7;

template <const int32_t MOD>
struct modint {
    int32_t val; modint() = default;
    modint(int32_t value) : val(value) {} // make sure value is less than M
    inline modint<MOD> operator+(modint<MOD> other) const { int32_t c = this->val + other.val; return modint<MOD>(c >= MOD ? c - MOD : c); }
    inline modint<MOD> operator-(modint<MOD> other) const { int32_t c = this->val - other.val; return modint<MOD>(c < 0 ? c + MOD : c); }
    inline modint<MOD> operator*(modint<MOD> other) const { int32_t c = (int64_t)this->val * other.val % MOD; return modint<MOD>(c < 0 ? c + MOD : c); }
    inline modint<MOD> &operator+=(modint<MOD> other) { this->val += other.val; if (this->val >= MOD) this->val -= MOD; return *this; }
    inline modint<MOD> &operator-=(modint<MOD> other) { this->val -= other.val; if (this->val < 0) this->val += MOD; return *this; }
    inline modint<MOD> &operator*=(modint<MOD> other) { this->val = (int64_t)this->val * other.val % MOD; if (this->val < 0) this->val += MOD; return *this; }
    inline modint<MOD> operator-() const { return modint<MOD>(this->val ? MOD - this->val : 0); }
    modint<MOD> pow(uint64_t k) const { modint<MOD> x = *this, y = 1; for (; k; k >>= 1) { if (k & 1) y *= x; x *= x; } return y; }
    modint<MOD> inv() const { return pow(MOD - 2); } // M must be a prime
    inline modint<MOD> operator/(modint<MOD> other) const { return *this * other.inv(); }
    inline modint<MOD> operator/=(modint<MOD> other) { return *this *= other.inv(); }
    inline bool operator==(modint<MOD> other) const { return val == other.val; }
    inline bool operator!=(modint<MOD> other) const { return val != other.val; }
    inline bool operator<(modint<MOD> other) const { return val < other.val; }
    inline bool operator>(modint<MOD> other) const { return val > other.val; }
};
template <int32_t MOD> modint<MOD> operator*(int64_t val, modint<MOD> n) { return modint<MOD>(val) * n; }
template <int32_t MOD> modint<MOD> operator*(int32_t val, modint<MOD> n) { return modint<MOD>(val % MOD) * n; }
template <int32_t MOD> istream &operator>>(istream &in, modint<MOD> &n) { return in >> n.val; }
template <int32_t MOD> ostream &operator<<(ostream &out, modint<MOD> n) { return out << n.val; }
using mint = modint<M>;

struct ST
{
    struct Int
    { // arithmetic progression a, a + d, a + 2 * d, ...
        mint a = 0, d = 0;
        Int() {};
        Int(mint _a, mint _d) { a = _a, d = _d; }
        mint at(mint n) { return (a + (n - 1) * d); }
        Int shift(mint n) { return Int((a + (n - 1) * d), d); }
        mint get_get(mint n) { return (((a * 2) + (n - 1) * d) * n) * ((mod + 1) / 2); }
        const Int operator+(const Int &b) const
        {
            return Int(a + b.a, d + b.d);
        }
    };
    mint tre[N << 2];
    Int lazy[N << 2];
    ST()
    {
        memset(t, 0, sizeof t);
        memset(lazy, 0, sizeof lazy);
    }
    void push(int n, int b, int e)
    {
        if (lazy[n].a == 0 && lazy[n].d == 0)
            return;
        tre[n] += lazy[n].get_get(e - b + 1);
        if (b != e)
        {
            lazy[n << 1] = lazy[n << 1] + lazy[n];
            lazy[n << 1 | 1] = lazy[n << 1 | 1] + lazy[n].shift(((b + e) >> 1) + 2 - b);
        }
        lazy[n] = Int(0, 0);
    }
    void make(int n, int b, int e)
    {
        lazy[n] = Int(0, 0);
        if (b == e)
        {
            tre[n] = 0;
            return;
        }
        int m = b + e >> 1, l = n << 1, r = n << 1 | 1;
        make(l, b, m);
        make(r, m + 1, e);
        tre[n] = tre[l] + tre[r];
    }
    void upd(int n, int b, int e, int i, int j, pair<mint, mint> v)
    {
        push(n, b, e);
        if (b > j || e < i)
            return;
        if (i <= b && e <= j)
        {
            Int temp(v.first, v.second);
            lazy[n] = lazy[n] + temp.shift(b - i + 1);
            push(n, b, e);
            return;
        }
        int m = b + e >> 1, l = n << 1, r = n << 1 | 1;
        upd(l, b, m, i, j, v);
        upd(r, m + 1, e, i, j, v);
        tre[n] = tre[l] + tre[r];
    }
    mint get(int n, int b, int e, int i, int j)
    {
        push(n, b, e);
        if (e < i || b > j)
            return 0;
        if (i <= b && e <= j)
            return tre[n];
        int m = b + e >> 1, l = n << 1, r = n << 1 | 1;
        return get(l, b, m, i, j) + get(r, m + 1, e, i, j);
    }
};

int n;
int C(int i)
{
    return i * (i + 1) / 2;
}
mint g[N][N];
ST t;
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int k;
    cin >> n >> k;
    vector<mint> a(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        cin >> ar[i];
    }
    for (int w = 0; w < k; w++)
    {
        t.make(1, 1, n);
        for (int i = 1; i <= n; ++i)
        {
            t.upd(1, 1, n, i, i, {ar[i] * (C(i - 1) + C(n - i)), 0});
            if (i * 2 <= n)
            {
                int j = n - i + 1;
                t.upd(1, 1, n, j, n, {ar[i] * (n - j + 1), mint(mod) - ar[i]});
                if (i < j)
                    t.upd(1, 1, n, i, j - 1, {ar[i] * i, 0});

                if (i > 1)
                    t.upd(1, 1, n, 1, i - 1, {ar[i], ar[i]});
            }
            else
            {
                if (i < n)
                    t.upd(1, 1, n, i + 1, n, {ar[i] * (n - i), mint(mod) - ar[i]});

                int j = n - i + 1;
                t.upd(1, 1, n, 1, j, {ar[i], ar[i]});
                if (j < i)
                    t.upd(1, 1, n, j + 1, i, {ar[i] * (n - i + 1), 0});
            }
        }
        for (int i = 1; i <= n; ++i)
        {
            ar[i] = t.get(1, 1, n, i, i);
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        cout << ar[i] / mint(C(n)).pow(k) << ' ';
    }
    cout << '\n';
    return 0;
}

// https://www.codechef.com/problems/RVRSE