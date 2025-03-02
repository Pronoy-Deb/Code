// NTT:

#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 20;
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
        {
            for (int k = 0; k < i; ++k)
            {
                const int x = a[k + j], y = (int64_t)a[k + j + i] * w[k] % mod;
                reduce(a[k + j] += y - mod), reduce(a[k + j + i] = x - y);
            }
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
    a.resize(n + 1);
    return a;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++)
    {
        cin >> b[i];
    }
    auto ans = multiply(a, b);
    ans.resize(n + m - 1);
    for (auto x : ans)
        cout << x << ' ';
    cout << '\n';
    return 0;
}
// https://judge.yosupo.jp/problem/convolution_mod

// NTT 2D:

#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 13;
const int mod = 998244353;
const int root = 3;
using Mat = vector<vector<int>>;
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
        {
            for (int k = 0; k < i; ++k)
            {
                const int x = a[k + j], y = (int64_t)a[k + j + i] * w[k] % mod;
                reduce(a[k + j] += y - mod), reduce(a[k + j + i] = x - y);
            }
        }
    }
    if (!typ)
    {
        reverse(a.begin() + 1, a.begin() + lim);
        for (int i = 0; i < lim; ++i)
            a[i] = (int64_t)a[i] * inv_lim % mod;
    }
}
// a is of size n * n
// b is of size m * m
// max(n, m)^2 * log(max(n, m));
Mat multiply(Mat a, Mat b)
{
    int n = a.size(), m = b.size();
    int len = n + m - 1;
    precompute(len);
    a.resize(lim);
    for (int i = 0; i < lim; i++)
    {
        a[i].resize(lim, 0);
    }
    b.resize(lim);
    for (int i = 0; i < lim; i++)
    {
        b[i].resize(lim, 0);
    }
    // convert rows to point value form
    for (int i = 0; i < lim; i++)
    {
        ntt(a[i], 1);
        ntt(b[i], 1);
    }
    Mat ans(lim, vector<int>(lim, 0));
    for (int j = 0; j < lim; j++)
    {
        vector<int> col_a(lim), col_b(lim);
        for (int i = 0; i < lim; i++)
        {
            col_a[i] = a[i][j];
            col_b[i] = b[i][j];
        }
        // convert columns to point value form
        ntt(col_a, 1);
        ntt(col_b, 1);
        // so everything is in point value form,
        // so compute the product easily
        for (int i = 0; i < lim; i++)
        {
            col_a[i] = 1LL * col_a[i] * col_b[i] % mod;
        }
        // inverse fft on columns
        ntt(col_a, 0);
        for (int i = 0; i < lim; i++)
        {
            a[i][j] = col_a[i];
        }
    }
    // inverse fft on rows
    for (int i = 0; i < lim; i++)
    {
        ntt(a[i], 0);
    }
    a.resize(n + m - 1);
    for (int i = 0; i < n + m - 1; i++)
    {
        a[i].resize(n + m - 1);
    }
    return a;
}
Mat multiply_brute(Mat a, Mat b)
{
    int n = a.size(), m = b.size();
    Mat ans(n + m - 1, vector<int>(n + m - 1, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int r = 0; r < m; r++)
            {
                for (int c = 0; c < m; c++)
                {
                    ans[i + r][j + c] += 1LL * a[i][j] * b[r][c] % mod;
                    ans[i + r][j + c] %= mod;
                }
            }
        }
    }
    return ans;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n = 30, m = 119;
    vector<vector<int>> a(n, vector<int>(n, 0)), b(m, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[i][j] = 1LL * rand() * rand() % mod;
        }
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            b[i][j] = 1LL * rand() * rand() % mod;
        }
    }
    Mat brute = multiply_brute(a, b);
    for (int i = 0; i < n + m - 1; i++)
    {
        for (int j = 0; j < n + m - 1; j++)
        {
            cout << brute[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
    Mat fast = multiply(a, b);
    for (int i = 0; i < n + m - 1; i++)
    {
        for (int j = 0; j < n + m - 1; j++)
        {
            cout << fast[i][j] << ' ';
        }
        cout << '\n';
    }
    assert(brute == fast);
    return 0;
}

// NTT Online:

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
        {
            for (int k = 0; k < i; ++k)
            {
                const int x = a[k + j], y = (int64_t)a[k + j + i] * w[k] % mod;
                reduce(a[k + j] += y - mod), reduce(a[k + j + i] = x - y);
            }
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
    return a;
}
// 1s for n = 2e5
struct OnlineConvolution
{
    vector<int> a, b, c;
    int k;
    OnlineConvolution(int n) : a(n), b(n), c(n), k(0) {}
    // poly c = poly a * poly b
    // add a[i] = x and b[i] = y and it will return c[i]
    // online!
    int extend(int i, int x, int y)
    {
        assert(i == k);
        a[k] = x;
        b[k] = y;
        int s = k + 2;
        for (int w = 1; s % w == 0 && w < s; w <<= 1)
        {
            for (int ri = 0; ri < 2; ri++)
            {
                if (ri == 0 || w * 2 != s)
                {
                    vector<int> f(w), g(w);
                    for (int i = 0; i < w; i++)
                        f[i] = a[w - 1 + i], g[i] = b[k - w + 1 + i];
                    f = multiply(f, g);
                    for (int i = 0, j = k; i < f.size() && j < c.size(); i++, j++)
                    {
                        c[j] += f[i];
                        if (c[j] >= mod)
                            c[j] -= mod;
                    }
                }
                swap(a, b);
            }
        }
        return c[k++];
    }
};
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    OnlineConvolution C(n);
    vector<int> f(n + 1);
    f[0] = 1;
    int pref = 0;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        int y = C.extend(i - 1, f[i - 1], f[i - 1]) % mod;
        pref = (pref + y) % mod;
        f[i] = 1LL * x * pref % mod;
        cout << f[i] << ' ';
    }
    cout << '\n';
    return 0;
}
// https://atcoder.jp/contests/abc315/tasks/abc315_h

