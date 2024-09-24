/**
Linear Convex Hull Trick
Requirement:
    Minimum:
        M increasing, x decreasing, useless(s-1, s-2, s-3)
        M decreasing, x increasing, useless(s-3, s-2, s-1)
    Maximum:
        M increasing, x increasing, useless(s-3, s-2, s-1)
        M decreasing, x decreasing, useless(s-1, s-2, s-3)
**/

struct CHT
{
    vector<long long> M, C;
    long long ptr = 0;
    /// Use double comp if M, C is long long range
    bool useless(long long l1, long long l2, long long l3)
    {
        return (1.0 * (C[l3] - C[l1]) * (M[l1] - M[l2]) >= 1.0 * (C[l2] - C[l1]) * (M[l1] - M[l3]));
    }
    long long f(long long id, long long x) { return M[id] * x + C[id]; }
    void add(long long m, long long c)
    {
        M.push_back(m);
        C.push_back(c);
        int s = M.size();
        while (s >= 3 && useless(s - 3, s - 2, s - 1))
        {
            M.erase(M.end() - 2);
            C.erase(C.end() - 2);
            s--;
        }
    }
    long long query(long long x)
    {
        if (ptr >= M.size())
            ptr = M.size() - 1;
        while (ptr < M.size() - 1 && f(ptr, x) < f(ptr + 1, x))
            ptr++; // change > to < for maximum
        return f(ptr, x);
    }
    long long query2(long long x)
    {
        long long lo = 0, hi = M.size() - 1;
        while (lo < hi)
        {
            long long mid = (lo + hi) >> 1;
            if (f(mid, x) < f(mid + 1, x))
                lo = mid + 1; // change > to < for maximum
            else
                hi = mid;
        }
        return f(lo, x);
    }
};

long long a[N], p[N], s[N];

// Operation:
cin >> n;
for (i = 1; i <= n; ++i)
{
    cin >> a[i];
    p[i] = a[i] + p[i - 1];
    s[i] = i * a[i] + s[i - 1];
}
CHT cht;
cht.add(0, 0);
long long ans = 0;
for (i = 1; i <= n; ++i)
{
    ans = max(ans, cht.query2(p[i]) + s[i]);
    cht.add(-i, i * p[i] - s[i]);
}
cout << ans;

// Dynamic Convex Hull Trick:

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define eb emplace_back
#define nl '\n'
#define deb(x) cerr << #x " = " << x << nl
#define in() ({ int a ; scanf("%d", &a); a; })

const int N = 3e5 + 9;
const int mod = 1e9 + 7;

// add lines with -m and -b and return -ans to
// make this code work for minimums.(not -x)
const ll inf = -(1LL << 62);
struct line
{
    ll m, b;
    mutable function<const line *()> succ;
    bool operator<(const line &rhs) const
    {
        if (rhs.b != inf)
            return m < rhs.m;
        const line *s = succ();
        if (!s)
            return 0;
        ll x = rhs.m;
        return b - s->b < (s->m - m) * x;
    }
};
struct CHT : public multiset<line>
{
    bool bad(iterator y)
    {
        auto z = next(y);
        if (y == begin())
        {
            if (z == end())
                return 0;
            return y->m == z->m && y->b <= z->b;
        }
        auto x = prev(y);
        if (z == end())
            return y->m == x->m && y->b <= x->b;
        return 1.0 * (x->b - y->b) * (z->m - y->m) >= 1.0 * (y->b - z->b) * (y->m - x->m);
    }
    void add(ll m, ll b)
    {
        auto y = insert({m, b});
        y->succ = [=, this]
        { return next(y) == end() ? 0 : &*next(y); };
        if (bad(y))
        {
            erase(y);
            return;
        }
        while (next(y) != end() && bad(next(y)))
            erase(next(y));
        while (y != begin() && bad(prev(y)))
            erase(prev(y));
    }
    ll query(ll x)
    {
        assert(!empty());
        auto l = *lower_bound((line){
            x, inf});
        return l.m * x + l.b;
    }
};
CHT *cht;
ll a[N], b[N];
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];
    cht = new CHT();
    cht->add(-b[0], 0);
    ll ans = 0;
    for (int i = 1; i < n; i++)
    {
        ans = -cht->query(a[i]);
        cht->add(-b[i], -ans);
    }
    cout << ans << nl;
    return 0;
}

// Convex Hull Trick Dynamic:
/* Dynamic ConvexHull Trick - Maximizes f(x)
 * For minimization: insert(-m, -c) and negate the result
 */

const long long IS_QUERY = -(1LL << 62);
struct line
{
    long long m, b;
    mutable function<const line *()> succ;
    bool operator<(const line &rhs) const
    {
        if (rhs.b != IS_QUERY)
            return m < rhs.m;
        const line *s = succ();
        if (!s)
            return 0;
        long long x = rhs.m;
        return b - s->b < (s->m - m) * x;
    }
};

