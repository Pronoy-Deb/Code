// FWHT:

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9, mod = 1e9 + 7;

int POW(int64_t n, int64_t k)
{
    int ans = 1 % mod;
    n %= mod;
    if (n < 0)
        n += mod;
    while (k)
    {
        if (k & 1)
            ans = (int64_t)ans * n % mod;
        n = (int64_t)n * n % mod;
        k >>= 1;
    }
    return ans;
}
const int inv2 = (mod + 1) >> 1;
#define M (1 << 20)
#define OR 0
#define AND 1
#define XOR 2
struct FWHT
{
    int P1[M], P2[M];
    void wt(int *a, int n, int flag = XOR)
    {
        if (n == 0)
            return;
        int m = n / 2;
        wt(a, m, flag);
        wt(a + m, m, flag);
        for (int i = 0; i < m; i++)
        {
            int x = a[i], y = a[i + m];
            if (flag == OR)
                a[i] = x, a[i + m] = (x + y) % mod;
            if (flag == AND)
                a[i] = (x + y) % mod, a[i + m] = y;
            if (flag == XOR)
                a[i] = (x + y) % mod, a[i + m] = (x - y + mod) % mod;
        }
    }
    void iwt(int *a, int n, int flag = XOR)
    {
        if (n == 0)
            return;
        int m = n / 2;
        iwt(a, m, flag);
        iwt(a + m, m, flag);
        for (int i = 0; i < m; i++)
        {
            int x = a[i], y = a[i + m];
            if (flag == OR)
                a[i] = x, a[i + m] = (y - x + mod) % mod;
            if (flag == AND)
                a[i] = (x - y + mod) % mod, a[i + m] = y;
            if (flag == XOR)
                a[i] = 1LL * (x + y) * inv2 % mod, a[i + m] = 1LL * (x - y + mod) * inv2 % mod; // replace inv2 by >>1 if not required
        }
    }
    vector<int> multiply(int n, vector<int> A, vector<int> B, int flag = XOR)
    {
        assert(__builtin_popcount(n) == 1);
        A.resize(n);
        B.resize(n);
        for (int i = 0; i < n; i++)
            P1[i] = A[i];
        for (int i = 0; i < n; i++)
            P2[i] = B[i];
        wt(P1, n, flag);
        wt(P2, n, flag);
        for (int i = 0; i < n; i++)
            P1[i] = 1LL * P1[i] * P2[i] % mod;
        iwt(P1, n, flag);
        return vector<int>(P1, P1 + n);
    }
    vector<int> pow(int n, vector<int> A, int64_t k, int flag = XOR)
    {
        assert(__builtin_popcount(n) == 1);
        A.resize(n);
        for (int i = 0; i < n; i++)
            P1[i] = A[i];
        wt(P1, n, flag);
        for (int i = 0; i < n; i++)
            P1[i] = POW(P1[i], k);
        iwt(P1, n, flag);
        return vector<int>(P1, P1 + n);
    }
} t;
int32_t main()
{
    int n;
    cin >> n;
    vector<int> a(M, 0);
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        a[k]++;
    }
    vector<int> v = t.pow(M, a, n, AND);
    int ans = 1;
    for (int i = 1; i < M; i++)
        ans += v[i] > 0;
    cout << ans << '\n';
    ;
    return 0;
}
// https://csacademy.com/contest/archive/task/and-closure/statement/

// FWHT in any Base:

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9, mod = 330301441;

