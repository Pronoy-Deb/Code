// Complexity: O(|s|)
// -> base = 29: Immediate prime number after 26
// const long long M = 3037000493;

// Palindrome checking using Hashing:

long long fh[N], bh[N], pw[N], n;
string s;
long long mmi(auto base)
{
    long long ans = 1, pow = M - 2;
    while (pow)
    {
        if (pow & 1)
            ans = (ans * base) % M;
        base = (base * base) % M;
        pow >>= 1;
    }
    return ans;
}
void pre(int p = 31)
{
    pw[0] = 1;
    for (int i = 0; i < n; ++i)
    {
        pw[i + 1] = (pw[i] * p) % M;
        fh[i + 1] = (fh[i] + (s[i] * pw[i]) % M) % M;
    }
    bh[1] = s[n - 1];
    for (int i = n - 2, j = 2; i >= 0 && j <= n; --i, ++j)
        bh[j] = (bh[j - 1] + (s[i] * pw[j - 1]) % M) % M;
}

bool pal(auto l, auto r)
{
    long long L = ((fh[r + 1] - fh[l] + M) % M * mmi(pw[l])) % M;
    long long R = ((bh[n - l] - bh[n - r - 1] + M) % M * mmi(pw[n - r - 1])) % M;
    return (L == R);
}

// Operation:
cin >> n >> s >> q;
pre();
while (q--)
{
    int l, r;
    cin >> l >> r;
    cout << boolalpha << pal(l, r) << '\n';
}

// Cumulative Forward Hashing:
// const long long M = 1e15 + 37;

long long hs[N], pw[N], n;
string s;
void pre(int p = 31)
{
    pw[0] = 1;
    for (int i = 0; i < n; ++i)
    {
        pw[i + 1] = (pw[i] * p) % M;
        fh[i + 1] = (fh[i] + (s[i] * pw[i]) % M) % M;
    }
}

// OR,

long long fhs(auto &s, int base = 31)
{
    long long sz = s.size(), tmp = s[0] - 96;
    for (int i = 1; i < sz; ++i)
        tmp = ((tmp * base) + (s[i] - 96)) % M;
    return tmp;
}

// Cumulative Backward Hashing:

long long bhs(auto &s, int base = 31)
{
    long long tmp = s.back() - 96;
    for (int i = s.size() - 2; i >= 0; --i)
        tmp = ((tmp * base) + (s[i] - 96)) % M;
    return tmp;
}

// Operation:
set<long long> st;
for (i = 0; i < n; ++i)
    st.insert((((hs[i] * pow(29, length_skipped)) % M) + (hs[n] - hs[i + length_skipped] + M)) % M);

// String Double Hashing:

long long hs[N], hs1[N], n;
string s;
void pre(int base = 31)
{
    long long p = 1;
    for (int i = 0; i < n; ++i)
    {
        if (base == 29)
            hs[i + 1] = (hs[i] + (s[i] - 95) * p) % M;
        else
            hs1[i + 1] = (hs1[i] + (s[i] - 95) * p) % M;
        p = (p * base) % M;
    }
}

// Operation:
cin >> n >> s;
fhs(29);
fhs();
set<pair<long long, long long>> st;
for (i = length_skipped; i <= n; ++i)
    st.emplace((hs[i - length_skipped] + ((((hs[n] - hs[i] + M))) * 853745547) % M) % M, (hs1[i - length_skipped] + ((((hs1[n] - hs1[i] + M))) * 746097820) % M) % M);

    // Problems:
    // https://codeforces.com/contest/1800/problem/D
    // https://codeforces.com/contest/271/problem/D
    // https://codeforces.com/problemset/problem/1943/B

    // String Hashing:

#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 9;

int power(long long n, long long k, const int mod)
{
    int ans = 1 % mod;
    n %= mod;
    if (n < 0)
        n += mod;
    while (k)
    {
        if (k & 1)
            ans = (long long)ans * n % mod;
        n = (long long)n * n % mod;
        k >>= 1;
    }
    return ans;
}