struct HullDynamic : public multiset<line>
{
    bool bad(iterator y)
    {
        auto z = next(y);
        if (y == begin())
        {
            if (z == end())
                return 0;
            return y->m == z->m && y->b <= z->b;
        }
        auto x = prev(y);
        if (z == end())
            return y->m == x->m && y->b <= x->b;
        return (1.0 * (x->b - y->b) * (z->m - y->m) >= 1.0 * (y->b - z->b) * (y->m - x->m));
    }
    void insert_line(long long m, long long b)
    {
        auto y = insert({m, b});
        y->succ = [=]
        { return next(y) == end() ? 0 : &*next(y); };
        if (bad(y))
        {
            erase(y);
            return;
        }
        while (next(y) != end() && bad(next(y)))
            erase(next(y));
        while (y != begin() && bad(prev(y)))
            erase(prev(y));
    }
    long long eval(long long x)
    {
        auto l = *lower_bound((line){x, IS_QUERY});
        return l.m * x + l.b;
    }
};

// Problem: https://codeforces.com/contest/660/problem/F

long long a[N], p[N], s[N];

// Operation:
cin >> n;
for (i = 1; i <= n; ++i)
{
    cin >> a[i];
    p[i] = a[i] + p[i - 1];
    s[i] = i * a[i] + s[i - 1];
}
HullDynamic hull;
hull.insert_line(0, 0);
long long ans = 0;
for (i = 1; i <= n; ++i)
{
    ans = max(ans, hull.eval(p[i]) + s[i]);
    hull.insert_line(-i, i * p[i] - s[i]);
}
cout << ans;

// OR,

#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

// credit: chemthan
typedef set<pair<int, int> >::iterator iter;
struct PT {
    int x, y;
    PT() : x(0), y(0) {}
    PT(int x, int y) : x(x), y(y) {}
    PT(const PT& rhs) : x(rhs.x), y(rhs.y) {}
    PT(const iter& p) : x(p->first), y(p->second) {}
    PT operator - (const PT& rhs) const {
        return PT(x - rhs.x, y - rhs.y);
    }
};
long long cross(PT a, PT b) {
    return (long long) a.x * b.y - (long long) a.y * b.x;
}
inline int inside(set<pair<int, int>>& hull, const PT& p) { //border inclusive
    int x = p.x, y = p.y;
    iter p1 = hull.lower_bound(make_pair(x, y));
    if (p1 == hull.end()) return 0;
    if (p1->first == x) return p1 != hull.begin() && y <= p1->second;
    if (p1 == hull.begin()) return 0;
    iter p2(p1--);
    return cross(p - PT(p1), PT(p2) - p) >= 0;
}
inline void del(set<pair<int, int>>& hull, iter it, long long& scross) {
    if (hull.size() == 1) {
        hull.erase(it);
        return;
    }
    if (it == hull.begin()) {
        iter p1 = it++;
        scross -= cross(p1, it);
        hull.erase(p1);
        return;
    }
    iter p1 = --it, p2 = ++it;
    if (++it == hull.end()) {
        scross -= cross(p1, p2);
        hull.erase(p2);
        return;
    }
    scross -= cross(p1, p2) + cross(p2, it) - cross(p1, it);
    hull.erase(p2);
}
inline void add(set<pair<int, int>>& hull, iter it, long long& scross) {
    if (hull.size() == 1) return;
    if (it == hull.begin()) {
        iter p1 = it++;
        scross += cross(p1, it);
        return;
    }
    iter p1 = --it, p2 = ++it;
    if (++it == hull.end()) {
        scross += cross(p1, p2);
        return;
    }
    scross += cross(p1, p2) + cross(p2, it) - cross(p1, it);
}
inline void add(set<pair<int, int>>& hull, const PT& p, long long& scross) { //no collinear PTs
    if (inside(hull, p)) return;
    int x = p.x, y = p.y;
    iter pnt = hull.insert(make_pair(x, y)).first, p1, p2;
    add(hull, pnt, scross);
    for ( ; ; del(hull, p2, scross)) {
        p1 = pnt;
        if (++p1 == hull.end()) break;
        p2 = p1;
        if (++p1 == hull.end()) break;
        if (cross(PT(p2) - p, PT(p1) - p) < 0) break;
    }
    for ( ; ; del(hull, p2, scross)) {
        if ((p1 = pnt) == hull.begin()) break;
        if (--p1 == hull.begin()) break;
        p2 = p1--;
        if (cross(PT(p2) - p, PT(p1) - p) > 0) break;
    }
}

int main() {
    long long ucross = 0, dcross = 0;
    set<pair<int, int>> uhull, dhull;
    PT p[] = {PT(0, 0), PT(3, 0), PT(3, 3), PT(0, 3), PT(0, 1), PT(0, 2), PT(3, 1), PT(3, 2)};
    for (int i = 0; i < 5; i++) {
        add(uhull, PT(+p[i].x, +p[i].y), ucross);
        add(dhull, PT(-p[i].x, -p[i].y), dcross);
    }
    for (iter it = uhull.begin(); it != uhull.end(); it++) {
        cout << "(" << +it->first << "," << +it->second << ") ";
    }
    cout << "\n";
    for (iter it = dhull.begin(); it != dhull.end(); it++) {
        cout << "(" << -it->first << "," << -it->second << ") ";
    }
    cout << "\n";
    cout << fixed << setprecision(1) << "Area: " << fabs(ucross + dcross) / 2.0 << "\n";
    return 0;
}

