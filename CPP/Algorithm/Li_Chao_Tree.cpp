#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll inf = 2e18;

struct Line
{
    ll m, c;
    ll eval(ll x)
    {
        return m * x + c;
    }
};
struct node
{
    Line line;
    node *left = nullptr;
    node *right = nullptr;
    node(Line line) : line(line) {}
    void add_segment(Line nw, int l, int r, int L, int R)
    {
        if (l > r || r < L || l > R)
            return;
        int m = (l + 1 == r ? l : (l + r) / 2);
        if (l >= L and r <= R)
        {
            bool lef = nw.eval(l) < line.eval(l);
            bool mid = nw.eval(m) < line.eval(m);
            if (mid)
                swap(line, nw);
            if (l == r)
                return;
            if (lef != mid)
            {
                if (left == nullptr)
                    left = new node(nw);
                else
                    left->add_segment(nw, l, m, L, R);
            }
            else
            {
                if (right == nullptr)
                    right = new node(nw);
                else
                    right->add_segment(nw, m + 1, r, L, R);
            }
            return;
        }
        if (max(l, L) <= min(m, R))
        {
            if (left == nullptr)
                left = new node({0, inf});
            left->add_segment(nw, l, m, L, R);
        }
        if (max(m + 1, L) <= min(r, R))
        {
            if (right == nullptr)
                right = new node({0, inf});
            right->add_segment(nw, m + 1, r, L, R);
        }
    }
    ll query_segment(ll x, int l, int r, int L, int R)
    {
        if (l > r || r < L || l > R)
            return inf;
        int m = (l + 1 == r ? l : (l + r) / 2);
        if (l >= L and r <= R)
        {
            ll ans = line.eval(x);
            if (l < r)
            {
                if (x <= m && left != nullptr)
                    ans = min(ans, left->query_segment(x, l, m, L, R));
                if (x > m && right != nullptr)
                    ans = min(ans, right->query_segment(x, m + 1, r, L, R));
            }
            return ans;
        }
        ll ans = inf;
        if (max(l, L) <= min(m, R))
        {
            if (left == nullptr)
                left = new node({0, inf});
            ans = min(ans, left->query_segment(x, l, m, L, R));
        }
        if (max(m + 1, L) <= min(r, R))
        {
            if (right == nullptr)
                right = new node({0, inf});
            ans = min(ans, right->query_segment(x, m + 1, r, L, R));
        }
        return ans;
    }
};

struct LiChaoTree
{
    int L, R;
    node *root;
    LiChaoTree() : L(numeric_limits<int>::min() / 2), R(numeric_limits<int>::max() / 2), root(nullptr) {}
    LiChaoTree(int L, int R) : L(L), R(R)
    {
        root = new node({0, inf});
    }
    void add_line(Line line)
    {
        root->add_segment(line, L, R, L, R);
    }
    // y = mx + b: x in [l, r]
    void add_segment(Line line, int l, int r)
    {
        root->add_segment(line, L, R, l, r);
    }
    ll query(ll x)
    {
        return root->query_segment(x, L, R, L, R);
    }
    ll query_segment(ll x, int l, int r)
    {
        return root->query_segment(x, l, r, L, R);
    }
};

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    LiChaoTree t = LiChaoTree((int)-1e9, (int)1e9);
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++)
    {
        ll l, r, a, b;
        cin >> l >> r >> a >> b;
        r--;
        t.add_segment({a, b}, l, r);
    }
    while (q--)
    {
        int ty;
        cin >> ty;
        if (ty == 0)
        {
            ll l, r, a, b;
            cin >> l >> r >> a >> b;
            r--;
            t.add_segment({a, b}, l, r);
        }
        else
        {
            ll x;
            cin >> x;
            ll ans = t.query(x);
            if (ans >= inf)
                cout << "INFINITY\n";
            else
                cout << ans << '\n';
        }
    }
    return 0;
}
// https://judge.yosupo.jp/problem/segment_add_get_min