int POW(int64_t n, int64_t k)
{
    int ans = 1 % mod;
    n %= mod;
    if (n < 0)
        n += mod;
    while (k)
    {
        if (k & 1)
            ans = (int64_t)ans * n % mod;
        n = (int64_t)n * n % mod;
        k >>= 1;
    }
    return ans;
}
namespace FWHT
{
    const int MXK = 10; //(mod - 1) should be divisible by each base
    struct Matrix
    {
        int a[MXK][MXK], n, m;
        Matrix(int n, int m) : n(n), m(m) {}
    };
    Matrix operator*(Matrix &p, Matrix &q)
    {
        Matrix result(p.n, q.m);
        for (int i = 0; i < p.n; i++)
            for (int j = 0; j < q.m; j++)
            {
                int64_t val = 0;
                for (int k = 0; k < p.m; k++)
                    val += 1LL * p.a[i][k] * q.a[k][j];
                result.a[i][j] = val % mod;
            }
        return result;
    }
    Matrix constructMatrix(int k, bool invert)
    {
        vector<int> divs;
        int x = mod - 1;
        for (int i = 2; i * i <= x; i++)
            if (x % i == 0)
            {
                divs.push_back((mod - 1) / i);
                while (x % i == 0)
                    x /= i;
            }
        if (x > 1)
            divs.push_back((mod - 1) / x);
        int g = 2;
        while (true)
        {
            bool ok = true;
            for (int d : divs)
                if (POW(g, d) == 1)
                    ok = false;
            if (ok)
                break;
            g++;
        }
        int root = POW(g, (mod - 1) / k);
        Matrix result(k, k);
        for (int i = 0; i < k; i++)
        {
            int x = POW(root, invert ? k - i : i);
            for (int j = 0; j < k; j++)
                result.a[i][j] = POW(x, j);
        }
        return result;
    }
    void transform(vector<int> &a, int n, int k, bool invert)
    {
        Matrix M = constructMatrix(k, invert);
        for (int len = 1; len < n; len *= k)
            for (int i = 0; i < n; i += k * len)
                for (int j = 0; j < len; j++)
                {
                    Matrix V(1, k);
                    for (int p = 0; p < k; p++)
                        V.a[0][p] = a[i + j + p * len];
                    V = V * M;
                    for (int p = 0; p < k; p++)
                        a[i + j + p * len] = V.a[0][p];
                }
        if (invert)
        {
            int64_t d = POW(n, mod - 2);
            for (int i = 0; i < n; i++)
                a[i] = a[i] * d % mod;
        }
    }
    // O(k^d * k * d) where d = log_k(MAX VALUE)
    vector<int> multiply(vector<int> a, vector<int> b, int k)
    {
        int n = 1;
        int nw = max((int)a.size() - 1, (int)b.size() - 1);
        while (n <= nw)
            n *= k;
        a.resize(n);
        b.resize(n);
        transform(a, n, k, false);
        transform(b, n, k, false);
        for (int i = 0; i < n; i++)
            a[i] = 1LL * a[i] * b[i] % mod;
        transform(a, n, k, true);
        return a;
    }
    vector<int> pow(vector<int> a, int64_t p, int k)
    {
        int n = 1;
        int nw = (int)a.size() - 1;
        while (n <= nw)
            n *= k;
        a.resize(n);
        transform(a, n, k, false);
        for (int i = 0; i < n; i++)
            a[i] = POW(a[i], p);
        transform(a, n, k, true);
        return a;
    }
}
int cnt[N];
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        memset(cnt, 0, sizeof cnt);
        int n, k;
        int64_t x;
        cin >> n >> k >> x;
        for (int i = 0; i < n; i++)
        {
            int z;
            cin >> z;
            cnt[z]++;
        }
        int cur = POW(2, n), mx = 0;
        vector<int> MEX(N, 0);
        for (int i = 0; cur != 0; i++)
        {
            cur = 1LL * cur * POW(2, 1LL * cnt[i] * (mod - 2ll)) % mod;
            MEX[i] = cur;
            mx = i;
            cur = 1LL * cur * (POW(2, cnt[i]) - 1) % mod;
        }
        MEX.resize(mx + 1);
        auto res = FWHT::pow(MEX, x, k);
        int sum = 0, ans = 0;
        for (auto x : res)
            sum = (sum + x) % mod;
        for (int y = 0; y < res.size(); y++)
        {
            int64_t p = 1LL * res[y] * POW(sum, mod - 2) % mod;
            p = 1LL * POW(p, 3) * POW(y, 2) % mod;
            ans = (ans + POW(p, y)) % mod;
        }
        cout << ans << '\n';
    }
    return 0;
}
// https://www.codechef.com/problems/XORTREEH

