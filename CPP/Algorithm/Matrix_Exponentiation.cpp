// Complexity: O(log(n))

void mul(auto a[3][3], auto b[3][3]) {
    int mul[3][3];
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            mul[i][j] = 0;
            for (int k = 0; k < 3; ++k)
                mul[i][j] += a[i][k] * b[k][j];
        }
    }
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            a[i][j] = mul[i][j];
}
auto power(auto F[3][3], auto n) {
    int M[3][3] = {{1, 1, 0}, {1, 0, 0}, {0, 1, 0}};
    if (n == 1)
        return F[0][0] + F[0][1];
    power(F, n >> 1);
    mul(F, F);
    if (n & 1)
        mul(F, M);
    return F[0][0] + F[0][1];
}
auto find(auto n) {
    int F[3][3] = {{1, 1, 0}, {1, 0, 0}, {0, 1, 0}};
    if (n == 0)
        return 0;
    if (n == 1 || n == 2)
        return 1;
    return power(F, n - 2);
}

// OR,

int64_t aa[N][N], I[N][N];
void mul(auto A[][N], auto B[][N], auto dim) {
    int res[dim + 1][dim + 1];
    for (int i = 1; i <= dim; ++i) {
        for (int j = 1; j <= dim; ++j) {
            res[i][j] = 0;
            for (int k = 1; k <= dim; ++k)
                res[i][j] = res[i][j] + (A[i][k] * B[k][j]);
        }
    }
    for (int i = 1; i <= dim; ++i)
        for (int j = 1; j <= dim; ++j)
            A[i][j] = res[i][j];
}
void power(auto A[][N], auto dim, auto n) {
    for (int i = 1; i <= dim; ++i)
        for (int j = 1; j <= dim; ++j)
            I[i][j] = (i == j);
    // Complexity O(N) for calculating power
    //    for(int i=1;i<=n;++i) //I=I*A
    //        mul(I,A,dim);
    while (n) {
        if (n & 1)
            mul(I, A, dim), --n;
        else
            mul(A, A, dim), n >>= 1;
    }
    for (int i = 1; i <= dim; ++i)
        for (int j = 1; j <= dim; ++j)
            aa[i][j] = I[i][j];
}
void print(auto A[][N], auto dim) {
    for (int i = 1; i <= dim; ++i) {
        for (int j = 1; j <= dim; ++j)
            cout << A[i][j] << ' ';
        cout << '\n';
    }
}

// Operation:
    int64_t dim; cin >> dim >> n;
    for (i = 1; i <= dim; ++i)
        for (j = 1; j <= dim; ++j) cin >> aa[i][j];
    power(aa, dim, n); print(aa, dim);

// OR,

#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;

struct Mat {
    int n, m;
    vector<vector<int>> a;
    Mat() {}
    Mat(int _n, int _m) {
        n = _n;
        m = _m;
        a.assign(n, vector<int>(m, 0));
    }
    Mat(vector<vector<int>> v) {
        n = v.size();
        m = n ? v[0].size() : 0;
        a = v;
    }
    inline void make_unit() {
        assert(n == m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                a[i][j] = i == j;
        }
    }
    inline Mat operator+(const Mat &b) {
        assert(n == b.n && m == b.m);
        Mat ans = Mat(n, m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                ans.a[i][j] = (a[i][j] + b.a[i][j]) % mod;
            }
        }
        return ans;
    }
    inline Mat operator-(const Mat &b) {
        assert(n == b.n && m == b.m);
        Mat ans = Mat(n, m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                ans.a[i][j] = (a[i][j] - b.a[i][j] + mod) % mod;
            }
        }
        return ans;
    }
    inline Mat operator*(const Mat &b) {
        assert(m == b.n);
        Mat ans = Mat(n, b.m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < b.m; ++j) {
                for (int k = 0; k < m; ++k) {
                    ans.a[i][j] = (ans.a[i][j] + 1LL * a[i][k] * b.a[k][j] % mod) % mod;
                }
            }
        }
        return ans;
    }
    inline Mat power(int64_t k) {
        assert(n == m);
        Mat ans(n, n), t = a;
        ans.make_unit();
        while (k) {
            if (k & 1) ans *= t;
            t *= t; k >>= 1;
        }
        return ans;
    }
    inline Mat &operator+=(const Mat &b) { return *this = (*this) + b; }
    inline Mat &operator-=(const Mat &b) { return *this = (*this) - b; }
    inline Mat &operator*=(const Mat &b) { return *this = (*this) * b; }
    inline bool operator==(const Mat &b) { return a == b.a; }
    inline bool operator!=(const Mat &b) { return a != b.a; }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    int64_t k;
    cin >> n >> k;
    Mat a(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a.a[i][j];
        }
    }
    Mat ans = a.power(k);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << ans.a[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}
// https://judge.yosupo.jp/problem/pow_of_matrix

// Matrix Exponentiation with Polynomial Coefficients:

