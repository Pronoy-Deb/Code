// Linear Recurrence:

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
istream &operator>>(istream &in, modint<MOD> &n) { return in >> n.value; }
template <int32_t MOD>
ostream &operator<<(ostream &out, modint<MOD> n) { return out << n.value; }

using mint = modint<mod>;

vector<mint> combine(int n, vector<mint> &a, vector<mint> &b, vector<mint> &tr)
{
    vector<mint> res(n * 2 + 1, 0);
    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < n + 1; j++)
            res[i + j] += a[i] * b[j];
    }
    for (int i = 2 * n; i > n; --i)
    {
        for (int j = 0; j < n; j++)
            res[i - 1 - j] += res[i] * tr[j];
    }
    res.resize(n + 1);
    return res;
};
// transition -> for(i = 0; i < x; i++) f[n] += tr[i] * f[n-i-1]
// S contains initial values, k is 0 indexed
mint LinearRecurrence(vector<mint> &S, vector<mint> &tr, long long k)
{
    int n = S.size();
    assert(n == (int)tr.size());
    if (n == 0)
        return 0;
    if (k < n)
        return S[k];
    vector<mint> pol(n + 1), e(pol);
    pol[0] = e[1] = 1;
    for (++k; k; k /= 2)
    {
        if (k % 2)
            pol = combine(n, pol, e, tr);
        e = combine(n, e, e, tr);
    }
    mint res = 0;
    for (int i = 0; i < n; i++)
        res += pol[i + 1] * S[i];
    return res;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<mint> S(n);
        for (int i = 0; i < n; i++)
            cin >> S[i];
        vector<mint> tr(n);
        for (int i = 0; i < n; i++)
            cin >> tr[i];
        int k;
        cin >> k;
        --k;
        cout << LinearRecurrence(S, tr, k) << '\n';
    }
    return 0;
}

// Linear Recurrence Fastest:

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9, mod = 104857601;

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
int LinearRecurrence(vector<int> &S, vector<int> &C, long long n)
{
    if (C.empty())
        return 0;
    int k = (int)C.size();
    assert((int)S.size() == k);
    if (n < k)
        return S[n];
    auto Q = C;
    for (auto &x : Q)
        x = mod - x;
    Q.insert(Q.begin(), 1);
    auto P = multiply(S, Q);
    P.resize(k);
    while (n)
    {
        auto Qminus = Q;
        for (int i = 1; i < (int)Qminus.size(); i += 2)
            Qminus[i] = mod - Qminus[i];
        auto S = multiply(P, Qminus);
        auto T = multiply(Q, Qminus);
        if (n & 1)
        {
            for (int i = 1; i < (int)S.size(); i += 2)
                P[i >> 1] = S[i];
            for (int i = 0; i < (int)T.size(); i += 2)
                Q[i >> 1] = T[i];
        }
        else
        {
            for (int i = 0; i < (int)S.size(); i += 2)
                P[i >> 1] = S[i];
            for (int i = 0; i < (int)T.size(); i += 2)
                Q[i >> 1] = T[i];
        }
        n >>= 1;
    }
    return P[0];
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int k;
    long long n;
    cin >> k >> n;
    n--;
    vector<int> S(k), C(k);
    for (int i = 0; i < k; i++)
        cin >> S[i];
    for (int i = 0; i < k; i++)
        cin >> C[i];
    cout << LinearRecurrence(S, C, n) << '\n';
    return 0;
}
// https://www.codechef.com/problems/RNG

// Linear Recurrence with Polynomial Coefficients:

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

using ll = long long;

// credit: unknown

int mod_inv(int a, int mod)
{
    int b = mod, s = 1, t = 0, old_a = a;
    while (b)
    {
        int q = a / b;
        swap(a %= b, b);
        swap(s -= t * q, t);
    }
    if (a != 1)
    {
        fprintf(stderr,
                "Error: %d^{-1} mod %d does not exist.\n\n", old_a, mod);
        assert(0);
    }
    return s < 0 ? s + mod : s;
}

