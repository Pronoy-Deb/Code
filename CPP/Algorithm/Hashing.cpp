// Complexity: O(|s|)
// -> base = 29: Immediate prime number after 26
// Palindrome checking using Hashing:

const int64_t M = 9223372036854775783ll;
__int128 fh[N], bh[N], pw[N], n; string s;
__int128 bex(__int128 base) {
    base %= M; __int128 ans = 1, pow = M - 2;
    while (pow) {
        if (pow & 1) ans = (ans * base) % M;
        base = (base * base) % M; pow >>= 1;
    }
    return ans;
}
void pre(int p = 31) {
    pw[0] = 1;
    for (int i = 0; i < n; ++i) {
        pw[i + 1] = (pw[i] * p) % M;
        fh[i + 1] = (fh[i] + (s[i] * pw[i]) % M) % M;
    }
    bh[1] = s[n - 1];
    for (int i = n - 2, j = 2; i >= 0 && j <= n; --i, ++j)
        bh[j] = (bh[j - 1] + (s[i] * pw[j - 1]) % M) % M;
}
bool pal(int l, int r) {
    int64_t L = ((fh[r + 1] - fh[l] + M) % M * bex(pw[l])) % M;
    int64_t R = ((bh[n - l] - bh[n - r - 1] + M) % M * bex(pw[n - r - 1])) % M;
    return (L == R);
}

// Cumulative Forward Hashing:

const int64_t M = 9223372036854775783ll;
__int128 bex(__int128 base, __int128 pow = M - 2) {
    base %= M; __int128 ans = 1;
    while (pow) {
        if (pow & 1) ans = (ans * base) % M;
        base = (base * base) % M; pow >>= 1;
    }
    return ans;
}
__int128 hs[N], pw[N], inv[N], n; string s;
void pre(int p = 31) {
    pw[0] = inv[0] = 1; __int128 pinv = bex(p);
    for (int i = 0; i < n; ++i) {
        pw[i + 1] = (pw[i] * p) % M;
        hs[i + 1] = (hs[i] + ((pw[i] * s[i]) % M)) % M;
        inv[i + 1] = (inv[i] * pinv) % M;
    }
}
inline int64_t get(int l, int r) { // 1-based range
    return ((hs[r] - hs[l - 1] + M) % M * inv[l - 1]) % M;
}

// OR,

__int128 cfh(auto &s, int base = 31) {
    __int128 sz = s.size(), tmp = 0, pow = 1;
    for (int i = 0; i < sz; ++i) {
        tmp = (tmp + (s[i] * pow) % M) % M;
        pow = (pow * base) % M;
    }
    return tmp;
}

// Cumulative Backward Hashing:

__int128 cfh(auto &s, int base = 31) {
    __int128 sz = s.size(), tmp = 0, pow = 1;
    for (int i = sz - 1; i >= 0; --i) {
        tmp = (tmp + (s[i] * pow) % M) % M;
        pow = (pow * base) % M;
    }
    return tmp;
}

// Operation:
set<int64_t> st;
for (i = 0; i < n; ++i)
    st.insert((((hs[i] * pow(29, length_skipped)) % M) + (hs[n] - hs[i + length_skipped] + M)) % M);

// String Double Hashing:

__int128 hs[N], hs1[N], n; string s;
void pre(int base = 31) {
    __int128 p = 1;
    for (int i = 0; i < n; ++i) {
        if (base == 29) hs[i + 1] = (hs[i] + s[i] * p) % M;
        else hs1[i + 1] = (hs1[i] + s[i] * p) % M;
        p = (p * base) % M;
    }
}

// Operation:
    cin >> n >> s;
    fhs(29); fhs();
    set<pair<int64_t, int64_t>> st;
    for (i = length_skipped; i <= n; ++i)
        st.emplace((hs[i - length_skipped] + ((((hs[n] - hs[i] + M))) * 853745547) % M) % M, (hs1[i - length_skipped] + ((((hs1[n] - hs1[i] + M))) * 746097820) % M) % M);

https://codeforces.com/contest/1800/problem/D
https://codeforces.com/contest/271/problem/D
https://codeforces.com/problemset/problem/1943/B

// String Hashing:

#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 9;

int bex(__int128 n, __int128 k, const int m) {
    n %= m; __int128 ans = 1 % m;
    if (n < 0) n += m;
    while (k) {
        if (k & 1) ans = ans * n % m;
        n = n * n % m; k >>= 1;
    }
    return ans;
}