// FWHT in Ternary Base:

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
};
template <int32_t MOD>
modint<MOD> operator*(int64_t value, modint<MOD> n) { return modint<MOD>(value) * n; }
template <int32_t MOD>
modint<MOD> operator*(int32_t value, modint<MOD> n) { return modint<MOD>(value % MOD) * n; }
template <int32_t MOD>
ostream &operator<<(ostream &out, modint<MOD> n) { return out << n.value; }

using mint = modint<mod>;

struct cmplx
{
    mint a, b;
    cmplx(int _a = 0, int _b = 0) { a = _a, b = _b; }
    cmplx(mint _a, mint _b) { a = _a, b = _b; }
    cmplx operator+(cmplx x) { return cmplx(a + x.a, b + x.b); }
    cmplx operator*(int k) { return cmplx(a * k, b * k); }
    cmplx operator*(mint k) { return cmplx(a * k, b * k); }
    cmplx operator*(cmplx x)
    {
        mint na = a * x.a - b * x.b;
        mint nb = a * x.b + b * x.a - b * x.b;
        return cmplx(na, nb);
    }
} w(0, 1), w2(mod - 1, mod - 1);

//(mod + 1) should be divisible by 3
typedef vector<cmplx> poly;
struct FWHT
{
    const int BIT = 11;   // log2(MAX VALUE)
    const int M = 177147; // 3^BIT, it must be a power of 3
    void fwht(poly &coefs, poly &vals, bool invert = false)
    {
        vals = coefs;
        int n = vals.size();
        for (int len = 1; len < n; len *= 3)
        {
            int pitch = len * 3;
            int len2 = len * 2;
            for (int i = 0; i < n; i += pitch)
            {
                for (int j = 0; j < len; j++)
                {
                    cmplx a = vals[i + j];
                    cmplx b = vals[i + j + len];
                    cmplx c = vals[i + j + len2];
                    vals[i + j] = a + b + c;
                    vals[i + j + len] = a + b * w + c * w2;
                    vals[i + j + len2] = a + b * w2 + c * w;
                    if (invert)
                        swap(vals[i + j + len], vals[i + j + len2]);
                }
            }
        }
        int inv3 = (mod + 1) / 3;
        mint inv = 1;
        for (int i = 1; i < n; i *= 3)
            inv *= inv3;
        if (invert)
            for (int i = 0; i < n; i++)
                vals[i] = vals[i] * inv;
        return;
    }
    cmplx power(cmplx x, int64_t n)
    {
        cmplx ret(1);
        while (n)
        {
            if (n & 1)
                ret = ret * x;
            x = x * x;
            n >>= 1;
        }
        return ret;
    }
    // converts the binary representation of x to ternary
    // 5 (101 in binary) is transformed to 10 (101 in ternary)
    int tobase3(int x)
    {
        int ret = 0;
        for (int i = BIT - 1; i >= 0; i--)
        {
            ret *= 3;
            if (x & (1 << i))
                ret++;
        }
        return ret;
    }
    poly convert(int n, vector<int> &a)
    {
        poly p(M);
        for (int i = 0; i < n; i++)
        {
            int x = tobase3(i);
            assert(x < M);
            p[x].a += a[i];
        }
        return p;
    }
    // O(3^BIT * BIT)
    vector<int> multiply(int n, vector<int> &a, vector<int> &b)
    {
        poly p = convert(n, a), q = convert(n, b);
        fwht(p, p);
        fwht(q, q);
        for (int i = 0; i < M; i++)
            p[i] = p[i] * q[i];
        fwht(p, p, true);
        vector<int> ans;
        for (int i = 0; i < M; i++)
            ans.push_back(p[i].a.value);
        return ans;
    }
    vector<int> pow(int n, vector<int> &a, int64_t k)
    {
        poly p = convert(n, a);
        fwht(p, p);
        for (int i = 0; i < M; i++)
            p[i] = power(p[i], k);
        fwht(p, p, true);
        vector<int> ans;
        for (int i = 0; i < M; i++)
            ans.push_back(p[i].a.value);
        return ans;
    }
} t;

int32_t main()
{

    return 0;
}
// https://www.codechef.com/problems/MDSWIN