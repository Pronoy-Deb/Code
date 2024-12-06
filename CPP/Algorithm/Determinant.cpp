// Determinant:

const double eps = 1e-9;
int gauss(vector<vector<double>> a) {
    int n = (int)a.size(), m = (int)a[0].size();
    double det = 1;
    int rank = 0;
    for (int col = 0, row = 0; col < m && row < n; ++col) {
        int mx = row;
        for (int i = row; i < n; ++i)
            if (fabs(a[i][col]) > fabs(a[mx][col])) mx = i;
        if (fabs(a[mx][col]) < eps) { det = 0; continue; }
        for (int i = col; i < m; ++i) swap(a[row][i], a[mx][i]);
        if (row != mx) det = -det; det *= a[row][col];
        for (int i = 0; i < n; ++i) {
            if (i != row && fabs(a[i][col]) > eps) {
                double c = a[i][col] / a[row][col];
                for (int j = col; j < m; ++j) a[i][j] -= a[row][j] * c;
            }
        }
        ++row; ++rank;
    }
    return det;
}

// Operation:
    cin >> n >> m;
    vector<vector<double>> v(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            double x; cin >> x;
            v[i].push_back(x);
        }
    }
    cout << gauss(v) << '\n';

// Determinant of Permutant Matrix:

#include <bits/stdc++.h>
using namespace std;

constexpr int P = 1000000007;
using Poly = vector<int>;
int power(int a, int b)
{
    int res = 1;
    for (; b; b >>= 1, a = 1ll * a * a % P)
        if (b & 1)
            res = 1ll * res * a % P;
    return res;
}
Poly operator%(Poly a, const Poly &b)
{
    assert(!b.empty());
    int m = b.size() - 1, n = a.size() - 1;
    int inv = power(b[m], P - 2);
    while (n >= m)
    {
        int x = 1ll * inv * (P - a[n]) % P;
        for (int j = 0; j < m; ++j)
            a[n - m + j] = (a[n - m + j] + 1ll * x * b[j]) % P;
        a.pop_back();
        while (!a.empty() && a.back() == 0)
            a.pop_back();
        n = a.size() - 1;
    }
    return a;
}
// Let n = deg(A), m = deg(B). Treat deg(0) = 0.
// a[n] != 0, b[m] != 0
// R(A, B) := b[m]^n prod_{j=0..m-1} A(b_roots[j]) // counted with multiplicities
// = (-1)^(mn) a[n]^m prod_{i=0..n-1} B(a_roots[i])
// O(n * m)
int resultant(const Poly &a, const Poly &b)
{
    if (b.empty())
        return 0;
    if (b.size() == 1)
        return power(b[0], a.size() - 1);
    auto c = a % b;
    return 1ll * power(b.back(), a.size() - c.size()) * (((a.size() & 1) | (b.size() & 1)) ? 1 : P - 1) % P * resultant(b, c) % P;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n), p(n); // for cyclic matrix set p accordingly
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < n; ++i)
    {
        cin >> p[i];
        --p[i];
    }
    for (int i = 0, x = 0; i < n - 1; ++i)
    {
        x = p[x];
        if (x == 0)
        { // if permutation has more than one cycle than ans is 0
            cout << 0 << "\n";
            return 0;
        }
    }
    vector<int> q(n);
    for (int i = n - 1, x = 0; i >= 0; --i)
    {
        q[i] = x;
        x = p[x];
    }
    vector<int> vis(n);
    int coef = (n & 1) ? P - 1 : 1;
    for (int i = 0; i < n; ++i)
    {
        if (vis[i])
            continue;
        for (int j = i; !vis[j]; j = q[j])
            vis[j] = 1;
        coef = P - coef;
    }
    vector<int> b(n);
    for (int i = 0; i < n; ++i)
        b[i] = a[q[i]];
    a.assign(n + 1, 0);
    a[0] = P - 1;
    a[n] = 1;
    int ans = resultant(a, b);
    ans = 1ll * ans * coef % P;
    cout << ans << "\n";
    return 0;
}
// https://codeforces.com/gym/102129/problem/G

// Determinant of Cyclic Matrix:

#include <bits/stdc++.h>
using namespace std;