const int M1 = 127657753, M2 = 987654319;
const int p1 = 137, p2 = 277;
int ip1, ip2;
pair<int, int> pw[N], ipw[N];
void prec()
{
    pw[0] = {1, 1};
    for (int i = 1; i < N; i++)
    {
        pw[i].first = 1LL * pw[i - 1].first * p1 % M1;
        pw[i].second = 1LL * pw[i - 1].second * p2 % M2;
    }
    ip1 = bex(p1, M1 - 2, M1);
    ip2 = bex(p2, M2 - 2, M2);
    ipw[0] = {1, 1};
    for (int i = 1; i < N; i++)
    {
        ipw[i].first = 1LL * ipw[i - 1].first * ip1 % M1;
        ipw[i].second = 1LL * ipw[i - 1].second * ip2 % M2;
    }
}
struct Hashing {
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
            p.first = (hs[i].first + 1LL * pw[i].first * s[i] % M1) % M1;
            p.second = (hs[i].second + 1LL * pw[i].second * s[i] % M2) % M2;
            hs.push_back(p);
        }
    }
    pair<int, int> get_hash(int l, int r)
    { // 1 - indexed
        assert(1 <= l && l <= r && r <= n);
        pair<int, int> ans;
        ans.first = (hs[r].first - hs[l - 1].first + M1) * 1LL * ipw[l - 1].first % M1;
        ans.second = (hs[r].second - hs[l - 1].second + M2) * 1LL * ipw[l - 1].second % M2;
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
                hs[i + 1][j + 1] = s[i][j] - 96;
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
// https://codeforces.com/group/qcIqFPYhVr/contest/203881/problem/W

int bex(__int128 n, __int128 k, const int m) {
    n %= m; __int128 ans = 1;
    if (n < 0) n += m;
    while (k) {
        if (k & 1) ans = ans * n % m;
        n = n * n % m; k >>= 1;
    }
    return ans;
}
using T = array<int, 2>;
const T MOD = {127657753, 987654319};
const T p = {137, 277};
T operator+(T a, int x) { return {(a[0] + x) % MOD[0], (a[1] + x) % MOD[1]}; }
T operator-(T a, int x) { return {(a[0] - x + MOD[0]) % MOD[0], (a[1] - x + MOD[1]) % MOD[1]}; }
T operator*(T a, int x) { return {(int)((__int128)a[0] * x % MOD[0]), (int)((__int128)a[1] * x % MOD[1])}; }
T operator+(T a, T x) { return {(a[0] + x[0]) % MOD[0], (a[1] + x[1]) % MOD[1]}; }
T operator-(T a, T x) { return {(a[0] - x[0] + MOD[0]) % MOD[0], (a[1] - x[1] + MOD[1]) % MOD[1]}; }
T operator*(T a, T x) { return {(int)((__int128)a[0] * x[0] % MOD[0]), (int)((__int128)a[1] * x[1] % MOD[1])}; }
ostream &operator<<(ostream &os, T hash) { return os << "(" << hash[0] << ", " << hash[1] << ")"; }

T pw[N], ipw[N];
void pre() {
    pw[0] = {1, 1};
    for (int i = 1; i < N; ++i) pw[i] = pw[i - 1] * p;
    ipw[0] = {1, 1};
    T ip = {bex(p[0], MOD[0] - 2, MOD[0]), bex(p[1], MOD[1] - 2, MOD[1])};
    for (int i = 1; i < N; ++i) ipw[i] = ipw[i - 1] * ip;
}
struct hs {
    int n; string s; // 1 - indexed
    vector<array<T, 2>> t; // (normal, rev) hash
    array<T, 2> com(array<T, 2> l, array<T, 2> r) {
        l[0] = l[0] + r[0]; l[1] = l[1] + r[1]; return l;
    }
    void make(int nd, int b, int e) {
        if (b == e) {
            t[nd][0] = pw[b] * s[b];
            t[nd][1] = pw[n - b + 1] * s[b]; return;
        }
        int mid = (b + e) >> 1, l = nd << 1, r = l | 1;
        make(l, b, mid); make(r, mid + 1, e);
        t[nd] = com(t[l], t[r]);
    }
    void up(int nd, int b, int e, int i, char x) {
        if (b > i || e < i) return;
        if (b == e && b == i) {
            t[nd][0] = pw[b] * x;
            t[nd][1] = pw[n - b + 1] * x; return;
        }
        int mid = (b + e) >> 1, l = nd << 1, r = l | 1;
        up(l, b, mid, i, x); up(r, mid + 1, e, i, x);
        t[nd] = com(t[l], t[r]);
    }
    array<T, 2> get(int nd, int b, int e, int i, int j) {
        if (b > j || e < i) return {T({0, 0}), T({0, 0})};
        if (b >= i && e <= j) return t[nd];
        int mid = (b + e) >> 1, l = nd << 1, r = l | 1;
        return com(get(l, b, mid, i, j), get(r, mid + 1, e, i, j));
    }
    hs() {}
    hs(string _s) {
        n = _s.size(); s = "." + _s;
        t.resize((n << 2) + 1); make(1, 1, n);
    }
    void up(int i, char c) {
        up(1, 1, n, i, c); s[i] = c;
    }
    T get_hash(int l, int r) { // 1 - indexed
        return get(1, 1, n, l, r)[0] * ipw[l - 1];
    }
    T rev_hash(int l, int r) { // 1 - indexed
        return get(1, 1, n, l, r)[1] * ipw[n - r];
    }
    T get_hash() {
        return get_hash(1, n);
    }
    bool pal(int l, int r) {
        return get_hash(l, r) == rev_hash(l, r);
    }
};

// Operation:
    pre(); string s; cin >> s;
    hs h(s);
    int n = s.size(), q; cin >> q;
    while (q--) {
        int ty; cin >> ty;
        if (ty == 1) {
            int k; char c;
            cin >> k >> c;
            h.up(k, c);
        }
        else if (ty == 2) {
            int k; cin >> k;
            int l = 1, r = min(k - 1, n - k), ans = 0;
            while (l <= r) {
                int mid = (l + r) >> 1, x = k - mid, y = k + mid;
                if (h.pal(x, y)) ans = mid, l = mid + 1;
                else r = mid - 1;
            }
            cout << (ans << 1) + 1 << '\n';
        }
        else {
            int k; cin >> k;
            int l = 1, r = min(k, n - k), ans = -1;
            while (l <= r) {
                int mid = (l + r) >> 1, x = k - mid + 1, y = k + mid;
                if (h.pal(x, y)) ans = mid, l = mid + 1;
                else r = mid - 1;
            }
            cout << (ans == -1 ? -1 : (ans << 1)) << '\n';
        }
    }