// NTT Online (D & C):

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9, mod = 1e9 + 7;

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
int ncr(int n, int r)
{
    if (n < r || n < 0 || r < 0)
        return 0;
    return 1LL * f[n] * finv[n - r] % mod * finv[r] % mod;
}
int catalan(int n)
{
    return 1LL * inv[n + 1] * ncr(2 * n, n) % mod;
}
int ans[N], a[N], dp[N];
// ans[n] = \sum_{i = 0}^{n-1}{ans[i] * a[n - i]}
void yo(int l, int r)
{
    if (l == r)
    {
        dp[l] = (l ? dp[l - 1] : 0) + ans[l];
        if (dp[l] >= mod)
            dp[l] -= mod;
        return;
    }
    int mid = l + r >> 1;
    yo(l, mid);
    vector<int> b;
    for (int i = l; i <= r; i++)
        b.push_back(a[i - l]);
    vector<int> f;
    for (int i = l; i <= mid; i++)
        f.push_back(dp[i]);
    auto res = multiply(b, f);
    res.resize(r - l + 2);
    for (int i = mid + 1; i <= r; i++)
    {
        ans[i] += res[i - l];
        if (ans[i] >= mod)
            ans[i] -= mod;
    }
    yo(mid + 1, r);
}
int32_t main()
{
    pre();
    int n, k;
    cin >> n >> k;
    k = min(k, n / 2);
    for (int i = 1; i <= 2 * k; i++)
        a[i] = (i & 1) ? 0 : catalan(i / 2 - 1);
    ans[0] = 1; // initial value
    yo(0, n);
    cout << dp[n] << '\n';
    return 0;
}
// https://csacademy.com/contest/round-9/task/jetpack/statement/

// NTT with any Prime MOD:

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
        int64_t aa = A[i].x + 0.5;
        int64_t bb = B[i].x + 0.5;
        int64_t cc = A[i].y + 0.5;
        res[i] = (aa + ((bb % mod) << 15) + ((cc % mod) << 30)) % mod;
    }
    return res;
}

vector<int> pow(vector<int> &a, int p)
{
    vector<int> res;
    res.emplace_back(1);
    while (p)
    {
        if (p & 1)
            res = multiply(res, a);
        a = multiply(a, a, 1);
        p >>= 1;
    }
    return res;
}
int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(10, 0);
    while (k--)
    {
        int m;
        cin >> m;
        a[m] = 1;
    }
    vector<int> ans = pow(a, n / 2);
    int res = 0;
    for (auto x : ans)
        res = (res + 1LL * x * x % mod) % mod;
    cout << res << '\n';
    return 0;
}
// https://codeforces.com/contest/1096/problem/G