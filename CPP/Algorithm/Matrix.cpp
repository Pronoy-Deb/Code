// Inverse of a Matrix:

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9, mod = 1e9 + 7;
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
bool Gauss(vector<vector<int>> a, vector<vector<int>> &ans, const int mod)
{
    int n = (int)a.size();
    vector<int> col(n);
    vector<vector<int>> tmp(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        tmp[i][i] = 1, col[i] = i;
    for (int i = 0; i < n; i++)
    {
        int r = i, c = i;
        for (int j = i; j < n; j++)
        {
            for (int k = i; k < n; k++)
            {
                if (a[j][k])
                {
                    r = j;
                    c = k;
                    goto found;
                }
            }
        }
        return false; // not invertible
    found:
        a[i].swap(a[r]);
        tmp[i].swap(tmp[r]);
        for (int j = 0; j < n; j++)
        {
            swap(a[j][i], a[j][c]);
            swap(tmp[j][i], tmp[j][c]);
        }
        swap(col[i], col[c]);
        int v = power(a[i][i], mod - 2, mod);
        for (int j = i + 1; j < n; j++)
        {
            int f = 1LL * a[j][i] * v % mod;
            a[j][i] = 0;
            for (int k = i + 1; k < n; k++)
            {
                a[j][k] -= 1LL * f * a[i][k] % mod;
                if (a[j][k] < 0)
                    a[j][k] += mod;
            }
            for (int k = 0; k < n; k++)
            {
                tmp[j][k] -= 1LL * f * tmp[i][k] % mod;
                if (tmp[j][k] < 0)
                    tmp[j][k] += mod;
            }
        }
        for (int j = i + 1; j < n; j++)
            a[i][j] = 1LL * a[i][j] * v % mod;
        for (int j = 0; j < n; j++)
            tmp[i][j] = 1LL * tmp[i][j] * v % mod;
        a[i][i] = 1;
    }
    for (int i = n - 1; i > 0; --i)
    {
        for (int j = 0; j < i; j++)
        {
            int v = a[j][i];
            for (int k = 0; k < n; k++)
            {
                tmp[j][k] -= 1LL * v * tmp[i][k] % mod;
                if (tmp[j][k] < 0)
                    tmp[j][k] += mod;
            }
        }
    }
    ans.resize(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            ans[col[i]][col[j]] = tmp[i][j];
        }
    }
    return true; // invertible
}
int32_t main()
{
    int n, mod;
    while (cin >> n >> mod && n && mod)
    {
        vector<vector<int>> a(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cin >> a[i][j];
        }
        vector<vector<int>> ans;
        int ok = Gauss(a, ans, mod);
        if (!ok)
        {
            cout << "singular\n";
            continue;
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << ans[i][j] << ' ';
            cout << '\n';
        }
    }
    return 0;
}

// Inverse of a Matrix Modulo 2:

#include <bits/stdc++.h>
using namespace std;

const int N = 2005;

bitset<N> z;
// permanent after inverting mat[i][j] = mat[i][j] ^ inv[j][i]
vector<bitset<N>> inverse(int n, vector<bitset<N>> mat)
{
    vector<bitset<N>> inv(n, z);
    for (int i = 0; i < n; i++)
        inv[i][i] = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (mat[j][i])
            {
                swap(mat[i], mat[j]);
                swap(inv[i], inv[j]);
                break;
            }
        }
        for (int j = i + 1; j < n; j++)
        {
            if (mat[j][i])
            {
                mat[j] ^= mat[i];
                inv[j] ^= inv[i];
            }
        }
    }
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (mat[i][j])
                inv[i] ^= inv[j];
        }
    }
    return inv;
}
int a[500500], b[500500];
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    z.reset();
    int n, m;
    cin >> n >> m;
    vector<bitset<N>> mat(n, z);
    for (int i = 0; i < m; i++)
    {
        cin >> a[i] >> b[i];
        --a[i];
        --b[i];
        mat[a[i]][b[i]] = 1;
    }
    auto inv = inverse(n, mat);
    for (int i = 0; i < m; i++)
    {
        if (inv[b[i]][a[i]])
            cout << "NO\n";
        else
            cout << "YES\n";
    }
    return 0;
}
// https://codeforces.com/contest/736/problem/D

// Hafnian of a Matrix:

#include <bits/stdc++.h>
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

