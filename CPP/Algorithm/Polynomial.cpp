// Polynomial:

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
    pair<poly, poly> divmod_slow(const poly &b) const
    { // when divisor or quotient is small
        vector<mint> A(a);
        vector<mint> ans;
        while (A.size() >= b.a.size())
        {
            ans.push_back(A.back() / b.a.back());
            if (ans.back() != mint(0))
            {
                for (size_t i = 0; i < b.a.size(); i++)
                {
                    A[A.size() - i - 1] -= ans.back() * b.a[b.a.size() - i - 1];
                }
            }
            A.pop_back();
        }
        reverse(ans.begin(), ans.end());
        return {ans, A};
    }
    pair<poly, poly> divmod(const poly &b) const
    { // returns quotient and remainder of a mod b
        if (size() < b.size())
            return {poly{0}, *this};
        int d = size() - b.size();
        if (min(d, b.size()) < 250)
            return divmod_slow(b);
        poly D = (reverse_it(d + 1) * b.reverse_it(d + 1).inverse(d + 1)).mod_xk(d + 1).reverse_it(d + 1, 1);
        return {D, *this - (D * b)};
    }
    poly operator/(const poly &t) const { return divmod(t).first; }
    poly operator%(const poly &t) const { return divmod(t).second; }
    poly &operator/=(const poly &t) { return *this = divmod(t).first; }
    poly &operator%=(const poly &t) { return *this = divmod(t).second; }
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
    // better for small k, k < 100000
    poly pow(int k, int n) const
    { // p(x)^k mod x^n
        if (is_zero())
            return *this;
        poly ans({1}), b = mod_xk(n);
        while (k)
        {
            if (k & 1)
                ans = (ans * b).mod_xk(n);
            b = (b * b).mod_xk(n);
            k >>= 1;
        }
        return ans;
    }
    int leading_xk() const
    { // minimum i such that C[i] > 0
        if (is_zero())
            return 1000000000;
        int res = 0;
        while (a[res] == 0)
            res++;
        return res;
    }
    // better for k > 100000
    poly pow2(int k, int n) const
    { // p(x)^k mod x^n
        if (is_zero())
            return *this;
        int i = leading_xk();
        mint j = a[i];
        poly t = div_xk(i) / j;
        poly ans = (t.log(n) * mint(k)).exp(n);
        if (1LL * i * k > n)
            ans = {0};
        else
            ans = ans.mul_xk(i * k).mod_xk(n);
        ans *= (j.pow(k));
        return ans;
    }
    // if the poly is not zero but the result is zero, then no solution
    poly sqrt(int n) const
    {
        if ((*this)[0] == mint(0))
        {
            for (int i = 1; i < size(); i++)
            {
                if ((*this)[i] != mint(0))
                {
                    if (i & 1)
                        return {};
                    if (n - i / 2 <= 0)
                        break;
                    return div_xk(i).sqrt(n - i / 2).mul_xk(i / 2);
                }
            }
            return {};
        }
        mint s = (*this)[0].sqrt();
        if (s == 0)
            return {};
        poly y = *this / (*this)[0];
        poly ret({1});
        mint inv2 = mint(1) / 2;
        for (int i = 1; i < n; i <<= 1)
        {
            ret = (ret + y.mod_xk(i << 1) * ret.inverse(i << 1)) * inv2;
        }
        return ret.mod_xk(n) * s;
    }
    poly root(int n, int k = 2) const
    { // kth root of p(x) mod x^n
        if (is_zero())
            return *this;
        if (k == 1)
            return mod_xk(n);
        assert(a[0] == 1);
        poly q({1});
        for (int i = 1; i < n; i <<= 1)
        {
            if (k == 2)
                q += mod_xk(2 * i) * q.inverse(2 * i);
            else
                q = q * mint(k - 1) + mod_xk(2 * i) * q.inverse(2 * i).pow(k - 1, 2 * i);
            q = q.mod_xk(2 * i) / mint(k);
        }
        return q.mod_xk(n);
    }
    poly mulx(mint x)
    { // component-wise multiplication with x^k
        mint cur = 1;
        poly ans(*this);
        for (int i = 0; i < size(); i++)
            ans.a[i] *= cur, cur *= x;
        return ans;
    }
    poly mulx_sq(mint x)
    { // component-wise multiplication with x^{k^2}
        mint cur = x, total = 1, xx = x * x;
        poly ans(*this);
        for (int i = 0; i < size(); i++)
            ans.a[i] *= total, total *= cur, cur *= xx;
        return ans;
    }
    vector<mint> chirpz_even(mint z, int n)
    { // P(1), P(z^2), P(z^4), ..., P(z^2(n-1))
        int m = size() - 1;
        if (is_zero())
            return vector<mint>(n, 0);
        vector<mint> vv(m + n);
        mint iz = z.inv(), zz = iz * iz, cur = iz, total = 1;
        for (int i = 0; i <= max(n - 1, m); i++)
        {
            if (i <= m)
                vv[m - i] = total;
            if (i < n)
                vv[m + i] = total;
            total *= cur;
            cur *= zz;
        }
        poly w = (mulx_sq(z) * vv).substr(m, m + n).mulx_sq(z);
        vector<mint> ans(n);
        for (int i = 0; i < n; i++)
            ans[i] = w[i];
        return ans;
    }
    // O(nlogn)
    vector<mint> chirpz(mint z, int n)
    { // P(1), P(z), P(z^2), ..., P(z^(n-1))
        auto even = chirpz_even(z, (n + 1) / 2);
        auto odd = mulx(z).chirpz_even(z, n / 2);
        vector<mint> ans(n);
        for (int i = 0; i < n / 2; i++)
        {
            ans[2 * i] = even[i];
            ans[2 * i + 1] = odd[i];
        }
        if (n % 2 == 1)
            ans[n - 1] = even.back();
        return ans;
    }
    poly shift_it(int m, vector<poly> &pw)
    {
        if (size() <= 1)
            return *this;
        while (m >= size())
            m /= 2;
        poly q(a.begin() + m, a.end());
        return q.shift_it(m, pw) * pw[m] + mod_xk(m).shift_it(m, pw);
    };
    // n log(n)
    poly shift(mint a)
    { // p(x + a)
        int n = size();
        if (n == 1)
            return *this;
        vector<poly> pw(n);
        pw[0] = poly({1});
        pw[1] = poly({a, 1});
        int i = 2;
        for (; i < n; i *= 2)
            pw[i] = pw[i / 2] * pw[i / 2];
        return shift_it(i, pw);
    }
    mint eval(mint x)
    { // evaluates in single point x
        mint ans(0);
        for (int i = size() - 1; i >= 0; i--)
        {
            ans *= x;
            ans += a[i];
        }
        return ans;
    }
    // p(g(x))
    // O(n^2 logn)
    poly composition_brute(poly g, int deg)
    {
        int n = size();
        poly c(deg, 0), pw({1});
        for (int i = 0; i < min(deg, n); i++)
        {
            int d = min(deg, (int)pw.size());
            for (int j = 0; j < d; j++)
            {
                c.a[j] += coef(i) * pw[j];
            }
            pw *= g;
            if (pw.size() > deg)
                pw.a.resize(deg);
        }
        return c;
    }
    // p(g(x))
    // O(nlogn * sqrt(nlogn))
    poly composition(poly g, int deg)
    {
        int n = size();
        int k = 1;
        while (k * k <= n)
            k++;
        k--;
        int d = n / k;
        if (k * d < n)
            d++;
        vector<poly> pw(k + 3, poly({1}));
        for (int i = 1; i <= k + 2; i++)
        {
            pw[i] = pw[i - 1] * g;
            if (pw[i].size() > deg)
                pw[i].a.resize(deg);
        }
        vector<poly> fi(k, poly(deg, 0));
        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < d; j++)
            {
                int idx = i * d + j;
                if (idx >= n)
                    break;
                int sz = min(fi[i].size(), pw[j].size());
                for (int t = 0; t < sz; t++)
                {
                    fi[i].a[t] += pw[j][t] * coef(idx);
                }
            }
        }
        poly ret(deg, 0), gd({1});
        for (int i = 0; i < k; i++)
        {
            fi[i] = fi[i] * gd;
            int sz = min((int)ret.size(), (int)fi[i].size());
            for (int j = 0; j < sz; j++)
                ret.a[j] += fi[i][j];
            gd = gd * pw[d];
            if (gd.size() > deg)
                gd.a.resize(deg);
        }
        return ret;
    }
    poly build(vector<poly> &ans, int v, int l, int r, vector<mint> &vec)
    { // builds evaluation tree for (x-a1)(x-a2)...(x-an)
        if (l == r)
            return ans[v] = poly({-vec[l], 1});
        int mid = l + r >> 1;
        return ans[v] = build(ans, 2 * v, l, mid, vec) * build(ans, 2 * v + 1, mid + 1, r, vec);
    }
    vector<mint> eval(vector<poly> &tree, int v, int l, int r, vector<mint> &vec)
    { // auxiliary evaluation function
        if (l == r)
            return {eval(vec[l])};
        if (size() < 400)
        {
            vector<mint> ans(r - l + 1, 0);
            for (int i = l; i <= r; i++)
                ans[i - l] = eval(vec[i]);
            return ans;
        }
        int mid = l + r >> 1;
        auto A = (*this % tree[2 * v]).eval(tree, 2 * v, l, mid, vec);
        auto B = (*this % tree[2 * v + 1]).eval(tree, 2 * v + 1, mid + 1, r, vec);
        A.insert(A.end(), B.begin(), B.end());
        return A;
    }
    // O(nlog^2n)
    vector<mint> eval(vector<mint> x)
    { // evaluate polynomial in (x_0, ..., x_n-1)
        int n = x.size();
        if (is_zero())
            return vector<mint>(n, mint(0));
        vector<poly> tree(4 * n);
        build(tree, 1, 0, n - 1, x);
        return eval(tree, 1, 0, n - 1, x);
    }
    poly interpolate(vector<poly> &tree, int v, int l, int r, int ly, int ry, vector<mint> &y)
    { // auxiliary interpolation function
        if (l == r)
            return {y[ly] / a[0]};
        int mid = l + r >> 1;
        int midy = ly + ry >> 1;
        auto A = (*this % tree[2 * v]).interpolate(tree, 2 * v, l, mid, ly, midy, y);
        auto B = (*this % tree[2 * v + 1]).interpolate(tree, 2 * v + 1, mid + 1, r, midy + 1, ry, y);
        return A * tree[2 * v + 1] + B * tree[2 * v];
    }
};
// O(nlog^2n)
poly interpolate(vector<mint> x, vector<mint> y)
{ // interpolates minimum polynomial from (xi, yi) pairs
    int n = x.size();
    assert(n == (int)y.size()); // assert(all x are distinct)
    vector<poly> tree(4 * n);
    poly tmp({1});
    return tmp.build(tree, 1, 0, n - 1, x).differentiate().interpolate(tree, 1, 0, n - 1, 0, n - 1, y);
}
// O(a.size() * b.size())
// if gcd.size() - 1 = number of common roots between a and b
poly gcd(poly a, poly b)
{
    return b.is_zero() ? a : gcd(b, a % b);
}
// Let ra_0, ..., ra_n be the roots of A and rb_0, ..., rb_m be the roots of B
// resultant = A(rb_0) * ... A(rb_m). It is 0 iif there is a common root between A and B
// O(a.size() * b.size())
mint resultant(poly a, poly b)
{ // computes resultant of a and b, assert(!a.is_zero())
    if (b.is_zero() || a.is_zero())
        return 0;
    else if (b.size() == 1)
        return b.a.back().pow((int)a.size() - 1);
    else
    {
        int pw = (int)a.size() - 1;
        a %= b;
        pw -= (int)a.size() - 1;
        mint mul = b.a.back().pow(pw) * mint(((b.size() - 1) & (a.size() - 1) & 1) ? -1 : 1);
        mint ans = resultant(b, a);
        return ans * mul;
    }
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<mint> a, b;
    a.resize(m + 1);
    a[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        if (x <= m)
            a[x] = -4;
    }
    b = poly(a).root(m + 1).a;
    if (b.size() == 1)
    {
        for (int i = 1; i <= m; i++)
            cout << 0 << '\n';
        return 0;
    }
    b[0] += 1;
    a = poly(b).inverse(m + 1).a;
    a.resize(m + 1);
    for (int i = 1; i <= m; i++)
        cout << a[i] * 2 << '\n';
    return 0;
}
// https://codeforces.com/problemset/problem/438/E

