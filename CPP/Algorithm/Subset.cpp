// Subset Generation:
// Bitmasking Approach:
// Complexity: O(2^n)  // n = inp.size()

vector<vector<long long>> res;
auto sset(auto &inp) {
    int sz = inp.size(), n = (1 << sz);
    for (int i = 0; i < n; ++i) {
        vector<long long> sub;
        int j = 0, hi = __builtin_popcount(i);
        while (hi) {
            if (i & (1 << j)) {
                sub.emplace_back(inp[j]); --hi;
            }
            ++j;
        }
        res.emplace_back(sub);
    }
}

// Recursive Approach:
// Complexity: O(2^n)  // n = inp.size()
// Note: if(!sub.empty()) condition in the 24th line to remove the NULL subset

vector<vector<long long>> res;
auto sset(auto &inp, auto &sub, auto i) {
    if (i == (int)inp.size()) {
        res.emplace_back(sub); return;
    }
    sset(inp, sub, i + 1);  // Not considering the i-th element
    sub.emplace_back(inp[i]);
    sset(inp, sub, i + 1);  // Considering the i-th element
    sub.pop_back();         // Backtracking
}

// Operation:
vector<long long> inp = {1, 2, 3}, sub;
sset(inp, sub, 0);

// Subset Union of Bitsets:

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 9;

int x[N], y[N], c[N], dp[1 << 20], msk[N], ans[N];

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, r;
    cin >> n >> m >> r;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }
    // total m bitsets and size of each is n
    for (int i = 1; i <= m; i++) {
        int X, Y;
        cin >> X >> Y >> c[i];
        for (int j = 1; j <= n; j++) {
            if (1LL * (X - x[j]) * (X - x[j]) + 1LL * (Y - y[j]) * (Y - y[j]) <= 1LL * r * r) {
                msk[j] |= 1 << (i - 1);
            }
        }
    }
    // msk[i] = mask of the i-th index
    for (int i = 1; i <= n; i++) {
        dp[msk[i] ^ ((1 << m) - 1)]++;
    }
    for (int i = 0; i < m; i++) {
        for (int mask = (1 << m) - 1; mask >= 0; mask--) {
            if (~mask >> i & 1) {
                dp[mask] += dp[mask ^ (1 << i)];
            }
        }
    }
    // dp[mask] = n - (popcount of the union of the bitsets which are on in mask)
    for (int i = 1; i <= n; i++) {
        ans[i] = 2e9 + 9;
    }
    for (int mask = 0; mask < (1 << m); mask++) {
        int cost = 0;
        for (int i = 0; i < m; i++) {
            if (mask >> i & 1) {
                cost += c[i + 1];
            }
        }
        ans[n - dp[mask]] = min(ans[n - dp[mask]], cost);
    }
    for (int i = n - 1; i >= 1; i--) {
        ans[i] = min(ans[i], ans[i + 1]);
    }
    for (int i = 1; i <= n; i++) {
        if (ans[i] == 2e9 + 9) ans[i] = -1;
        cout << ans[i] << '\n';
    }
    return 0;
}
// https://tlx.toki.id/contests/troc-16/problems/F

// Subset Sum:

// Complexity: O(n * 2^n)
// Application: Determine the possibility of having any subset sum equal to given value
// Subset Sum Generation:
https://cses.fi/problemset/task/1623

long long ar[N], n;
auto ssum() {
    int sz = (1 << n); vector<long long> res(sz);
    for (int i = 0; i < sz; ++i, int j = 0) {
        long long sum = 0, hi = __builtin_popcount(i);
        while (hi) {
            if (i & (1 << j++)) {
                sum += ar[j - 1]; --hi;
            }
        }
        res[i] = sum;
    }
    return res;
}

OR, https://leetcode.com/problems/partition-equal-subset-sum/