struct Hafnian
{
    int h;
    void add(vector<mint> &ans, const vector<mint> &a, const vector<mint> &b)
    {
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < h - 1 - i; j++)
                ans[i + j + 1] += a[i] * b[j];
        }
    }
    vector<mint> yo(const vector<vector<vector<mint>>> &v)
    {
        vector<mint> ans(h);
        if (!(int)v.size())
        {
            ans[0] = 1;
            return ans;
        }
        int m = (int)v.size() - 2;
        auto V = v;
        V.resize(m);
        vector<mint> zero = yo(V);
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < i; j++)
            {
                add(V[i][j], v[m][i], v[m + 1][j]);
                add(V[i][j], v[m + 1][i], v[m][j]);
            }
        }
        vector<mint> one = yo(V);
        for (int i = 0; i < h; i++)
            ans[i] += one[i] - zero[i];
        add(ans, one, v[m + 1][m]);
        return ans;
    }
    // Number of Perfect Matchings of a general graph
    // SQRT of the Permanent of a zero diagonal symmetric matrix
    // Takes ~2s for (38 * 38) matrix
    mint solve(vector<vector<mint>> a)
    {
        int n = a.size();
        assert(n % 2 == 0);
        h = n / 2 + 1;
        vector<vector<vector<mint>>> v(n);
        for (int i = 0; i < n; i++)
        {
            v[i].resize(i);
            for (int j = 0; j < i; j++)
            {
                v[i][j] = vector<mint>(h), v[i][j][0] = a[i][j];
            }
        }
        return yo(v).back();
    }
} H;
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<vector<mint>> a(n, vector<mint>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    }
    cout << H.solve(a) << '\n';
    return 0;
}
// https://judge.yosupo.jp/problem/hafnian_of_matrix
// https://dl.acm.org/doi/pdf/10.5555/2095116.2095189

// Permanent of a Matrix:

#include <bits/stdc++.h>
using namespace std;

const int N = 20;

long long dp[1 << N];
int n, a[N][N];
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cin >> a[i][j];
        }
        memset(dp, 0, sizeof dp);
        dp[(1 << n) - 1] = 1;
        for (int mask = (1 << n) - 2; mask >= 0; mask--)
        {
            int i = __builtin_popcount(mask);
            for (int j = 0; j < n; j++)
                if (!(mask >> j & 1))
                    dp[mask] += dp[mask | 1 << j] * a[i][j];
        }
        cout << dp[0] << '\n'; // permanent of the matrix
    }
    return 0;
}

// Vandermonde Matrix:

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9, mod = 1e9 + 7;
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

vector<mint> multiply(vector<mint> a, vector<mint> b)
{
    vector<mint> ans(a.size() + b.size() - 1, 0);
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < b.size(); j++)
        {
            ans[i + j] += a[i] * b[j];
        }
    }
    return ans;
}
/*
matrix form:
  1 x0  x0^2  ... x0^(n-1)
  1 x1  x1^2  ... x1^(n-1)
  1 x2  x2^2  ... x2^(n-1)
  . ..  ....  ... .......
  1 x(n-1)  x(n-1)^2  ... x(n-1)^(n-1)
if the 1st coloumn starts from x_i(2nd column), then inverse will be changed by: ans[i][j] /= x[i]
determinant of this matrix = mul_{1 <= i < j <= n}{x[j] - x[i]}
*/
#define vv vector<vector<mint>>
vv inverse(vector<mint> &x)
{
    int n = x.size();
    vv ans(n, vector<mint>(n, 0));
    vector<mint> all(n + 1, 0); //(x - x0) * (x - x1) * ... * (x - x(n-1))
    all[0] = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = n; j >= 0; j--)
        {
            all[j] *= -x[i];
            if (j)
                all[j] += all[j - 1];
        }
    }
    // lagrange
    for (int i = 0; i < n; i++)
    {
        vector<mint> up(n); // all / (x - xi)
        mint rem = all[n];
        for (int j = n - 1; j >= 0; --j)
        {
            up[j] = rem;
            rem = all[j] + rem * x[i];
        }
        mint down = 1;
        for (int j = 0; j < n; j++)
            if (i != j)
                down *= x[i] - x[j];
        up.resize(n);
        down = down.inv();
        for (int j = 0; j < n; j++)
            ans[i][j] = up[j] * down;
    }
    // transpose
    auto tmp = ans;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            ans[j][i] = tmp[i][j];
    }
    return ans;
}
int32_t main()
{
    int n;
    cin >> n;
    vector<mint> f(n);
    for (int i = 0; i < n; i++)
        cin >> f[i].value;
    vector<mint> x(n);
    for (int i = 1; i <= n; i++)
        x[i - 1] = i;
    auto v = inverse(x);
    // transpose
    auto t = v;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            t[j][i] = v[i][j];
    }
    vector<mint> a(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[i] += t[i][j] * f[j];
        }
    }
    for (int x = 0; x < n; x++)
    {
        mint ans = 0;
        for (int i = 0; i < n; i++)
            ans += a[i] * mint(x).pow(i + 1);
        cout << ans << ' ';
    }
    cout << '\n';
    return 0;
}
// https://www.codechef.com/problems/SATA05