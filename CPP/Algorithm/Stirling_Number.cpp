// Stirling Number of the First Kind for Fixed K:

#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 18;
const int mod = 998244353;
const int root = 3;
int lim, rev[N], w[N], wn[N], inv_lim;
void reduce(int &x) { x = (x + mod) % mod; }
int POW(int x, int y, int ans = 1)
{
    for (; y; y >>= 1, x = (int64_t)x * x % mod)
        if (y & 1)
            ans = (int64_t)ans * x % mod;
    return ans;
}
void precompute(int len)
{
    lim = wn[0] = 1;
    int s = -1;
    while (lim < len)
        lim <<= 1, ++s;
    for (int i = 0; i < lim; ++i)
        rev[i] = rev[i >> 1] >> 1 | (i & 1) << s;
    const int g = POW(root, (mod - 1) / lim);
    inv_lim = POW(lim, mod - 2);
    for (int i = 1; i < lim; ++i)
        wn[i] = (int64_t)wn[i - 1] * g % mod;
}
void ntt(vector<int> &a, int typ)
{
    for (int i = 0; i < lim; ++i)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    for (int i = 1; i < lim; i <<= 1)
    {
        for (int j = 0, t = lim / i / 2; j < i; ++j)
            w[j] = wn[j * t];
        for (int j = 0; j < lim; j += i << 1)
            for (int k = 0; k < i; ++k)
            {
                const int x = a[k + j], y = (int64_t)a[k + j + i] * w[k] % mod;
                reduce(a[k + j] += y - mod), reduce(a[k + j + i] = x - y);
            }
    }
    if (!typ)
    {
        reverse(a.begin() + 1, a.begin() + lim);
        for (int i = 0; i < lim; ++i)
            a[i] = (int64_t)a[i] * inv_lim % mod;
    }
}
vector<int> multiply(vector<int> &f, vector<int> &g)
{
    int n = (int)f.size() + (int)g.size() - 1;
    precompute(n);
    vector<int> a = f, b = g;
    a.resize(lim);
    b.resize(lim);
    ntt(a, 1), ntt(b, 1);
    for (int i = 0; i < lim; ++i)
        a[i] = (int64_t)a[i] * b[i] % mod;
    ntt(a, 0);
    // while((int)a.size() && a.back() == 0) a.pop_back();
    return a;
}
// a^k % x^n
vector<int> power(vector<int> a, int k, int n)
{
    assert(a.size() <= n);
    vector<int> ans({1});
    while (k)
    {
        if (k & 1)
        {
            ans = multiply(ans, a);
            ans.resize(n);
        }
        a = multiply(a, a);
        a.resize(n);
        k >>= 1;
    }
    return ans;
}
// returns stirling1st(i, k) for 0 <= i < n
// O(n log^2 n)
vector<int> stirling(int n, int k)
{
    assert(k <= n);
    vector<int> a(n); // sum c(i) / i! x^i, c(i) = (i - 1)!
    a[0] = 0;
    for (int i = 1; i < n; i++)
    {
        a[i] = POW(i, mod - 2);
    }
    auto ans = power(a, k, n);
    ans.resize(n);
    int f = 1;
    for (int i = 1; i <= k; i++)
    {
        f = 1LL * f * i % mod;
    }
    int cur = 1;
    // sum ans(i) / i! = 1 / k! * a^k
    for (int i = 0; i < n; i++)
    {
        ans[i] = 1LL * ans[i] * cur % mod;
        cur = 1LL * cur * (i + 1) % mod;
        ans[i] = 1LL * ans[i] * POW(f, mod - 2) % mod;
    }
    return ans;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int k = 3, n = 10;
    auto ans = stirling(n, k);
    for (int i = 0; i < n; i++)
    {
        cout << ans[i] << '\n';
    }
    return 0;
}
// https://codeforces.com/blog/entry/77468

// Stirling Number of the First Kind for Fixed n:

#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 18;
const int mod = 998244353;
const int root = 3;
int lim, rev[N], w[N], wn[N], inv_lim;
void reduce(int &x) { x = (x + mod) % mod; }
int POW(int x, int y, int ans = 1)
{
    for (; y; y >>= 1, x = (int64_t)x * x % mod)
        if (y & 1)
            ans = (int64_t)ans * x % mod;
    return ans;
}
void precompute(int len)
{
    lim = wn[0] = 1;
    int s = -1;
    while (lim < len)
        lim <<= 1, ++s;
    for (int i = 0; i < lim; ++i)
        rev[i] = rev[i >> 1] >> 1 | (i & 1) << s;
    const int g = POW(root, (mod - 1) / lim);
    inv_lim = POW(lim, mod - 2);
    for (int i = 1; i < lim; ++i)
        wn[i] = (int64_t)wn[i - 1] * g % mod;
}
void ntt(vector<int> &a, int typ)
{
    for (int i = 0; i < lim; ++i)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    for (int i = 1; i < lim; i <<= 1)
    {
        for (int j = 0, t = lim / i / 2; j < i; ++j)
            w[j] = wn[j * t];
        for (int j = 0; j < lim; j += i << 1)
            for (int k = 0; k < i; ++k)
            {
                const int x = a[k + j], y = (int64_t)a[k + j + i] * w[k] % mod;
                reduce(a[k + j] += y - mod), reduce(a[k + j + i] = x - y);
            }
    }
    if (!typ)
    {
        reverse(a.begin() + 1, a.begin() + lim);
        for (int i = 0; i < lim; ++i)
            a[i] = (int64_t)a[i] * inv_lim % mod;
    }
}
vector<int> multiply(vector<int> &f, vector<int> &g)
{
    int n = (int)f.size() + (int)g.size() - 1;
    precompute(n);
    vector<int> a = f, b = g;
    a.resize(lim);
    b.resize(lim);
    ntt(a, 1), ntt(b, 1);
    for (int i = 0; i < lim; ++i)
        a[i] = (int64_t)a[i] * b[i] % mod;
    ntt(a, 0);
    // while((int)a.size() && a.back() == 0) a.pop_back();
    return a;
}
int fact[N], ifact[N];
vector<int> shift(vector<int> &f, int c)
{ // f(x + c)
    int n = (int)f.size();
    precompute(n + n - 1);
    vector<int> a = f;
    a.resize(lim);
    for (int i = 0; i < n; ++i)
        a[i] = (int64_t)a[i] * fact[i] % mod;
    reverse(a.begin(), a.begin() + n);
    vector<int> b;
    b.resize(lim);
    b[0] = 1;
    for (int i = 1; i < n; ++i)
        b[i] = (int64_t)b[i - 1] * c % mod;
    for (int i = 0; i < n; ++i)
        b[i] = (int64_t)b[i] * ifact[i] % mod;
    ntt(a, 1), ntt(b, 1);
    for (int i = 0; i < lim; ++i)
        a[i] = (int64_t)a[i] * b[i] % mod;
    ntt(a, 0), reverse(a.begin(), a.begin() + n);
    vector<int> g;
    g.resize(n);
    for (int i = 0; i < n; ++i)
        g[i] = (int64_t)a[i] * ifact[i] % mod;
    return g;
}
// (x+1)*(x+2)*(x+3)...(x+n)
// O(n log n) only for ntt friendly primes
// otherwise use divide and conquer in O(n log^2 n)
vector<int> range_mul(int n)
{
    if (n == 0)
        return vector<int>({1});
    if (n & 1)
    {
        vector<int> f = range_mul(n - 1);
        f.push_back(0);
        for (int i = (int)f.size() - 1; i; --i)
            f[i] = (f[i - 1] + (int64_t)n * f[i]) % mod;
        f[0] = (int64_t)f[0] * n % mod;
        return f;
    }
    else
    {
        int n_ = n >> 1;
        vector<int> f = range_mul(n_);
        vector<int> tmp = shift(f, n_);
        f.resize(n_ + 1);
        tmp.resize(n_ + 1);
        return multiply(f, tmp);
    }
}
// returns stirling1st(n, i) for 0 <= i <= n
vector<int> stirling(int n)
{
    if (n == 0)
        return {1};
    vector<int> ans = range_mul(n - 1);
    ans.resize(n + 1);
    for (int i = n - 1; i >= 0; i--)
    {
        ans[i + 1] = ans[i];
    }
    ans[0] = 0;
    return ans;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    fact[0] = 1;
    for (int i = 1; i < N; ++i)
        fact[i] = (int64_t)fact[i - 1] * i % mod;
    ifact[N - 1] = POW(fact[N - 1], mod - 2);
    for (int i = N - 1; i; --i)
        ifact[i - 1] = (int64_t)ifact[i] * i % mod;
    int n;
    cin >> n;
    auto ans = stirling(n);
    for (int i = 0; i <= n; i++)
    {
        cout << ans[i] << ' ';
    }
    return 0;
}