// Polynomial Sum:

#include <bits/stdc++.h>
using namespace std;

const int N = 1e7 + 9, mod = 998244353;

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

// p = first at least n + 1 points: a, a+d, ..., a+n*d of the n degree polynomial, returns f(k)
mint Lagrange(const vector<mint> &p, mint x, mint a = 0, mint d = 1)
{
    int n = p.size() - 1;
    if (a == 0 and d == 1 and x.value <= n)
        return p[x.value];

    vector<mint> pref(n + 1, 1), suf(n + 1, 1);
    for (int i = 0; i < n; i++)
        pref[i + 1] = pref[i] * (x - (a + d * i));
    for (int i = n; i > 0; i--)
        suf[i - 1] = suf[i] * (x - (a + d * i));

    vector<mint> fact(n + 1, 1), finv(n + 1, 1);
    for (int i = 1; i <= n; i++)
        fact[i] = fact[i - 1] * d * i;
    finv[n] /= fact[n];
    for (int i = n; i >= 1; i--)
        finv[i - 1] = finv[i] * d * i;

    mint ans = 0;
    for (int i = 0; i <= n; i++)
    {
        mint tmp = p[i] * pref[i] * suf[i] * finv[i] * finv[n - i];
        if ((n - i) & 1)
            ans -= tmp;
        else
            ans += tmp;
    }

    return ans;
}
// Given a polynomial of degree k,
// f(x) = \sum_{i = 0}^{k}{c_i * x^i} and c_k != 0
// Let S(n) = \sum_{i = 0}^{n}{a^i * f(i)}
// Given S(0), S(1), ... S(k) find S(n)
// O(k log mod), can be optimized to O(k)
// Take care of the special case [a = 1] separately
mint yo(vector<mint> S, long long n, mint a, int k)
{
    assert(k + 1 == S.size());
    assert(a != 1);
    mint c = 0;
    for (int i = 0; i <= k; i++)
    {
        c += C.ncr(k + 1, i + 1) * (-a).pow(k - i) * S[i];
    }
    c /= (-a + 1).pow(k + 1);
    mint nw = 1;
    for (int i = 0; i <= k; i++)
    {
        S[i] = (S[i] - c) * nw;
        nw /= a;
    }
    return Lagrange(S, mint(n % mod)) * a.pow(n) + c;
}
int k;
mint f(int i)
{ // f(i)
    return mint(i).pow(k);
}
// Find \sum{i = 0}{n - 1}{a^i * i^k}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long a, n;
    cin >> a >> k >> n;
    n--;
    if (n < 0)
    {
        cout << 0 << '\n';
        return 0;
    }
    vector<mint> p;
    mint sum = 0;
    for (int i = 0; i <= k; i++)
    {
        sum += f(i) * mint(a).pow(i);
        p.push_back(sum);
    }
    if (a == 1)
    {
        sum += f(k + 1) * mint(a).pow(k + 1);
        p.push_back(sum);
        cout << Lagrange(p, mint(n % mod)) << '\n';
    }
    else
        cout << yo(p, n, a, k) << '\n';
    return 0;
}
// https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial
// https://min-25.hatenablog.com/entry/2015/04/24/031413