long long dp[N][N], ar[N];
auto ssum(auto i, auto sum) {
    if (!sum) return true;
    if (i < 0) return false;
    if (dp[i][sum] != -1) return dp[i][sum];
    bool psbl = ssum(i - 1, sum);
    if (sum - ar[i] >= 0) psbl |= ssum(i - 1, sum - ar[i]);
    return dp[i][sum] = psbl;
}
auto psbl() {
    memset(dp, -1, sizeof dp);
    long long sum = accumulate(ar, ar + N, 0ll);
    if (sum & 1) return false;
    return ssum(N - 1, sum >> 1);
}

// No of non-overlapping subsets with sum equal to given value: O(n*logn)

long long sub(auto &v, long long val) {
	long long cnt = 0, in = -1, csum = 0, n = v.size();
	map<long long, long long> mp; mp[0] = -1;
	for (int i = 0; i < n; ++i) {
		csum += v[i];
		if (mp.find(csum - val) != mp.end() && mp[csum - val] >= in) {
			++cnt; in = i;
		}
		mp[csum] = i;
	}
	return cnt;
}

// Subset Sum in SQRT:

// if sum of the array values = x, then complexity is O(x sqrt(x))
// returns the subset ids
vector<int> subset_sum(vector<int> a, int s) {
    vector<int> cnt(s + 1, 0), dp(s + 1, 0), last(s + 1, 0);
    map<int, vector<int>> id;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] <= s) {
            id[a[i]].push_back(i);
            cnt[a[i]]++;
        }
    }
    dp[0] = 1;
    for (int i = 1; i <= s; i++) {
        if (!cnt[i]) {
            continue;
        }
        for (int j = 0; j < i; j++) {
            int c = 0;
            for (int k = j; k <= s; k += i) {
                if (dp[k]) {
                    c = cnt[i];
                } else if (c) {
                    dp[k] = 1;
                    c--;
                    last[k] = id[i][c];
                }
            }
        }
    }
    if (dp[s]) {
        vector<int> ans;
        while (s) {
            ans.push_back(last[s]);
            s -= a[last[s]];
        }
        return ans;
    } else {
        return {-1};
    }
}
int ans[N], dep[N], sz[N];
vector<int> g[N], id[N];
void dfs(int u, int p = 0) {
    dep[u] = dep[p] + 1;
    id[dep[u]].push_back(u);
    sz[u] = 1;
    for (auto v : g[u]) {
        if (v ^ p) {
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
}
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    for (int i = 2; i <= n; i++) {
        int k;
        cin >> k;
        g[k].push_back(i);
    }
    dfs(1);
    vector<int> a;
    int mx = 0;
    for (int i = 1; i <= n; i++) {
        mx = max(mx, dep[i]);
    }
    for (int i = 1; i <= mx; i++) {
        a.push_back(id[i].size());
    }
    auto v = subset_sum(a, k);
    if (!v.empty() && v.front() == -1) {
        cout << mx + 1 << '\n';
        pair<int, int> x = {k, 1}, y = {n - k, 0};
        for (int i = 1; i <= mx; i++) {
            if (x < y) {
                swap(x, y);
            }
            sort(id[i].begin(), id[i].end(), [&](int u, int v) {
                return sz[u] < sz[v];
            });
            while (!id[i].empty() && x.first) {
                x.first--;
                ans[id[i].back()] = x.second;
                id[i].pop_back();
            }
            while (!id[i].empty() && y.first) {
                y.first--;
                ans[id[i].back()] = y.second;
                id[i].pop_back();
            }
        }
    } else {
        cout << mx << '\n';
        for (auto x : v) {
            for (auto i : id[x + 1]) {
                ans[i] = 1;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << (ans[i] ? 'a' : 'b');
    }
    return 0;
}
// https://codeforces.com/problemset/problem/1481/F

// Subset Sum Problem:

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9, mod = 998244353;

struct base
{
    double x, y;
    base() { x = y = 0; }
    base(double x, double y) : x(x), y(y) {}
};
inline base operator+(base a, base b) { return base(a.x + b.x, a.y + b.y); }
inline base operator-(base a, base b) { return base(a.x - b.x, a.y - b.y); }
inline base operator*(base a, base b) { return base(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
inline base conj(base a) { return base(a.x, -a.y); }
int lim = 1;
vector<base> roots = {{0, 0}, {1, 0}};
vector<int> rev = {0, 1};
const double PI = acosl(-1.0);
void ensure_base(int p)
{
    if (p <= lim)
        return;
    rev.resize(1 << p);
    for (int i = 0; i < (1 << p); i++)
        rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (p - 1));
    roots.resize(1 << p);
    while (lim < p)
    {
        double angle = 2 * PI / (1 << (lim + 1));
        for (int i = 1 << (lim - 1); i < (1 << lim); i++)
        {
            roots[i << 1] = roots[i];
            double angle_i = angle * (2 * i + 1 - (1 << lim));
            roots[(i << 1) + 1] = base(cos(angle_i), sin(angle_i));
        }
        lim++;
    }
}
void fft(vector<base> &a, int n = -1)
{
    if (n == -1)
        n = a.size();
    assert((n & (n - 1)) == 0);
    int zeros = __builtin_ctz(n);
    ensure_base(zeros);
    int shift = lim - zeros;
    for (int i = 0; i < n; i++)
        if (i < (rev[i] >> shift))
            swap(a[i], a[rev[i] >> shift]);
    for (int k = 1; k < n; k <<= 1)
    {
        for (int i = 0; i < n; i += 2 * k)
        {
            for (int j = 0; j < k; j++)
            {
                base z = a[i + j + k] * roots[j + k];
                a[i + j + k] = a[i + j] - z;
                a[i + j] = a[i + j] + z;
            }
        }
    }
}
// eq = 0: 4 FFTs in total
// eq = 1: 3 FFTs in total
vector<int> multiply(vector<int> &a, vector<int> &b, int eq = 0)
{
    int need = a.size() + b.size() - 1;
    int p = 0;
    while ((1 << p) < need)
        p++;
    ensure_base(p);
    int sz = 1 << p;
    vector<base> A, B;
    if (sz > (int)A.size())
        A.resize(sz);
    for (int i = 0; i < (int)a.size(); i++)
    {
        int x = (a[i] % mod + mod) % mod;
        A[i] = base(x & ((1 << 15) - 1), x >> 15);
    }
    fill(A.begin() + a.size(), A.begin() + sz, base{0, 0});
    fft(A, sz);
    if (sz > (int)B.size())
        B.resize(sz);
    if (eq)
        copy(A.begin(), A.begin() + sz, B.begin());
    else
    {
        for (int i = 0; i < (int)b.size(); i++)
        {
            int x = (b[i] % mod + mod) % mod;
            B[i] = base(x & ((1 << 15) - 1), x >> 15);
        }
        fill(B.begin() + b.size(), B.begin() + sz, base{0, 0});
        fft(B, sz);
    }
    double ratio = 0.25 / sz;
    base r2(0, -1), r3(ratio, 0), r4(0, -ratio), r5(0, 1);
    for (int i = 0; i <= (sz >> 1); i++)
    {
        int j = (sz - i) & (sz - 1);
        base a1 = (A[i] + conj(A[j])), a2 = (A[i] - conj(A[j])) * r2;
        base b1 = (B[i] + conj(B[j])) * r3, b2 = (B[i] - conj(B[j])) * r4;
        if (i != j)
        {
            base c1 = (A[j] + conj(A[i])), c2 = (A[j] - conj(A[i])) * r2;
            base d1 = (B[j] + conj(B[i])) * r3, d2 = (B[j] - conj(B[i])) * r4;
            A[i] = c1 * d1 + c2 * d2 * r5;
            B[i] = c1 * d2 + c2 * d1;
        }
        A[j] = a1 * b1 + a2 * b2 * r5;
        B[j] = a1 * b2 + a2 * b1;
    }
    fft(A, sz);
    fft(B, sz);
    vector<int> res(need);
    for (int i = 0; i < need; i++)
    {
        long long aa = A[i].x + 0.5;
        long long bb = B[i].x + 0.5;
        long long cc = A[i].y + 0.5;
        res[i] = (aa + ((bb % mod) << 15) + ((cc % mod) << 30)) % mod;
    }
    return res;
}
template <int32_t MOD>
struct modint
{
    int32_t value;
    modint() = default;
    modint(int32_t value_) : value(value_) {}
    inline modint<MOD> operator+(modint<MOD> other) const
    {
        int32_t c = this->value + other.value;
        return modint<MOD>(c >= MOD ? c - MOD : c);
    }
    inline modint<MOD> operator-(modint<MOD> other) const
    {
        int32_t c = this->value - other.value;
        return modint<MOD>(c < 0 ? c + MOD : c);
    }
    inline modint<MOD> operator*(modint<MOD> other) const
    {
        int32_t c = (int64_t)this->value * other.value % MOD;
        return modint<MOD>(c < 0 ? c + MOD : c);
    }
    inline modint<MOD> &operator+=(modint<MOD> other)
    {
        this->value += other.value;
        if (this->value >= MOD)
            this->value -= MOD;
        return *this;
    }
    inline modint<MOD> &operator-=(modint<MOD> other)
    {
        this->value -= other.value;
        if (this->value < 0)
            this->value += MOD;
        return *this;
    }
    inline modint<MOD> &operator*=(modint<MOD> other)
    {
        this->value = (int64_t)this->value * other.value % MOD;
        if (this->value < 0)
            this->value += MOD;
        return *this;
    }
    inline modint<MOD> operator-() const { return modint<MOD>(this->value ? MOD - this->value : 0); }
    modint<MOD> pow(uint64_t k) const
    {
        modint<MOD> x = *this, y = 1;
        for (; k; k >>= 1)
        {
            if (k & 1)
                y *= x;
            x *= x;
        }
        return y;
    }
    modint<MOD> inv() const { return pow(MOD - 2); } // MOD must be a prime
    inline modint<MOD> operator/(modint<MOD> other) const { return *this * other.inv(); }
    inline modint<MOD> operator/=(modint<MOD> other) { return *this *= other.inv(); }
    inline bool operator==(modint<MOD> other) const { return value == other.value; }
    inline bool operator!=(modint<MOD> other) const { return value != other.value; }
    inline bool operator<(modint<MOD> other) const { return value < other.value; }
    inline bool operator>(modint<MOD> other) const { return value > other.value; }
};
template <int32_t MOD>
modint<MOD> operator*(int64_t value, modint<MOD> n) { return modint<MOD>(value) * n; }
template <int32_t MOD>
modint<MOD> operator*(int32_t value, modint<MOD> n) { return modint<MOD>(value % MOD) * n; }
template <int32_t MOD>
ostream &operator<<(ostream &out, modint<MOD> n) { return out << n.value; }

using mint = modint<mod>;
struct poly
{
    vector<mint> a;
    inline void normalize()
    {
        while ((int)a.size() && a.back() == 0)
            a.pop_back();
    }
    template <class... Args>
    poly(Args... args) : a(args...) {}
    poly(const initializer_list<mint> &x) : a(x.begin(), x.end()) {}
    int size() const { return (int)a.size(); }
    inline mint coef(const int i) const { return (i < a.size() && i >= 0) ? a[i] : mint(0); }
    mint operator[](const int i) const { return (i < a.size() && i >= 0) ? a[i] : mint(0); } // Beware!! p[i] = k won't change the value of p.a[i]
    bool is_zero() const
    {
        for (int i = 0; i < size(); i++)
            if (a[i] != 0)
                return 0;
        return 1;
    }
    poly operator+(const poly &x) const
    {
        int n = max(size(), x.size());
        vector<mint> ans(n);
        for (int i = 0; i < n; i++)
            ans[i] = coef(i) + x.coef(i);
        while ((int)ans.size() && ans.back() == 0)
            ans.pop_back();
        return ans;
    }
    poly operator-(const poly &x) const
    {
        int n = max(size(), x.size());
        vector<mint> ans(n);
        for (int i = 0; i < n; i++)
            ans[i] = coef(i) - x.coef(i);
        while ((int)ans.size() && ans.back() == 0)
            ans.pop_back();
        return ans;
    }
    poly operator*(const poly &b) const
    {
        if (is_zero() || b.is_zero())
            return {};
        vector<int> A, B;
        for (auto x : a)
            A.push_back(x.value);
        for (auto x : b.a)
            B.push_back(x.value);
        auto res = multiply(A, B, (A == B));
        vector<mint> ans;
        for (auto x : res)
            ans.push_back(mint(x));
        while ((int)ans.size() && ans.back() == 0)
            ans.pop_back();
        return ans;
    }
    poly operator*(const mint &x) const
    {
        int n = size();
        vector<mint> ans(n);
        for (int i = 0; i < n; i++)
            ans[i] = a[i] * x;
        return ans;
    }
    poly operator/(const mint &x) const { return (*this) * x.inv(); }
    poly &operator+=(const poly &x) { return *this = (*this) + x; }
    poly &operator-=(const poly &x) { return *this = (*this) - x; }
    poly &operator*=(const poly &x) { return *this = (*this) * x; }
    poly &operator*=(const mint &x) { return *this = (*this) * x; }
    poly &operator/=(const mint &x) { return *this = (*this) / x; }
    poly mod_xk(int k) const { return {a.begin(), a.begin() + min(k, size())}; } // modulo by x^k
    poly mul_xk(int k) const
    { // multiply by x^k
        poly ans(*this);
        ans.a.insert(ans.a.begin(), k, 0);
        return ans;
    }
    poly div_xk(int k) const
    { // divide by x^k
        return vector<mint>(a.begin() + min(k, (int)a.size()), a.end());
    }
    poly substr(int l, int r) const
    { // return mod_xk(r).div_xk(l)
        l = min(l, size());
        r = min(r, size());
        return vector<mint>(a.begin() + l, a.begin() + r);
    }
    poly differentiate() const
    {
        int n = size();
        vector<mint> ans(n);
        for (int i = 1; i < size(); i++)
            ans[i - 1] = coef(i) * i;
        return ans;
    }
    poly integrate() const
    {
        int n = size();
        vector<mint> ans(n + 1);
        for (int i = 0; i < size(); i++)
            ans[i + 1] = coef(i) / (i + 1);
        return ans;
    }
    poly inverse(int n) const
    { // 1 / p(x) % x^n, O(nlogn)
        assert(!is_zero());
        assert(a[0] != 0);
        poly ans{mint(1) / a[0]};
        for (int i = 1; i < n; i *= 2)
        {
            ans = (ans * mint(2) - ans * ans * mod_xk(2 * i)).mod_xk(2 * i);
        }
        return ans.mod_xk(n);
    }
    poly log(int n) const
    { // ln p(x) mod x^n
        assert(a[0] == 1);
        return (differentiate().mod_xk(n) * inverse(n)).integrate().mod_xk(n);
    }
    poly exp(int n) const
    { // e ^ p(x) mod x^n
        if (is_zero())
            return {1};
        assert(a[0] == 0);
        poly ans({1});
        int i = 1;
        while (i < n)
        {
            poly C = ans.log(2 * i).div_xk(i) - substr(i, 2 * i);
            ans -= (ans * C).mod_xk(i).mul_xk(i);
            i *= 2;
        }
        return ans.mod_xk(n);
    }
};
// number of subsets of an array of n elements having sum equal to k for each k from 1 to m
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> a(m + 1, 0);
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k; // k >= 1, handle [k = 0] separately
        if (k <= m)
            a[k]++;
    }
    poly p(m + 1, 0);
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; i * j <= m; j++)
        {
            if (j & 1)
                p.a[i * j] += mint(a[i]) / j;
            else
                p.a[i * j] -= mint(a[i]) / j;
        }
    }
    p = p.exp(m + 1);
    for (int i = 1; i <= m; i++)
        cout << p[i] << ' ';
    cout << '\n'; // check for m = 0
    return 0;
}
// https://judge.yosupo.jp/problem/sharp_p_subset_sum