// Stirling Number of the Second Kind for Fixed K:

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9, mod = 1e9 + 7;

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
        int64_t aa = A[i].x + 0.5;
        int64_t bb = B[i].x + 0.5;
        int64_t cc = A[i].y + 0.5;
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
    modint sqrt() const
    {
        if (value == 0)
            return 0;
        if (MOD == 2)
            return 1;
        if (pow((MOD - 1) >> 1) == MOD - 1)
            return 0; // does not exist, it should be -1, but kept as 0 for this program
        unsigned int Q = MOD - 1, M = 0, i;
        modint zQ;
        while (!(Q & 1))
            Q >>= 1, M++;
        for (int z = 1;; z++)
        {
            if (modint(z).pow((MOD - 1) >> 1) == MOD - 1)
            {
                zQ = modint(z).pow(Q);
                break;
            }
        }
        modint t = pow(Q), R = pow((Q + 1) >> 1), r;
        while (true)
        {
            if (t == 1)
            {
                r = R;
                break;
            }
            for (i = 1; modint(t).pow(1 << i) != 1; i++)
                ;
            modint b = modint(zQ).pow(1 << (M - 1 - i));
            M = i, zQ = b * b, t = t * zQ, R = R * b;
        }
        return min(r, -r + MOD);
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
    poly reverse_it(int n, bool rev = 0) const
    { // reverses and leaves only n terms
        poly ans(*this);
        if (rev)
        { // if rev = 1 then tail goes to head
            ans.a.resize(max(n, (int)ans.a.size()));
        }
        reverse(ans.a.begin(), ans.a.end());
        return ans.mod_xk(n);
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
};
struct Combi
{
    int n;
    vector<mint> facts, finvs, invs;
    Combi(int _n) : n(_n), facts(_n), finvs(_n), invs(_n)
    {
        facts[0] = finvs[0] = 1;
        invs[1] = 1;
        for (int i = 2; i < n; i++)
            invs[i] = invs[mod % i] * (-mod / i);
        for (int i = 1; i < n; i++)
        {
            facts[i] = facts[i - 1] * i;
            finvs[i] = finvs[i - 1] * invs[i];
        }
    }
    inline mint fact(int n) { return facts[n]; }
    inline mint finv(int n) { return finvs[n]; }
    inline mint inv(int n) { return invs[n]; }
    inline mint ncr(int n, int k) { return n < k ? 0 : facts[n] * finvs[k] * finvs[n - k]; }
};
Combi C(N);

// mul (1 - ix)
void yo(int l, int r, poly &ans)
{
    if (l == r)
    {
        ans = poly({1, mod - l});
        return;
    }
    int mid = (l + r) >> 1;
    poly a, b;
    yo(l, mid, a);
    yo(mid + 1, r, b);
    ans = a * b;
}
// stirling2nd(i, k) for 0 <= i <= n
// O(n log^2 n)
vector<mint> stirling(int n, int k)
{
    poly p;
    yo(1, k, p);
    p = p.inverse(n + 1);
    auto ans = p.a;
    ans.insert(ans.begin(), k, 0);
    ans.resize(n + 1);
    return ans;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    mint sum = 0;
    for (int i = 1; i <= n; i++)
    {
        int p;
        cin >> p;
        sum += p;
    }
    if (k == 1)
        return cout << sum * n << '\n', 0;
    auto p = stirling(n, k - 1);
    mint ans = 0;
    for (int i = 1; i <= n; i++)
        if (n - i >= 0)
            ans += C.ncr(n - 1, i - 1) * i * p[n - i];
    ans *= sum;
    cout << ans << '\n';
    return 0;
}
// https://codeforces.com/contest/961/problem/G

// Stirling Number of the Second Kind for Fixed n:

#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 18;
const int mod = 998244353;
const int root = 3;
int lim, rev[N], w[N], wn[N], inv_lim;
void reduce(int &x) { x = (x + mod) % mod; }
int POW(int x, int y, int ans = 1)
{
    for (; y; y >>= 1, x = (int64_t)x * x % mod)
        if (y & 1)
            ans = (int64_t)ans * x % mod;
    return ans;
}
void precompute(int len)
{
    lim = wn[0] = 1;
    int s = -1;
    while (lim < len)
        lim <<= 1, ++s;
    for (int i = 0; i < lim; ++i)
        rev[i] = rev[i >> 1] >> 1 | (i & 1) << s;
    const int g = POW(root, (mod - 1) / lim);
    inv_lim = POW(lim, mod - 2);
    for (int i = 1; i < lim; ++i)
        wn[i] = (int64_t)wn[i - 1] * g % mod;
}
void ntt(vector<int> &a, int typ)
{
    for (int i = 0; i < lim; ++i)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    for (int i = 1; i < lim; i <<= 1)
    {
        for (int j = 0, t = lim / i / 2; j < i; ++j)
            w[j] = wn[j * t];
        for (int j = 0; j < lim; j += i << 1)
            for (int k = 0; k < i; ++k)
            {
                const int x = a[k + j], y = (int64_t)a[k + j + i] * w[k] % mod;
                reduce(a[k + j] += y - mod), reduce(a[k + j + i] = x - y);
            }
    }
    if (!typ)
    {
        reverse(a.begin() + 1, a.begin() + lim);
        for (int i = 0; i < lim; ++i)
            a[i] = (int64_t)a[i] * inv_lim % mod;
    }
}
vector<int> multiply(vector<int> &f, vector<int> &g)
{
    int n = (int)f.size() + (int)g.size() - 1;
    precompute(n);
    vector<int> a = f, b = g;
    a.resize(lim);
    b.resize(lim);
    ntt(a, 1), ntt(b, 1);
    for (int i = 0; i < lim; ++i)
        a[i] = (int64_t)a[i] * b[i] % mod;
    ntt(a, 0);
    // while((int)a.size() && a.back() == 0) a.pop_back();
    return a;
}
template <const int32_t MOD>
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
istream &operator>>(istream &in, modint<MOD> &n) { return in >> n.value; }
template <int32_t MOD>
ostream &operator<<(ostream &out, modint<MOD> n) { return out << n.value; }

using mint = modint<mod>;

mint f[N];
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    f[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        f[i] = f[i - 1] * i;
    }
    vector<int> a(n + 1), b(n + 1);
    for (int i = 0; i <= n; i++)
    {
        a[i] = (f[i].inv() * (i & 1 ? mod - 1 : 1)).value;
    }
    for (int i = 0; i <= n; i++)
    {
        b[i] = (mint(i).pow(n) / f[i]).value;
    }
    auto ans = multiply(a, b);
    ans.resize(n + 1);
    for (int i = 0; i <= n; i++)
    {
        cout << ans[i] << ' ';
    }
    cout << '\n';
    return 0;
}
// https://codeforces.com/blog/entry/48603?#comment-326879