// Polynomial Factorization:

#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
using vi = vector<int>;

// credit- ksun
std::ostream &operator<<(std::ostream &o, const vi &v)
{
    o << "(";
    for (int i = int(v.size()) - 1; i >= 0; i--)
    {
        int c = v[i];
        if (c == 0)
            continue;
        if (i < int(v.size()) - 1)
        {
            o << (c > 0 ? '+' : '-');
        }
        else
        {
            assert(c == 1);
        }
        c = abs(c);
        if (i == 0)
        {
            o << c;
        }
        else
        {
            if (c != 1)
                o << c;
            o << "x";
            if (i > 1)
                o << "^" << i;
        }
    }
    o << ")";
    return o;
}

// multiply by x^e - 1
void mul(vi &a, int e)
{
    int n = int(a.size());
    a.insert(a.begin(), e, 0);
    for (int i = 0; i < n; i++)
    {
        a[i] -= a[i + e];
        if (a[i] < 0)
            a[i] += MOD;
    }
}

// divide by x^e - 1
void div(vi &a, int e)
{
    int n = int(a.size());
    for (int i = n - 1 - e; i >= 0; i--)
    {
        a[i] += a[i + e];
        if (a[i] >= MOD)
            a[i] -= MOD;
    }
    for (int i = 0; i < e; i++)
    {
        assert(a[i] == 0);
    }
    a.erase(a.begin(), a.begin() + e);
}