constexpr int P = 1000000007;
using Poly = vector<int>;
int power(int a, int b)
{
    int res = 1;
    for (; b; b >>= 1, a = 1ll * a * a % P)
        if (b & 1)
            res = 1ll * res * a % P;
    return res;
}
Poly operator%(Poly a, const Poly &b)
{
    assert(!b.empty());
    int m = b.size() - 1, n = a.size() - 1;
    int inv = power(b[m], P - 2);
    while (n >= m)
    {
        int x = 1ll * inv * (P - a[n]) % P;
        for (int j = 0; j < m; ++j)
            a[n - m + j] = (a[n - m + j] + 1ll * x * b[j]) % P;
        a.pop_back();
        while (!a.empty() && a.back() == 0)
            a.pop_back();
        n = a.size() - 1;
    }
    return a;
}
// Let n = deg(A), m = deg(B). Treat deg(0) = 0.
// a[n] != 0, b[m] != 0
// R(A, B) := b[m]^n prod_{j=0..m-1} A(b_roots[j]) // counted with multiplicities
// = (-1)^(mn) a[n]^m prod_{i=0..n-1} B(a_roots[i])
// O(n * m)
int resultant(const Poly &a, const Poly &b)
{
    if (b.empty())
        return 0;
    if (b.size() == 1)
        return power(b[0], a.size() - 1);
    auto c = a % b;
    return 1ll * power(b.back(), a.size() - c.size()) * (((a.size() & 1) | (b.size() & 1)) ? 1 : P - 1) % P * resultant(b, c) % P;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n), p(n); // for cyclic matrix set p accordingly
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < n; ++i)
    {
        cin >> p[i];
        --p[i];
    }
    for (int i = 0, x = 0; i < n - 1; ++i)
    {
        x = p[x];
        if (x == 0)
        { // if permutation has more than one cycle than ans is 0
            cout << 0 << "\n";
            return 0;
        }
    }
    vector<int> q(n);
    for (int i = n - 1, x = 0; i >= 0; --i)
    {
        q[i] = x;
        x = p[x];
    }
    vector<int> vis(n);
    int coef = (n & 1) ? P - 1 : 1;
    for (int i = 0; i < n; ++i)
    {
        if (vis[i])
            continue;
        for (int j = i; !vis[j]; j = q[j])
            vis[j] = 1;
        coef = P - coef;
    }
    vector<int> b(n);
    for (int i = 0; i < n; ++i)
        b[i] = a[q[i]];
    a.assign(n + 1, 0);
    a[0] = P - 1;
    a[n] = 1;
    int ans = resultant(a, b);
    ans = 1ll * ans * coef % P;
    cout << ans << "\n";
    return 0;
}
// https://codeforces.com/gym/102129/problem/G

// Determinant of Product Matrix:

#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

// Given two arrays and x
// Matrix M(i, j) = a(i) * b(j) if i != j, (x + a(i) * b(j)) if i == j
// Find the determinant
// Solution = x^n + x^(n - 1) * sum_of(a(i) * b(i))

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, x;
    while (cin >> n >> x)
    {
        vector<int> a(n), b(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> a[i];
        }
        for (int i = 0; i < n; ++i)
        {
            cin >> b[i];
        }
        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            ans += 1LL * a[i] * b[i] % mod;
            ans %= mod;
        }
        int p = x;
        for (int i = 0; i + 1 < n; ++i)
        {
            ans = 1LL * ans * x % mod;
            p = 1LL * p * x % mod;
        }
        ans = (ans + p) % mod;
        cout << ans << '\n';
    }
    return 0;
}
// https://official.contest.yandex.ru/opencupXXI/contest/23124/problems/D/?success=43031828#7/2020_11_27/m1N1edUCxn

// Determinant of Sparse Matrix:

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9, mod = 998244353;

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
istream &operator>>(istream &in, modint<MOD> &n) { return in >> n.value; }
template <int32_t MOD>
ostream &operator<<(ostream &out, modint<MOD> n) { return out << n.value; }

using mint = modint<mod>;

