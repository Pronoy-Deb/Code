// Cyclic Convolution:

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 9;

const double PI = acos(-1);
struct base
{
    double a, b;
    base(double a = 0, double b = 0) : a(a), b(b) {}
    const base operator+(const base &c) const
    {
        return base(a + c.a, b + c.b);
    }
    const base operator-(const base &c) const
    {
        return base(a - c.a, b - c.b);
    }
    const base operator*(const base &c) const
    {
        return base(a * c.a - b * c.b, a * c.b + b * c.a);
    }
};
void fft(vector<base> &p, bool inv = 0)
{
    int n = p.size(), i = 0;
    for (int j = 1; j < n - 1; ++j)
    {
        for (int k = n >> 1; k > (i ^= k); k >>= 1)
            ;
        if (j < i)
            swap(p[i], p[j]);
    }
    for (int l = 1, m; (m = l << 1) <= n; l <<= 1)
    {
        double ang = 2 * PI / m;
        base wn = base(cos(ang), (inv ? 1. : -1.) * sin(ang)), w;
        for (int i = 0, j, k; i < n; i += m)
        {
            for (w = base(1, 0), j = i, k = i + l; j < k; ++j, w = w * wn)
            {
                base t = w * p[j + l];
                p[j + l] = p[j] - t;
                p[j] = p[j] + t;
            }
        }
    }
    if (inv)
        for (int i = 0; i < n; ++i)
            p[i].a /= n, p[i].b /= n;
}
vector<int64_t> multiply(vector<int> &a, vector<int> &b)
{
    int n = a.size(), m = b.size(), t = n + m - 1, sz = 1;
    while (sz < t)
        sz <<= 1;
    vector<base> x(sz), y(sz), z(sz);
    for (int i = 0; i < sz; ++i)
    {
        x[i] = i < (int)a.size() ? base(a[i], 0) : base(0, 0);
        y[i] = i < (int)b.size() ? base(b[i], 0) : base(0, 0);
    }
    fft(x), fft(y);
    for (int i = 0; i < sz; ++i)
        z[i] = x[i] * y[i];
    fft(z, 1);
    vector<int64_t> ret(sz);
    for (int i = 0; i < sz; ++i)
        ret[i] = (int64_t)round(z[i].a);
    while ((int)ret.size() > 1 && ret.back() == 0)
        ret.pop_back();
    return ret;
}
// ans[k] = sum(a[i] * b[j]) over 0 <= i < n and j - i = k
vector<int64_t> cyclic_convolution(vector<int> a, vector<int> b)
{
    assert(a.size() == b.size());
    int n = a.size();
    b.resize(3 * n);
    a.resize(3 * n);
    for (int i = 0; i < n; i++)
    {
        b[i + n] = b[i + 2 * n] = b[i];
        a[i + n] = a[i + 2 * n] = a[i];
    }
    auto c = multiply(a, b);
    vector<int64_t> ans(n, 0);
    for (int i = 0; i < n; i++)
    {
        int j = i + n - 1;
        ans[i] = c[i + j];
        if (i)
            ans[i] -= c[2 * i - 1];
    }
    return ans;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    vector<int> a({1, 2, 3});
    vector<int> b({1, 2, 1});
    auto c = cyclic_convolution(a, b);
    for (auto x : c)
    {
        cout << x << ' ';
    }
    return 0;
}

// Max Convolution between Convex Function:

#include <bits/stdc++.h>
using namespace std;

// a[i + 1] - a[i] >= a[i] - a[i - 1] -> convex
// b[i + 1] - b[i] >= b[i] - b[i - 1] -> convex
// compute ans(i + j) = max(a(i) + b(j))
vector<int> multiply(vector<int> a, vector<int> b)
{
    int n = a.size() - 1, m = b.size() - 1;
    vector<int> ans(n + m + 1);
    int sum = a[0] + b[0];
    ans[0] = sum;
    int l = 0, r = 0;
    while (l < n && r < m)
    {
        if (a[l + 1] - a[l] > b[r + 1] - b[r])
        {
            sum += a[l + 1] - a[l];
            l++;
        }
        else
        {
            sum += b[r + 1] - b[r];
            r++;
        }
        ans[l + r] = sum;
    }
    while (l < n)
        sum += a[l + 1] - a[l], l++, ans[l + r] = sum;
    while (r < m)
        sum += b[r + 1] - b[r], r++, ans[l + r] = sum;
    return ans;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    vector<int> a({1, 2, 4, 8, 20});
    vector<int> b({4, 6, 10, 18});
    auto ans = multiply(a, b);
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << ' ';
    }
    return 0;
}