vector<int> extended(int n,
                     const vector<vector<int>> &coeffs, const vector<int> &terms, int mod)
{

    vector<int> ret(max<int>(n + 1, terms.size()));
    copy(terms.begin(), terms.end(), ret.begin());
    const int order = coeffs.size() - 1;
    const int deg = coeffs[0].size() - 1;
    assert((int)terms.size() >= order);
    for (int m = terms.size(); m <= n; ++m)
    {
        int s = 0;
        for (int i = 1; i <= order; ++i)
        {
            int k = m - i, t = ret[k];
            for (int d = 0; d <= deg; ++d)
            {
                s = (s + ll(t) * coeffs[i][d]) % mod;
                t = ll(t) * k % mod;
            }
        }
        int denom = 0, mpow = 1;
        for (int d = 0; d <= deg; ++d)
        {
            denom = (denom + ll(mpow) * coeffs[0][d]) % mod;
            mpow = ll(mpow) * m % mod;
        }
        ret[m] = ll(mod - s) * mod_inv(denom, mod) % mod;
    }
    return ret;
}

vector<vector<int>> find_recurrence_relation(
    const vector<int> &terms, const int deg, const int mod, bool verify = true)
{

    const int n = terms.size();
    const int B = (n + 2) / (deg + 2); // number of blocks
    const int C = B * (deg + 1);       // number of columns
    const int R = n - (B - 1);         // number of rows
    assert(B >= 2);
    assert(R >= C - 1);

    auto mul = [mod](int a, int b)
    {
        return ll(a) * b % mod;
    };
    auto fixed = [mod](int a)
    {
        return (a %= mod) < 0 ? a + mod : a;
    };
    auto error = [](int order, int deg)
    {
        fprintf(stderr,
                "Error: Could not find a recurrence relation "
                "of order <= %d and degree <= %d.\n\n",
                order, deg);
        assert(0);
    };

    vector<vector<int>> mat(R, vector<int>(C));
    for (int y = 0; y < R; ++y)
    {
        for (int b = 0; b < B; ++b)
        {
            for (int d = 0, v = fixed(terms[y + b]); d <= deg; ++d)
            {
                mat[y][b * (deg + 1) + d] = v;
                v = mul(v, y + b);
            }
        }
    }

    int rank = 0;
    for (int x = 0; x < C; ++x)
    {
        int pivot = -1;
        for (int y = rank; y < R; ++y)
            if (mat[y][x] != 0)
            {
                pivot = y;
                break;
            }
        if (pivot < 0)
            break;
        if (pivot != rank)
            swap(mat[rank], mat[pivot]);
        int inv = mod_inv(mat[rank][x], mod);
        for (int x2 = x; x2 < C; ++x2)
            mat[rank][x2] = mul(mat[rank][x2], inv);
        for (int y = rank + 1; y < R; ++y)
            if (mat[y][x])
            {
                int c = mod - mat[y][x];
                for (int x2 = x; x2 < C; ++x2)
                {
                    mat[y][x2] = (ll(mat[y][x2]) + ll(c) * mat[rank][x2]) % mod;
                }
            }
        ++rank;
    }

    if (rank == C)
        error(B - 1, deg);

    for (int y = rank - 1; y >= 0; --y)
        if (mat[y][rank])
        {
            assert(mat[y][y] == 1);
            int c = mod - mat[y][rank];
            for (int y2 = 0; y2 < y; ++y2)
            {
                mat[y2][rank] = (mat[y2][rank] + ll(c) * mat[y2][y]) % mod;
            }
        }

    int order = rank / (deg + 1);
    vector<vector<int>> ret(order + 1, vector<int>(deg + 1));
    ret[0][rank % (deg + 1)] = 1;
    for (int y = rank - 1; y >= 0; --y)
    {
        int k = order - y / (deg + 1), d = y % (deg + 1);
        ret[k][d] = (mod - mat[y][rank]) % mod;
    }

    if (verify)
    {
        auto extended_terms = extended(n - 1, ret,
                                       vector<int>(terms.begin(), terms.begin() + order), mod);
        for (int i = 0; i < (int)terms.size(); ++i)
        {
            if (fixed(terms[i] - extended_terms[i]) != 0)
                error(B - 1, deg);
        }
    }

    auto verbose = [&]
    {
        int last = verify ? n - 1 : order + R - 1;
        fprintf(stderr,
                "[ Found a recurrence relation ]\n"
                "- order %d\n"
                "- degree %d\n"
                "- verified up to a(%d) (number of non-trivial terms: %d)\n",
                order, deg, last, (last + 1) - ((deg + 2) * (order + 1) - 2));
        fprintf(stderr, "{\n");
        for (int k = 0; k <= order; ++k)
        {
            fprintf(stderr, "  {");
            for (int d = 0; d <= deg; ++d)
            {
                if (d)
                    fprintf(stderr, ", ");
                fprintf(stderr, "%d", ret[k][d] <= mod / 2 ? ret[k][d] : ret[k][d] - mod);
            }
            fprintf(stderr, "}%s\n", k == order ? "" : ",");
        }
        fprintf(stderr, "}\n\n");
    };
    verbose();

    return ret;
}