vector<mint> BerlekampMassey(vector<mint> S)
{
    int n = (int)S.size(), L = 0, m = 0;
    vector<mint> C(n), B(n), T;
    C[0] = B[0] = 1;
    mint b = 1;
    for (int i = 0; i < n; ++i)
    {
        ++m;
        mint d = S[i];
        for (int j = 1; j <= L; j++)
            d += C[j] * S[i - j];
        if (d == 0)
            continue;
        T = C;
        mint coef = d * b.inv();
        for (int j = m; j < n; j++)
            C[j] -= coef * B[j - m];
        if (2 * L > i)
            continue;
        L = i + 1 - L;
        B = T;
        b = d;
        m = 0;
    }
    C.resize(L + 1);
    C.erase(C.begin());
    for (auto &x : C)
        x *= -1;
    return C;
}
struct Mat
{
    int n, m;
    vector<vector<int>> a;
    Mat() {}
    Mat(int _n, int _m)
    {
        n = _n;
        m = _m;
        a.assign(n, vector<int>(m, 0));
    }
    Mat(vector<vector<int>> v)
    {
        n = v.size();
        m = n ? v[0].size() : 0;
        a = v;
    }
    inline void make_unit()
    {
        assert(n == m);
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; j++)
                a[i][j] = i == j;
        }
    }
    inline Mat operator+(const Mat &b)
    {
        assert(n == b.n && m == b.m);
        Mat ans = Mat(n, m);
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; j++)
            {
                ans.a[i][j] = (a[i][j] + b.a[i][j]) % mod;
            }
        }
        return ans;
    }
    inline Mat operator-(const Mat &b)
    {
        assert(n == b.n && m == b.m);
        Mat ans = Mat(n, m);
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; j++)
            {
                ans.a[i][j] = (a[i][j] - b.a[i][j] + mod) % mod;
            }
        }
        return ans;
    }
    inline Mat operator*(const Mat &b)
    {
        assert(m == b.n);
        Mat ans = Mat(n, b.m);
        for (int i = 0; i < n; ++i)
        {
            for (int k = 0; k < m; k++)
            {
                for (int j = 0; j < b.m; j++)
                {
                    ans.a[i][j] = (ans.a[i][j] + 1LL * a[i][k] * b.a[k][j] % mod) % mod;
                }
            }
        }
        return ans;
    }
    inline Mat operator*(int k)
    {
        Mat ans = *this;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; j++)
            {
                ans.a[i][j] = 1LL * ans.a[i][j] * k % mod;
            }
        }
        return ans;
    }
    inline Mat pow(long long k)
    {
        assert(n == m);
        Mat ans(n, n), t = a;
        ans.make_unit();
        while (k)
        {
            if (k & 1)
                ans = ans * t;
            t = t * t;
            k >>= 1;
        }
        return ans;
    }
    inline Mat &operator+=(const Mat &b) { return *this = (*this) + b; }
    inline Mat &operator-=(const Mat &b) { return *this = (*this) - b; }
    inline Mat &operator*=(const Mat &b) { return *this = (*this) * b; }
    inline bool operator==(const Mat &b) { return a == b.a; }
    inline bool operator!=(const Mat &b) { return a != b.a; }
    void print()
    {
        cout << "Matrix: \n";
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; j++)
                cout << a[i][j] << ' ';
            cout << '\n';
        }
        cout << '\n';
    }
};
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