// Min Plus Convolution (Convex and Convex):

#include <bits/stdc++.h>
using namespace std;

// a[i + 1] - a[i] >= a[i] - a[i - 1] -> convex
// b[i + 1] - b[i] >= b[i] - b[i - 1] -> convex
// compute ans(i + j) = min(a(i) + b(j))
vector<int> min_plus_convolution(vector<int> a, vector<int> b)
{
    int n = a.size() - 1, m = b.size() - 1;
    vector<int> ans(n + m + 1);
    int sum = a[0] + b[0];
    ans[0] = sum;
    int l = 0, r = 0;
    while (l < n && r < m)
    {
        if (a[l + 1] - a[l] < b[r + 1] - b[r])
        {
            sum += a[l + 1] - a[l];
            l++;
        }
        else
        {
            sum += b[r + 1] - b[r];
            r++;
        }
        ans[l + r] = sum;
    }
    while (l < n)
        sum += a[l + 1] - a[l], l++, ans[l + r] = sum;
    while (r < m)
        sum += b[r + 1] - b[r], r++, ans[l + r] = sum;
    return ans;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    vector<int> b(m);
    for (int i = 0; i < m; i++)
    {
        cin >> b[i];
    }
    auto ans = min_plus_convolution(a, b);
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << ' ';
    }
    return 0;
}
// https://judge.yosupo.jp/problem/min_plus_convolution_convex_convex

// Dirichlet Convolution:

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

const int N = 3e5 + 9, mod = 998244353;

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

/**
Prefix sum of multiplicative functions :
  p_f : the prefix sum of f(x) (1 <= x <= T).
  p_g : the prefix sum of g(x) (0 <= x <= N).
  p_c : the prefix sum of f * g(x) (0 <= x <= N).
  T : the threshold, generally should be n ^ (2 / 3). for n = 1e9, T = 1e6
Magic Functions for different f(x)
For f(x) = phi(x): Id(x) = phi * I(x) i.e. p_c = prefix sum of Id(x), p_g = prefix sum of I(x). Here Id(n) = n, I(n) = 1
For f(x) = mu(x): e(x) = mu * I(x). Here e(x) = x == 1 ? 1 : 0
Complexity: O(n^(2/3))
**/
namespace Dirichlet
{
    // solution for f(x) = phi(x)
    const int T = 1e7 + 9;
    int64_t phi[T];
    gp_hash_table<int64_t, mint> mp;
    mint dp[T], inv;
    int sz, spf[T], prime[T];
    void init()
    {
        memset(spf, 0, sizeof spf);
        phi[1] = 1;
        sz = 0;
        for (int i = 2; i < T; i++)
        {
            if (spf[i] == 0)
                phi[i] = i - 1, spf[i] = i, prime[sz++] = i;
            for (int j = 0; j < sz && i * prime[j] < T && prime[j] <= spf[i]; j++)
            {
                spf[i * prime[j]] = prime[j];
                if (i % prime[j] == 0)
                    phi[i * prime[j]] = phi[i] * prime[j];
                else
                    phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            }
        }
        dp[0] = 0;
        for (int i = 1; i < T; i++)
            dp[i] = dp[i - 1] + phi[i] % mod;
        inv = 1; // g(1)
    }
    mint p_c(int64_t n)
    {
        if (n % 2 == 0)
            return n / 2 % mod * ((n + 1) % mod) % mod;
        return (n + 1) / 2 % mod * (n % mod) % mod;
    }
    mint p_g(int64_t n)
    {
        return n % mod;
    }
    mint solve(int64_t x)
    {
        if (x < T)
            return dp[x];
        if (mp.find(x) != mp.end())
            return mp[x];
        mint ans = 0;
        for (int64_t i = 2, last; i <= x; i = last + 1)
        {
            last = x / (x / i);
            ans += solve(x / i) * (p_g(last) - p_g(i - 1));
        }
        ans = p_c(x) - ans;
        ans /= inv;
        return mp[x] = ans;
    }
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int64_t n;
    cin >> n;
    Dirichlet::init();
    cout << Dirichlet::solve(n) << '\n';
    return 0;
}
// https://judge.yosupo.jp/problem/sum_of_totient_function
// https://codeforces.com/blog/entry/54150