const int MOD1 = 127657753, MOD2 = 987654319;
const int p1 = 137, p2 = 277;
int ip1, ip2;
pair<int, int> pw[N], ipw[N];
void prec()
{
    pw[0] = {1, 1};
    for (int i = 1; i < N; i++)
    {
        pw[i].first = 1LL * pw[i - 1].first * p1 % MOD1;
        pw[i].second = 1LL * pw[i - 1].second * p2 % MOD2;
    }
    ip1 = power(p1, MOD1 - 2, MOD1);
    ip2 = power(p2, MOD2 - 2, MOD2);
    ipw[0] = {1, 1};
    for (int i = 1; i < N; i++)
    {
        ipw[i].first = 1LL * ipw[i - 1].first * ip1 % MOD1;
        ipw[i].second = 1LL * ipw[i - 1].second * ip2 % MOD2;
    }
}
struct Hashing
{
    int n;
    string s;                  // 0 - indexed
    vector<pair<int, int>> hs; // 1 - indexed
    Hashing() {}
    Hashing(string _s)
    {
        n = _s.size();
        s = _s;
        hs.emplace_back(0, 0);
        for (int i = 0; i < n; i++)
        {
            pair<int, int> p;
            p.first = (hs[i].first + 1LL * pw[i].first * s[i] % MOD1) % MOD1;
            p.second = (hs[i].second + 1LL * pw[i].second * s[i] % MOD2) % MOD2;
            hs.push_back(p);
        }
    }
    pair<int, int> get_hash(int l, int r)
    { // 1 - indexed
        assert(1 <= l && l <= r && r <= n);
        pair<int, int> ans;
        ans.first = (hs[r].first - hs[l - 1].first + MOD1) * 1LL * ipw[l - 1].first % MOD1;
        ans.second = (hs[r].second - hs[l - 1].second + MOD2) * 1LL * ipw[l - 1].second % MOD2;
        return ans;
    }
    pair<int, int> get_hash()
    {
        return get_hash(1, n);
    }
};
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    prec();
    int n;
    while (cin >> n)
    {
        string s, p;
        cin >> p >> s;
        Hashing h(s);
        auto hs = Hashing(p).get_hash();
        for (int i = 1; i + n - 1 <= s.size(); i++)
        {
            if (h.get_hash(i, i + n - 1) == hs)
                cout << i - 1 << '\n';
        }
        cout << '\n';
    }
    return 0;
}
// https://www.spoj.com/problems/NHAY/

// String Hashing 2D:

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

struct Hashing
{
    vector<vector<int>> hs;
    vector<int> PWX, PWY;
    int n, m;
    static const int PX = 3731, PY = 2999, mod = 998244353;
    Hashing() {}
    Hashing(vector<string> &s)
    {
        n = (int)s.size(), m = (int)s[0].size();
        hs.assign(n + 1, vector<int>(m + 1, 0));
        PWX.assign(n + 1, 1);
        PWY.assign(m + 1, 1);
        for (int i = 0; i < n; i++)
            PWX[i + 1] = 1LL * PWX[i] * PX % mod;
        for (int i = 0; i < m; i++)
            PWY[i + 1] = 1LL * PWY[i] * PY % mod;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                hs[i + 1][j + 1] = s[i][j] - 'a' + 1;
            }
        }
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                hs[i][j + 1] = (hs[i][j + 1] + 1LL * hs[i][j] * PY % mod) % mod;
            }
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j <= m; j++)
            {
                hs[i + 1][j] = (hs[i + 1][j] + 1LL * hs[i][j] * PX % mod) % mod;
            }
        }
    }
    int get_hash(int x1, int y1, int x2, int y2)
    { // 1-indexed
        assert(1 <= x1 && x1 <= x2 && x2 <= n);
        assert(1 <= y1 && y1 <= y2 && y2 <= m);
        x1--;
        y1--;
        int dx = x2 - x1, dy = y2 - y1;
        return (1LL * (hs[x2][y2] - 1LL * hs[x2][y1] * PWY[dy] % mod + mod) % mod -
                1LL * (hs[x1][y2] - 1LL * hs[x1][y1] * PWY[dy] % mod + mod) % mod * PWX[dx] % mod + mod) %
               mod;
    }
    int get_hash()
    {
        return get_hash(1, 1, n, m);
    }
};
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        vector<string> a(n);
        for (int i = 0; i < n; i++)
            cin >> a[i];
        Hashing H(a);
        int x, y;
        cin >> x >> y;
        vector<string> b(x);
        for (int i = 0; i < x; i++)
            cin >> b[i];
        auto z = Hashing(b).get_hash();
        int ans = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (i + x - 1 <= n && j + y - 1 <= m && H.get_hash(i, j, i + x - 1, j + y - 1) == z)
                    ans++;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
// https://vjudge.net/problem/UVA-11019

// String Hashing with Updates and Reverse:

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9;

int power(long long n, long long k, const int mod)
{
    int ans = 1 % mod;
    n %= mod;
    if (n < 0)
        n += mod;
    while (k)
    {
        if (k & 1)
            ans = (long long)ans * n % mod;
        n = (long long)n * n % mod;
        k >>= 1;
    }
    return ans;
}

using T = array<int, 2>;
const T MOD = {127657753, 987654319};
const T p = {137, 277};