// Let A be an n * n matrix
// A^0, A^1, ..., A^inf follows a recurrence of degree <= n (check Cayley-Hamilton Theorem)
// Find the smallest recurrence P of degree k such that
// A^z = \sum_{i=0}^{k-1}{A^(z - i - 1) \times P_i}
// M contains (x, y, v) which means
// A[x][y] = v, 0-based and all (x, y) should be distinct
// all other elements are zeroes
struct Elem
{
    int x, y;
    mint v;
};
vector<mint> MatrixRecurrence(int n, vector<Elem> M)
{
    vector<mint> rd1, rd2;
    for (int i = 0; i < n; ++i)
    {
        rd1.push_back(1 + rnd() % (mod - 1));
        rd2.push_back(1 + rnd() % (mod - 1));
    }
    vector<mint> v;
    for (int i = 0; i < 2 * n + 2; ++i)
    {
        mint tmp = 0;
        for (int j = 0; j < n; j++)
            tmp += rd2[j] * rd1[j];
        v.push_back(tmp);
        vector<mint> nxt(n);
        for (auto &e : M)
            nxt[e.x] += e.v * rd1[e.y];
        rd1 = nxt;
    }
    auto ans = BerlekampMassey(v);
    return ans;
}
// O(n^2 + n*k) where k is the number of non-zero elements
mint Determinant(int n, vector<Elem> M)
{
    vector<mint> rd;
    for (int i = 0; i < n; ++i)
        rd.push_back(1 + rnd() % (mod - 1));
    for (auto &e : M)
        e.v *= rd[e.y];
    auto ans = MatrixRecurrence(n, M).back();
    if (n % 2 == 0)
        ans *= -1;
    for (auto &x : rd)
        ans /= x;
    return ans;
}
void verify_matrix_recurrence(int n, Mat a, vector<Elem> M)
{
    // cout << "Original "; a.print();
    auto p = MatrixRecurrence(n, M);
    // for (auto x: p) cout << x << ' '; cout << '\n';
    for (int i = p.size(); i <= p.size() + 1; ++i)
    {
        auto PW = (a.pow(i));
        Mat ans(n, n);
        int sz = p.size();
        for (int j = 0; j < sz; j++)
        {
            ans = ans + ((a.pow(i - j - 1)) * p[j].value);
        }
        assert(ans == PW);
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    vector<Elem> M;
    Mat a(n, n);
    for (int i = 0; i < k; ++i)
    {
        int x, y, z;
        cin >> x >> y >> z;
        M.push_back({x, y, z});
        a.a[x][y] = z;
    }
    // verify_matrix_recurrence(n, a, M);
    cout << Determinant(n, M) << '\n';
    return 0;
}
// https://judge.yosupo.jp/problem/sparse_matrix_det

// Determinant under Composite Modulo:

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

// O(n^3 logn)
int gauss(vector<vector<int>> a, const int mod)
{
    int n = (int)a.size();
    if (n != a[0].size())
        return 0;
    int det = 1;
    for (int col = 0, row = 0; col < n && row < n; ++col)
    {
        int mx = row;
        for (int i = row; i < n; ++i)
            if (a[i][col] > a[mx][col])
                mx = i;
        if (a[mx][col] == 0)
            return 0;
        for (int i = col; i < n; ++i)
            swap(a[row][i], a[mx][i]);
        if (row != mx)
            det = det == 0 ? 0 : mod - det;
        for (int i = row + 1; i < n; ++i)
        {
            while (a[row][col])
            {
                int t = a[i][col] / a[row][col];
                for (int j = col; j < n; j++)
                {
                    a[i][j] -= 1LL * a[row][j] * t % mod;
                    if (a[i][j] < 0)
                        a[i][j] += mod;
                    swap(a[i][j], a[row][j]);
                }
                det = det == 0 ? 0 : mod - det;
            }
            for (int j = col; j < n; j++)
                swap(a[row][j], a[i][j]);
            det = det == 0 ? 0 : mod - det;
        }
        det = 1LL * det * a[row][col] % mod;
        ++row;
    }
    return det;
}
int32_t main()
{
    int n, mod;
    while (cin >> n >> mod)
    {
        vector<vector<int>> a(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; j++)
            {
                int k;
                cin >> k;
                k %= mod;
                if (k < 0)
                    k += mod;
                a[i][j] = k;
            }
        }
        cout << gauss(a, mod) << '\n';
    }
    return 0;
}
// https://www.spoj.com/problems/DETER3/en/

// Determinant under Prime Modulo:

#include <bits/stdc++.h>
using namespace std;

const int N = 105, mod = 998244353;

int power(long long n, long long k)
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
int gauss(vector<vector<int>> a)
{
    int n = a.size(), m = (int)a[0].size();
    int free_var = 0;
    const long long MODSQ = (long long)mod * mod;
    int det = 1, rank = 0;
    for (int col = 0, row = 0; col < m && row < n; col++)
    {
        int mx = row;
        for (int k = row; k < n; k++)
            if (a[k][col] > a[mx][col])
                mx = k;
        if (a[mx][col] == 0)
        {
            det = 0;
            continue;
        }
        for (int j = col; j < m; j++)
            swap(a[mx][j], a[row][j]);
        if (row != mx)
            det = det == 0 ? 0 : mod - det;
        det = 1LL * det * a[row][col] % mod;
        int inv = power(a[row][col], mod - 2);
        for (int i = 0; i < n && inv; ++i)
        {
            if (i != row && a[i][col])
            {
                int x = ((long long)a[i][col] * inv) % mod;
                for (int j = col; j < m && x; j++)
                {
                    if (a[row][j])
                        a[i][j] = (MODSQ + a[i][j] - ((long long)a[row][j] * x)) % mod;
                }
            }
        }
        row++;
        ++rank;
    }
    return det;
}

int32_t main()
{
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    cout << gauss(a) << '\n';
    return 0;
}