const int MAXN = 1.1e5;
bool isPrime[MAXN];
int mu[MAXN];
void precomp()
{
    for (int i = 1; i < MAXN; i++)
    {
        isPrime[i] = true;
        mu[i] = 1;
    }
    isPrime[1] = false;
    for (int p = 2; p < MAXN; p++)
    {
        if (!isPrime[p])
            continue;
        assert(mu[p] == 1);
        mu[p] *= -1;
        for (int j = p + p; j < MAXN; j += p)
        {
            isPrime[j] = false;
            if (j / p % p == 0)
                mu[j] = 0;
            else
                mu[j] *= -1;
        }
    }
}
vi cache[MAXN];
void get(int N)
{ // compute the cyclotomic polynomial phi_N(x)
    if (!cache[N].empty())
        return;
    cache[N] = vi({1});
    for (int d = 1; d <= N; d++)
    {
        if (N % d)
            continue;
        if (mu[N / d] == 1)
        {
            mul(cache[N], d);
        }
    }
    for (int d = 1; d <= N; d++)
    {
        if (N % d)
            continue;
        if (mu[N / d] == -1)
        {
            div(cache[N], d);
        }
    }
    for (int &i : cache[N])
    {
        if (MOD - i < i)
        {
            i -= MOD;
        }
    }
}