T operator+(T a, int x) { return {(a[0] + x) % MOD[0], (a[1] + x) % MOD[1]}; }
T operator-(T a, int x) { return {(a[0] - x + MOD[0]) % MOD[0], (a[1] - x + MOD[1]) % MOD[1]}; }
T operator*(T a, int x) { return {(int)((long long)a[0] * x % MOD[0]), (int)((long long)a[1] * x % MOD[1])}; }
T operator+(T a, T x) { return {(a[0] + x[0]) % MOD[0], (a[1] + x[1]) % MOD[1]}; }
T operator-(T a, T x) { return {(a[0] - x[0] + MOD[0]) % MOD[0], (a[1] - x[1] + MOD[1]) % MOD[1]}; }
T operator*(T a, T x) { return {(int)((long long)a[0] * x[0] % MOD[0]), (int)((long long)a[1] * x[1] % MOD[1])}; }
ostream &operator<<(ostream &os, T hash) { return os << "(" << hash[0] << ", " << hash[1] << ")"; }

T pw[N], ipw[N];
void prec()
{
    pw[0] = {1, 1};
    for (int i = 1; i < N; i++)
    {
        pw[i] = pw[i - 1] * p;
    }
    ipw[0] = {1, 1};
    T ip = {power(p[0], MOD[0] - 2, MOD[0]), power(p[1], MOD[1] - 2, MOD[1])};
    for (int i = 1; i < N; i++)
    {
        ipw[i] = ipw[i - 1] * ip;
    }
}
struct Hashing
{
    int n;
    string s;              // 1 - indexed
    vector<array<T, 2>> t; // (normal, rev) hash
    array<T, 2> merge(array<T, 2> l, array<T, 2> r)
    {
        l[0] = l[0] + r[0];
        l[1] = l[1] + r[1];
        return l;
    }
    void build(int node, int b, int e)
    {
        if (b == e)
        {
            t[node][0] = pw[b] * s[b];
            t[node][1] = pw[n - b + 1] * s[b];
            return;
        }
        int mid = (b + e) >> 1, l = node << 1, r = l | 1;
        build(l, b, mid);
        build(r, mid + 1, e);
        t[node] = merge(t[l], t[r]);
    }
    void upd(int node, int b, int e, int i, char x)
    {
        if (b > i || e < i)
            return;
        if (b == e && b == i)
        {
            t[node][0] = pw[b] * x;
            t[node][1] = pw[n - b + 1] * x;
            return;
        }
        int mid = (b + e) >> 1, l = node << 1, r = l | 1;
        upd(l, b, mid, i, x);
        upd(r, mid + 1, e, i, x);
        t[node] = merge(t[l], t[r]);
    }
    array<T, 2> query(int node, int b, int e, int i, int j)
    {
        if (b > j || e < i)
            return {T({0, 0}), T({0, 0})};
        if (b >= i && e <= j)
            return t[node];
        int mid = (b + e) >> 1, l = node << 1, r = l | 1;
        return merge(query(l, b, mid, i, j), query(r, mid + 1, e, i, j));
    }
    Hashing() {}
    Hashing(string _s)
    {
        n = _s.size();
        s = "." + _s;
        t.resize(4 * n + 1);
        build(1, 1, n);
    }
    void upd(int i, char c)
    {
        upd(1, 1, n, i, c);
        s[i] = c;
    }
    T get_hash(int l, int r)
    { // 1 - indexed
        return query(1, 1, n, l, r)[0] * ipw[l - 1];
    }
    T rev_hash(int l, int r)
    { // 1 - indexed
        return query(1, 1, n, l, r)[1] * ipw[n - r];
    }
    T get_hash()
    {
        return get_hash(1, n);
    }
    bool is_palindrome(int l, int r)
    {
        return get_hash(l, r) == rev_hash(l, r);
    }
};
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    prec();
    string s;
    cin >> s;
    Hashing H(s);
    int n = s.size();
    int q;
    cin >> q;
    while (q--)
    {
        int ty;
        cin >> ty;
        if (ty == 1)
        {
            int k;
            char c;
            cin >> k >> c;
            H.upd(k, c);
        }
        else if (ty == 2)
        {
            int k;
            cin >> k;
            int l = 1, r = min(k - 1, n - k), ans = 0;
            while (l <= r)
            {
                int mid = (l + r) / 2;
                int x = k - mid, y = k + mid;
                if (H.is_palindrome(x, y))
                    ans = mid, l = mid + 1;
                else
                    r = mid - 1;
            }
            cout << ans * 2 + 1 << '\n';
        }
        else
        {
            int k;
            cin >> k;
            int l = 1, r = min(k, n - k), ans = -1;
            while (l <= r)
            {
                int mid = (l + r) / 2;
                int x = k - mid + 1, y = k + mid;
                if (H.is_palindrome(x, y))
                    ans = mid, l = mid + 1;
                else
                    r = mid - 1;
            }
            cout << (ans == -1 ? -1 : ans * 2) << '\n';
        }
    }
    return 0;
}
// https://codeforces.com/group/qcIqFPYhVr/contest/203881/problem/W