// Persistent Li Chao Tree:

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define eb emplace_back
#define nl '\n'
#define deb(x) cerr << #x " = " << x << nl
#define in() ({ int a ; scanf("%d", &a); a; })

const int N = 1e5 + 9;
const int mod = 1e9 + 7;

struct Line
{
    ll k, d;
    ll eval(ll x)
    {
        return k * x + d;
    }
};

struct LiChaoNode
{
    Line line;
    int l, r;
    LiChaoNode()
    {
        line = Line({0, numeric_limits<long long>::max() / 2});
        l = 0, r = 0;
    }
    LiChaoNode(Line line) : line(line), l(0), r(0) {}
} t[50 * N];

int T;
int upd(int pre, Line nw, int l, int r)
{
    int m = (l + r) / 2;
    int id = ++T;
    t[id].line = t[pre].line;
    bool lef = nw.eval(l) < t[id].line.eval(l);
    bool mid = nw.eval(m) < t[id].line.eval(m);
    if (mid)
        swap(t[id].line, nw);
    if (l == r)
        return id;
    if (lef != mid)
    {
        if (!t[pre].l)
            t[id].l = ++T, t[T] = LiChaoNode(nw);
        else
            t[id].l = upd(t[pre].l, nw, l, m);
        t[id].r = t[pre].r;
    }
    else
    {
        if (!t[pre].r)
            t[id].r = ++T, t[T] = LiChaoNode(nw);
        else
            t[id].r = upd(t[pre].r, nw, m + 1, r);
        t[id].l = t[pre].l;
    }
    return id;
}

ll Query(int cur, int x, int l, int r)
{
    ll val = t[cur].line.eval(x);
    int m = (l + r) / 2;
    if (l < r)
    {
        if (x <= m && t[cur].l)
            val = min(val, Query(t[cur].l, x, l, m));
        if (x > m && t[cur].r)
            val = min(val, Query(t[cur].r, x, m + 1, r));
    }
    return val;
}

struct PersistentLiChaoTree
{
    int L, R;
    vector<int> roots;
    PersistentLiChaoTree()
    {
        roots = {1};
        T = 1;
        L = -1e9;
        R = 1e9;
    }
    PersistentLiChaoTree(int L, int R) : L(L), R(R)
    {
        T = 1;
        roots.push_back(1);
    }
    void add_line(Line line)
    {
        int root = upd(roots.back(), line, L, R);
        roots.push_back(root);
    }
    ll query(int i, int x)
    {
        return Query(roots[i], x, L, R);
    }
} lt;

ll sum[N];
vector<pair<int, int>> g[N];
void dfs(int u, int pre = 0)
{
    for (auto x : g[u])
    {
        int v = x.first, d = x.second;
        if (v == pre)
            continue;
        sum[v] = sum[u] + d;
        dfs(v, u);
    }
}
ll ans[N], p[N], s[N];
void yo(int u, int pre = 0)
{
    for (auto x : g[u])
    {
        int v = x.first;
        if (v == pre)
            continue;
        ans[v] = lt.query((int)lt.roots.size() - 1, p[v]) + sum[v] * p[v] + s[v];
        int sz = lt.roots.size();
        lt.add_line({-sum[v], ans[v]});
        yo(v, u);
        lt.roots.pop_back();
    }
}
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int u, v, d;
        cin >> u >> v >> d;
        g[u].eb(v, d);
        g[v].eb(u, d);
    }
    for (int i = 2; i <= n; i++)
        cin >> s[i] >> p[i];
    dfs(1);
    T = 0;
    lt = PersistentLiChaoTree((ll)-1e9 - 10, (ll)1e9 + 10);
    lt.add_line({0, 0});
    yo(1);
    for (int i = 2; i <= n; i++)
    {
        if (i > 2)
            cout << ' ';
        cout << ans[i];
    }
    cout << nl;
    return 0;
}