#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 16;
const int mod = 998244353;
const int root = 3;
int lim, rev[N], w[N], wn[N], inv_lim;
void reduce(int &x) { x = (x + mod) % mod; }
int power(int x, int y, int ans = 1) {
    for (; y; y >>= 1, x = (int64_t)x * x % mod)
        if (y & 1)
            ans = (int64_t)ans * x % mod;
    return ans;
}
void pre(int len) {
    lim = wn[0] = 1;
    int s = -1;
    while (lim < len)
        lim <<= 1, ++s;
    for (int i = 0; i < lim; ++i)
        rev[i] = rev[i >> 1] >> 1 | (i & 1) << s;
    const int g = power(root, (mod - 1) / lim);
    inv_lim = power(lim, mod - 2);
    for (int i = 1; i < lim; ++i)
        wn[i] = (int64_t)wn[i - 1] * g % mod;
}
void ntt(vector<int> &a, int typ) {
    for (int i = 0; i < lim; ++i)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    for (int i = 1; i < lim; i <<= 1) {
        for (int j = 0, t = lim / i / 2; j < i; ++j)
            w[j] = wn[j * t];
        for (int j = 0; j < lim; j += i << 1) {
            for (int k = 0; k < i; ++k) {
                const int x = a[k + j], y = (int64_t)a[k + j + i] * w[k] % mod;
                reduce(a[k + j] += y - mod), reduce(a[k + j + i] = x - y);
            }
        }
    }
    if (!typ) {
        reverse(a.begin() + 1, a.begin() + lim);
        for (int i = 0; i < lim; ++i)
            a[i] = (int64_t)a[i] * inv_lim % mod;
    }
}
vector<int> multiply(vector<int> f, vector<int> g) {
    int n = (int)f.size() + (int)g.size() - 1;
    pre(n);
    vector<int> a = f, b = g;
    a.resize(lim);
    b.resize(lim);
    ntt(a, 1), ntt(b, 1);
    for (int i = 0; i < lim; ++i)
        a[i] = (int64_t)a[i] * b[i] % mod;
    ntt(a, 0);
    return a;
}

using poly = vector<int>;

struct Mat {
    int n, m;
    vector<vector<poly>> a;
    Mat() {}
    Mat(int _n, int _m) {
        n = _n;
        m = _m;
        a.assign(n, vector<poly>(m, poly({0})));
    }
    Mat(vector<vector<poly>> v) {
        n = v.size();
        m = n ? v[0].size() : 0;
        a = v;
    }
    inline void make_unit() {
        assert(n == m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                a[i][j] = poly({i == j});
        }
    }
    inline Mat operator+(const Mat &b) {
        assert(n == b.n && m == b.m);
        Mat ans = Mat(n, m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int sz = max(a[i][j].size(), b.a[i][j].size());
                auto &p = ans.a[i][j];
                p.resize(sz);
                for (int k = 0; k < sz; ++k) {
                    if (k < a[i][j].size())
                        p[k] = a[i][j][k];
                    if (k < b.a[i][j].size())
                    {
                        p[k] += b.a[i][j][k];
                        if (p[k] >= mod)
                        {
                            p[k] -= mod;
                        }
                    }
                }
            }
        }
        return ans;
    }
    inline Mat operator-(const Mat &b) {
        assert(n == b.n && m == b.m);
        Mat ans = Mat(n, m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int sz = max(a[i][j].size(), b.a[i][j].size());
                auto &p = ans.a[i][j];
                p.resize(sz);
                for (int k = 0; k < sz; ++k) {
                    if (k < a[i][j].size())
                        p[k] = a[i][j][k];
                    if (k < b.a[i][j].size())
                    {
                        p[k] -= b.a[i][j][k];
                        if (p[k] < 0)
                        {
                            p[k] += mod;
                        }
                    }
                }
            }
        }
        return ans;
    }
    inline Mat operator*(const Mat &b) {
        assert(m == b.n);
        Mat ans = Mat(n, b.m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < b.m; ++j) {
                for (int k = 0; k < m; ++k) {
                    poly prod = multiply(a[i][k], b.a[k][j]);
                    auto &p = ans.a[i][j];
                    if (p.size() < prod.size())
                    {
                        p.resize(prod.size());
                    }
                    for (int x = 0; x < prod.size(); x++)
                    {
                        p[x] += prod[x];
                        if (p[x] >= mod)
                        {
                            p[x] -= mod;
                        }
                    }
                }
            }
        }
        return ans;
    }
    void reduce(int z) { // % x^z
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (a[i][j].size() > z) {
                    a[i][j].resize(z);
                }
            }
        }
    }
    inline Mat power(int64_t k, int z) { // M^k % x^z
        assert(n == m);
        Mat ans(n, n), t = a;
        ans.make_unit();
        while (k) {
            if (k & 1) {
                ans = ans * t;
                ans.reduce(z);
            }
            t = t * t;
            t.reduce(z);
            k >>= 1;
        }
        return ans;
    }
    inline Mat &operator+=(const Mat &b) { return *this = (*this) + b; }
    inline Mat &operator-=(const Mat &b) { return *this = (*this) - b; }
    inline Mat &operator*=(const Mat &b) { return *this = (*this) * b; }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    Mat M(2, 2);
    M.a[0][0] = poly({1, 1});
    M.a[0][1] = poly({0, 1});
    M.a[1][0] = poly({1});
    M.a[1][1] = poly({0});
    M = M.power(n - 1, k + 1);
    poly p0 = poly({1});
    poly p1 = poly({1, 1});
    poly a = multiply(M.a[0][0], p1);
    poly b = multiply(M.a[0][1], p0);
    poly ans(k + 1);
    a.resize(k + 1);
    b.resize(k + 1);
    for (int i = 0; i <= k; ++i) {
        ans[i] = a[i] + b[i];
        ans[i] %= mod;
    }
    for (int i = 1; i <= k; ++i) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
    return 0;
}
// https://codeforces.com/contest/755/problem/G