// compute the factorization of (x^N - 1)
int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    precomp();
    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;
        vector<int> inds;
        for (int d = 1; d <= N; d++)
        {
            if (N % d)
                continue;
            get(d);
            inds.push_back(d);
        }
        sort(inds.begin(), inds.end(), [&](int a, int b) -> bool
             {
        if (cache[a].size() != cache[b].size()) {
          return cache[a].size() < cache[b].size();
        }
        for (int i = int(cache[a].size()) - 1; i >= 0; i--) {
          if (cache[a][i] != cache[b][i]) {
            return cache[a][i] < cache[b][i];
          }
        }
        assert(a == b);
        return false; });
        for (int d : inds)
        {
            cout << cache[d];
        }
        cout << '\n';
    }

    return 0;
}
// https://codeforces.com/gym/102114/submission/50549745

// Polynomial with Binomial Coefficients:

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
int POW(long long n, long long k)
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
int f[N], inv[N], finv[N];
void pre()
{
    f[0] = 1;
    for (int i = 1; i < N; i++)
        f[i] = 1LL * i * f[i - 1] % mod;
    inv[1] = 1;
    for (int i = 2; i < N; i++)
    {
        inv[i] = (-(1LL * mod / i) * inv[mod % i]) % mod;
        inv[i] = (inv[i] + mod) % mod;
    }
    finv[0] = 1;
    for (int i = 1; i < N; i++)
        finv[i] = 1LL * inv[i] * finv[i - 1] % mod;
}
// p(x) = \sum{a[i] * C(x, i)}, where C(x, i) = x * (x - 1) * ... * (x - i + 1) / i!
// given p(0), p(1), ..., p(n) of an n degree poly
// returns {a[0], a[1], ..., a[n]}
vector<int> extract(vector<int> &p)
{
    int n = p.size();
    vector<int> a(n, 0), b(n, 0);
    for (int i = 0; i < n; i++)
    {
        a[i] = 1LL * p[i] * finv[i] % mod;
        b[i] = 1LL * (i & 1 ? mod - 1 : 1) * finv[i] % mod;
    }
    auto ans = multiply(a, b);
    ans.resize(n);
    for (int i = 0; i < n; i++)
        ans[i] = 1LL * ans[i] * f[i] % mod;
    return ans;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    pre();
    int n, k;
    cin >> n >> k;
    vector<int> p;
    int sum = 0;
    p.push_back(0);
    for (int i = 1; i <= k + 1; i++)
    {
        sum += POW(i, k);
        sum %= mod;
        p.push_back(sum);
    }
    auto a = extract(p);
    vector<int> nck(k + 2, 0);
    nck[0] = 1;
    for (int i = 1; i < a.size(); i++)
    {
        nck[i] = 1LL * nck[i - 1] * (n - i + 1) % mod * inv[i] % mod;
    }
    int ans = 0;
    for (int i = 0; i < a.size(); i++)
        ans = (ans + 1LL * a[i] * nck[i] % mod) % mod;
    cout << ans << '\n';
    return 0;
}
// https://codeforces.com/problemset/problem/622/F