void show_extended_sequence(int n, const vector<int> &terms, int degree, int mod)
{
    auto coeffs = find_recurrence_relation(terms, degree, mod);
    auto extended_terms = extended(n, coeffs, terms, mod);
    for (int i = 0; i < (int)extended_terms.size(); ++i)
    {
        printf("%d %d\n", i, extended_terms[i]);
    }
    puts("");
}

// transition -> for(i = 0; i < k; i++) f[n] += tr[i] * f[n-i-1]
// here tr[i] is a polynomial. order = k and degree = degree of tr[i]
// given first few values of f, it will extract the recurrence
int main()
{
    const int mod = 1e9 + 7;

    // Ones
    // show_extended_sequence(10, {1, 1, 1, 1, 1}, 0, mod);

    // Factorials
    // show_extended_sequence(10, {1, 2, 6, 24, 120}, 1, mod);

    // Catalan numbers
    show_extended_sequence(10, {1, 1, 2, 5, 14, 42}, 1, mod);

    // Subfactorials
    // show_extended_sequence(10, {1, 0, 1, 2, 9, 44, 265}, 1, mod);

    // Motzkin numbers
    // show_extended_sequence(10, {1, 1, 2, 4, 9, 21, 51}, 1, mod);

    // Large Schröder numbers
    // show_extended_sequence(10, {1, 2, 6, 22, 90, 394, 1806}, 1, mod);

    // Error: (n + 1) a_n \equiv 0 (mod 2)
    // show_extended_sequence(10, {0, 1, 0, 1, 0, 1, 0, 1, 0, 1}, 1, 2);

    // Hertzsprung's problem: order 4, degree 1
    // show_extended_sequence(20, {
    //   1, 1, 0, 0, 2,
    //   14, 90, 646, 5242, 47622,
    //   479306, 5296790, 63779034, 831283558, 661506141
    // }, 1, mod);

    // yukicoder No.93: order 13, degree 2
    // show_extended_sequence(100, {
    //   1, 1, 2, 2, 8,
    //   28, 152, 952, 7208, 62296,
    //   605864, 6522952, 76951496, 986411272, 647501133,
    //   653303042, 170637030, 248109503, 700583494, 619914523,
    //   682935856, 443753916, 423068688, 507501942, 315541972,
    //   110825117, 848156395, 798418282, 920964362, 23823302,
    //   114894774, 279365223, 992413784, 833179437, 785518302,
    //   524368220, 42214454, 140345871, 188150268, 808714798,
    //   718376249, 732000901, 955005007, 139255097, 484615744,
    //   615066955, 726914809, 856989248, 460819998, 321277105,
    //   536397091, 555447300, 597473569, 217709372, 24981477,
    //   143561526, 171000806, 137649694, 749333590, 700935246,
    //   916763337, 762367836, 296796066, 236278263, 398507715,
    // }, 2, mod);

    // binom(3 * i, i) ^ 2 + binom(2 * i, i + 1): order 8, degree 5
    // show_extended_sequence(128, {
    //   1, 10, 229, 7071, 245081,
    //   9018219, 344622888, 521041312, 917599501, 328470621,
    //   920199271, 726809819, 712906773, 531692419, 688496750,
    //   140388924, 514070772, 712606107, 333670208, 549905369,
    //   504023887, 34217948, 890190161, 703909490, 6403597,
    //   623962638, 685637246, 126160387, 956873888, 9766247,
    //   864866393, 563563889, 613532405, 710746029, 182520210,
    //   914377932, 648461424, 715143730, 918800735, 503145605,
    //   27402642, 282029583, 635728688, 91880493, 896737996,
    //   773282006, 625726102, 992524580, 494071629, 82874383,
    //   536460288, 218839718, 406647024, 248185000, 360613817,
    //   546217158, 925224608, 482921337, 928327434, 372559325,
    //   614987117, 601351833, 765504201, 230666863, 98348380,
    // }, 5, mod);
    return 0;
}
// https://min-25.hatenablog.com/entry/2018/05/10/212805