// DP on Convex Hulls:

#include <bits/stdc++.h>
using namespace std;

const int N = 205;

int sign(int x) { return (x > 0) - (x < -0); }
struct PT
{
    int x, y;
    PT() { x = 0, y = 0; }
    PT(int x, int y) : x(x), y(y) {}
    PT(const PT &p) : x(p.x), y(p.y) {}
    PT operator+(const PT &a) const { return PT(x + a.x, y + a.y); }
    PT operator-(const PT &a) const { return PT(x - a.x, y - a.y); }
    PT operator*(const int a) const { return PT(x * a, y * a); }
    friend PT operator*(const int &a, const PT &b) { return PT(a * b.x, a * b.y); }
    PT operator/(const int a) const { return PT(x / a, y / a); }
    bool operator==(PT a) const { return sign(a.x - x) == 0 && sign(a.y - y) == 0; }
    bool operator!=(PT a) const { return !(*this == a); }
    bool operator<(PT a) const { return sign(a.x - x) == 0 ? y < a.y : x < a.x; }
    bool operator>(PT a) const { return sign(a.x - x) == 0 ? y > a.y : x > a.x; }
    int norm2() { return x * x + y * y; }
    double arg() { return atan2(y, x); }
};
inline int dot(PT a, PT b) { return a.x * b.x + a.y * b.y; }
inline int dist2(PT a, PT b) { return dot(a - b, a - b); }
inline int cross(PT a, PT b) { return a.x * b.y - a.y * b.x; }
inline int orientation(PT a, PT b, PT c) { return sign(cross(b - a, c - a)); }

int n;
PT p[N];
bool half(PT p)
{
    return p.y > 0 || (p.y == 0 && p.x < 0);
}
double dp[N][N];
vector<pair<int, int>> v;
bool yo(double x)
{
    for (int l = 1; l <= n; l++)
    {
        for (int r = 1; r <= n; r++)
        {
            dp[l][r] = -1e9;
        }
    }
    for (auto [mid, r] : v)
    {
        double cur = cross(p[mid], p[r]) * 0.5 - (p[r] - p[mid]).norm2() * x;
        for (int l = 1; l <= n; l++)
        {
            dp[l][r] = max(dp[l][r], (l == mid ? 0 : dp[l][mid]) + cur);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (dp[i][i] >= 0)
        {
            return true;
        }
    }
    return false;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> p[i].x >> p[i].y;
        }
        v.clear();
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i != j)
                    v.push_back({i, j});
            }
        }
        sort(v.begin(), v.end(), [&](pair<int, int> x, pair<int, int> y)
             {
      PT a = p[x.second] - p[x.first], b = p[y.second] - p[y.first];
      return make_tuple(half(a), 0, a.norm2()) < make_tuple(half(b), cross(a, b), b.norm2()); });
        double l = 0, r = 1e7, ans = 0;
        int it = 70;
        while (it--)
        {
            double mid = (l + r) / 2;
            if (yo(mid))
            {
                ans = mid;
                l = mid;
            }
            else
            {
                r = mid;
            }
        }
        cout << fixed << setprecision(10) << ans << '\n';
    }
    return 0;
}
// https://toph.co/p/profitable-home

// Persistent CHT:

struct PT
{
    int x, y;
    PT(int x = 0, int y = 0) : x(x), y(y) {}
    friend ll dot(PT &a, PT &b)
    {
        return 1ll * a.x * b.x + 1ll * a.y * b.y;
    }
    friend int orientation(PT &a, PT &b, PT &c)
    {
        ll s = 1ll * (b.x - a.x) * (c.y - a.y) - 1ll * (b.y - a.y) * (c.x - a.x);
        return (s > 0) - (s < 0);
    }
};
struct PersistentCHT
{ // minimizes dot product
    const static int N = 1e6 + 6;
    const static int lg = 22;
    int p[N][lg], sz;
    PT pnt[N];
    int insert(PT a, int rt)
    {
        for (int u, v, i = lg - 1; i >= 0; i--)
            if ((u = p[rt][i]) && (v = p[u][0]) && orientation(pnt[v], pnt[u], a) <= 0)
                rt = u;
        if (p[rt][0] && orientation(pnt[p[rt][0]], pnt[rt], a) <= 0)
            rt = p[rt][0];
        pnt[++sz] = a;
        p[sz][0] = rt;
        for (int i = 1; i < lg; i++)
            p[sz][i] = p[p[sz][i - 1]][i - 1];
        return sz;
    }
    ll query(PT a, int rt)
    {
        for (int u, v, i = lg - 1; i >= 0; i--)
            if ((u = p[rt][i]) && (v = p[u][0]) && dot(a, pnt[v]) > dot(a, pnt[u]))
                rt = u;
        if (p[rt][0] && dot(a, pnt[p[rt][0]]) > dot(a, pnt[rt]))
            rt = p[rt][0];
        return rt ? dot(a, pnt[rt]) : -1e18;
    }
} cht;