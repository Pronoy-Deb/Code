// Miller-Rabin Method of Primality Test:

int64_t pri[N >> 3], spf[N];
void pre() {
    for (int i = 2, c = 0; i < N; ++i) {
        if (!spf[i]) pri[c++] = spf[i] = i;
        for (int j = 0, k; (k = i * pri[j]) < N; ++j) {
            spf[k] = pri[j]; if (spf[i] == spf[k]) break;
        }
    }
}
int64_t mmul(int64_t x, int64_t y, int64_t m) {
    int64_t res = __int128(x) * y % m; return res;
    // int64_t res = x * y - (int64_t)((long double)x * y / m + 0.5) * m;
    // return res < 0 ? res + m : res;
}
int64_t bex(int64_t x, int64_t n, int64_t m) {
    int64_t res = 1 % m;
    while (n) {
        if (n & 1) res = mmul(res, x, m);
        x = mmul(x, x, m); n >>= 1;
    }
    return res;
}
bool ip(int64_t n) {
	if (n < 2 || (~n & 1) || !(n % 3)) return (n == 2 || n == 3);
    if (n < N) return spf[n] == n;
    int64_t s = 0, r = n - 1;
    while (~r & 1) { r >>= 1; ++s; }
    for (int i = 0; pri[i] < n && pri[i] < 32; ++i) {
        int64_t c = bex(pri[i], r, n);
        for (int j = 0; j < s; ++j) {
            int64_t d = mmul(c, c, n);
            if (d == 1 && c != 1 && c != (n - 1)) return false;
            c = d;
        }
        if (c != 1) return false;
    }
    return true;
}

// Complexity: O(k * log^2(n))
// Fermat Method of Primality Test:

mt19937_64 ran(chrono::high_resolution_clock::now().time_since_epoch().count());
int64_t bex(int64_t a, int64_t n, int64_t p) {
	int64_t res = 1; a %= p;
	while (n) {
		if (n & 1) res = (res * a) % p;
		n >>= 1; a = (a * a) % p;
	}
	return res;
}
bool ip(int64_t n, int k = 10) {
	if (n < 2 || (~n & 1) || !(n % 3)) return (n == 2 || n == 3);
    while (k--) {
        int64_t a = 2 + ran() % (n - 4);
        if (gcd(n, a) != 1 || bex(a, n - 1, n) != 1) return false;
	}
	return true;
}

// Solovay-Strassen method of Primality Test:

mt19937_64 ran(chrono::high_resolution_clock::now().time_since_epoch().count());
int64_t bex(int64_t a, int64_t n, int64_t p) {
	int64_t res = 1; a %= p;
	while (n) {
		if (n & 1) res = (res * a) % p;
		n >>= 1; a = (a * a) % p;
	}
	return res;
}
int64_t jaco(int64_t a, int64_t n) {
	if (!a) return 0; int64_t ans = 1;
	if (a < 0) {
		a = -a; if (n % 4 == 3) ans = -ans;
	}
	if (a == 1) return ans;
	while (a) {
		if (a < 0) {
			a = -a; if (n % 4 == 3) ans = -ans;
		}
		while (~a & 1) {
			a >>= 1; if (n % 8 == 3 || n % 8 == 5) ans = -ans;
		}
		swap(a, n);
		if (a % 4 == 3 && n % 4 == 3) ans = -ans;
		a %= n; if (a > (n >> 1)) a = a - n;
	}
	return (n == 1 ? ans : 0);
}
bool ip(int64_t p, int k = 12) {
	if (p < 2 || (~p & 1) || !(p % 3)) return (p == 2 || p == 3);
	while (k--) {
		int64_t a = ran() % (p - 1) + 1, jb = (p + jaco(a, p)) % p, m = bex(a, (p - 1) >> 1, p);
		if (!jb || m != jb) return false;
	}
	return true;
}

// Complexity: O(sqrt(n))

bool ip(int64_t n) {
	if (n < 2 || (~n & 1) || !(n % 3)) return (n == 2 || n == 3);
	for (int64_t i = 5; i * i <= n; i += 6) {
		if (!(n % i) || !(n % (i + 2))) return false;
	}
	return true;
}

// OR,

bool ip(int64_t n) {
	if (n < 2 || (~n & 1) || !(n % 3)) return (n == 2 || n == 3);
    for (int64_t i = 3; i * i <= n; i += 2) {
        if (!(n % i)) return false;
    }
    return true;
}

// Number of Primes from [1 - n] using Meissel-Lehmer Algorithm: O(n ^ (2 / 3))

const int64_t N = 2e7 + 10, MXP = 7, MXN = 50, MXM = 2 * 3 * 7 * 5 * 11 * 13 * 17;
constexpr auto fdv = [](const int64_t& a, const int& b) ->int64_t { return double(a) / b + 1e-9; };
vector<int> pri; bitset<N> ip; int pro[MXP], pi[N], dp[MXN][MXM];

void pre() {
    int64_t i, j; assert(MXN >= MXP);
    ip[2] = true; for (i = 3; i < N; i += 2) ip[i] = true;
    for (i = 3; i * i < N; i += 2) {
        for (j = i * i; ip[i] && j < N; j += (i << 1)) ip[j] = false;
    }
    for (i = 1; i < N; ++i) {
        pi[i] = pi[i - 1] + ip[i]; if (ip[i]) pri.push_back(i);
    }
    for (pro[0] = pri[0], i = 1; i < MXP; ++i) pro[i] = pro[i - 1] * pri[i];
    for (i = 0; i < MXM; ++i) dp[0][i] = i;
    for (i = 1; i < MXN; ++i) {
        for (j = 1; j < MXM; ++j)
            dp[i][j] = dp[i - 1][j] - dp[i - 1][fdv(j, pri[i - 1])];
    }
}
uint64_t phi(int64_t m, int n) {
    if (!n) return m; if (n < MXN && m < MXM) return dp[n][m];
    if (n < MXP) return dp[n][m % pro[n - 1]] + fdv(m, pro[n - 1]) * dp[n][pro[n - 1]];
    int64_t p = pri[n - 1]; if (m < N && p * p >= m) return pi[m] - n + 1;
    if (p * p * p < m || m >= N) return phi(m, n - 1) - phi(fdv(m, p), n - 1);
    int lim = pi[(int)sqrtl(0.5 + m)];
    uint64_t res = pi[m] - ((lim + n - 2) * (lim - n + 1) >> 1);
    for (int i = n; i < lim; ++i) res += pi[fdv(m, pri[i])];
    return res;
}
uint64_t ip(int64_t n) {
    if (n < N) return pi[n]; int s = sqrtl(0.5 + n), c = cbrtl(0.5 + n);
    uint64_t res = phi(n, pi[c]) + pi[c] - 1;
    for (int i = pi[c]; i < pi[s]; ++i) res -= ip(fdv(n, pri[i])) - i;
    return res;
}

// Prime Factorization:
// To store all the prime factors: O(sqrt(n))

auto pfac(int64_t n) {
    vector<int64_t> v;
    while (~n & 1) {
        v.push_back(2); n >>= 1;
    }
    for (int64_t i = 3; i * i <= n; i += 2) {
        while (!(n % i)) {
            v.push_back(i); n /= i;
        }
    }
    if (n > 2) v.push_back(n); return v;
}

// To store the count of prime factors:

auto pfac(int64_t n) {
    map<int64_t, int64_t> mp;
    while (~n & 1) {
        ++mp[2]; n >>= 1;
    }
    for (int64_t i = 3; i * i <= n; i += 2) {
        while (!(n % i)) {
            ++mp[i]; n /= i;
        }
    }
    if (n > 2) ++mp[n]; return mp;
}

// Sieve Approach: O(n * (log(log(n))) + log(n))

int64_t spf[N]; bool sv[N];
void pre() {
    spf[2] = 2;
    for (int i = 4; i < N; i += 2) {
        sv[i] = true; spf[i] = 2;
    }
    for (int64_t i = 3; i < N; i += 2) {
        if (!sv[i]) {
            spf[i] = i;
            for (int64_t j = i * i; j < N; j += (i << 1)) {
                sv[j] = true; if (!spf[j]) spf[j] = i;
            }
        }
    }
}
auto pfac(int64_t n) {
    vector<int64_t> v;
    while (n > 1) {
        int64_t p = spf[n];
        while (!(n % p)) {
            n /= p; v.push_back(p);
        }
    }
    return v;
}

// To store the count of prime numbers:
// Complexity: O(N * (log(log(N))) + log(n))

int64_t spf[N]; bool sv[N];
auto pre() {
    spf[2] = 2;
    for (int i = 4; i < N; i += 2) {
        sv[i] = true; spf[i] = 2;
    }
    for (int64_t i = 3; i < N; i += 2) {
        if (!sv[i]) {
            spf[i] = i;
            for (int64_t j = i * i; j < N; j += (i << 1)) {
                sv[j] = true; if (!spf[j]) spf[j] = i;
            }
        }
    }
}
auto pfac(int64_t n) {
    map<int64_t, int64_t> mp;
    while (n > 1) {
        int64_t p = spf[n];
        while (!(n % p)) {
            n /= p; ++mp[p];
        }
    }
    return mp;
}

// Prime Factorization Fastest:
https://judge.yosupo.jp/problem/factorize

struct Mint {
    uint64_t n; static uint64_t mod, inv, r2;
    Mint() : n(0) {}
    Mint(const uint64_t &x) : n(init(x)) {}
    static uint64_t init(const uint64_t &w) { return reduce(__uint128_t(w) * r2); }
    static void set_mod(const uint64_t &m) {
        mod = inv = m; for (int i = 0; i < 5; ++i) inv *= 2 - inv * m;
        r2 = -__uint128_t(m) % m;
    }
    static uint64_t reduce(const __uint128_t &x) {
        uint64_t y = uint64_t(x >> 64) - uint64_t((__uint128_t(uint64_t(x) * inv) * mod) >> 64);
        return int64_t(y) < 0 ? y + mod : y;
    }
    Mint &operator+=(const Mint &x) {
        n += x.n - mod; if (int64_t(n) < 0) n += mod; return *this;
    }
    Mint &operator+(const Mint &x) const { return Mint(*this) += x; }
    Mint &operator*=(const Mint &x) {
        n = reduce(__uint128_t(n) * x.n); return *this;
    }
    Mint &operator*(const Mint &x) const { return Mint(*this) *= x; }
    uint64_t val() const { return reduce(n); }
};
uint64_t Mint::mod, Mint::inv, Mint::r2;
bool suspect(const uint64_t &a, const uint64_t &s, uint64_t d, const uint64_t &n) {
    if (Mint::mod != n) Mint::set_mod(n);
    Mint x(1), xx(a), one(x), minusone(n - 1);
    while (d > 0) {
        if (d & 1) x *= xx; xx *= xx; d >>= 1;
    }
    if (x.n == one.n) return true;
    for (unsigned int r = 0; r < s; ++r) {
        if (x.n == minusone.n) return true; x *= x;
    }
    return false;
}
bool ip(const uint64_t &n) {
    if (n < 2 || (~n & 1) || !(n % 3)) return (n == 2 || n == 3);
    uint64_t d = n - 1, s = 0; while (~d & 1) ++s, d >>= 1;
    static const uint64_t a_big[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    static const uint64_t a_small[] = {2, 7, 61};
    if (n <= 4759123141LL) {
        for (auto &&p : a_small) {
            if (p >= n) break; if (!suspect(p, s, d, n)) return false;
        }
    }
    else {
        for (auto &&p : a_big) {
            if (p >= n) break; if (!suspect(p, s, d, n)) return false;
        }
    }
    return true;
}
uint64_t rho_pollard(const uint64_t &n) {
    if (~n & 1) return 2u; static random_device rng;
    uniform_int_distribution<uint64_t> rr(1, n - 1);
    if (Mint::mod != n) Mint::set_mod(n);
    for (;;) {
        uint64_t c_ = rr(rng), g = 1, r = 1, m = 500;
        Mint y(rr(rng)), xx(0), c(c_), ys(0), q(1);
        while (g == 1) {
            xx.n = y.n; for (unsigned int i = 1; i <= r; ++i) y *= y, y += c;
            uint64_t k = 0; g = 1;
            while (k < r && g == 1) {
                for (unsigned int i = 1; i <= (m > (r - k) ? (r - k) : m); ++i) {
                    ys.n = y.n; y *= y; y += c; uint64_t xxx = xx.val(), yyy = y.val();
                    q *= Mint(xxx > yyy ? xxx - yyy : yyy - xxx);
                }
                g = __gcd<uint64_t>(q.val(), n); k += m;
            }
            r <<= 1;
        }
        if (g == n) g = 1;
        while (g == 1) {
            ys *= ys; ys += c; uint64_t xxx = xx.val(), yyy = ys.val();
            g = __gcd<uint64_t>(xxx > yyy ? xxx - yyy : yyy - xxx, n);
        }
        if (g != n && ip(g)) return g;
    }
    assert(69 == 420);
}
template <typename T>
vector<T> factor(T n) {
    if (n < 2) return {};
    if (ip(n)) return {n};
    T d = rho_pollard(static_cast<uint64_t>(n));
    vector<T> l = factor(d), r = factor(n / d);
    l.insert(l.end(), r.begin(), r.end());
    return l;
}

// Operation:
    uint64_t n; cin >> n;
    vector<uint64_t> fac = factor(n);
    sort(fac.begin(), fac.end());
    cout << fac.size() << ' ';
    for (auto &&f : fac) cout << f << ' ';

// Prime Basis:

#include <bits/stdc++.h>
using namespace std;

// https://codeforces.com/blog/entry/108053
// for a set of n elements S, computes the basis of the set S
// any element of S will be representable using the elements of the basis.
// gcd(basis[i], basis[j]) == 1 for  all i < j
// all x * y, x / y, gcd(x, y) and lcm(x, y) for x in S, y in S will also be representable
// this also holds for all subsets of S
// basis size = n * log_log(A) where A = max(S)
// takes O(n^2 log_A) time to build the whole basis
template <typename T>
T gcd(T a, T b)
{
    return b == 0 ? a : gcd(b, a % b);
}
template <typename T>
struct PrimeBasis
{
    void reduce_pair(T &x, T &y)
    {
        bool to_swap = 0;
        if (x > y)
        {
            to_swap ^= 1;
            swap(x, y);
        }
        while (x > 1 && y % x == 0)
        {
            y /= x;
            if (x > y)
            {
                to_swap ^= 1;
                swap(x, y);
            }
        }
        if (to_swap)
            swap(x, y);
    }
    vector<T> basis;
    void solve_inner(int pos, T &val)
    {
        while (basis[pos] % val == 0)
            basis[pos] /= val;
        vector<T> curr_basis = {basis[pos], val};
        int ptr = 1;
        while (ptr < curr_basis.size())
        {
            for (int i = 0; i < ptr; i++)
            {
                reduce_pair(curr_basis[i], curr_basis[ptr]);
                if (curr_basis[ptr] == 1)
                    break;
                if (curr_basis[i] == 1)
                    break;
                T g = gcd(curr_basis[ptr], curr_basis[i]);
                if (g > 1)
                {
                    curr_basis[ptr] /= g;
                    curr_basis[i] /= g;
                    curr_basis.push_back(g);
                }
            }
            ++ptr;
        }
        basis[pos] = curr_basis[0];
        val = curr_basis[1];
        for (int i = 2; i < curr_basis.size(); i++)
            if (curr_basis[i] > 1)
                basis.push_back(curr_basis[i]);
        if (basis[pos] == 1)
        {
            swap(basis[pos], basis.back());
            basis.pop_back();
        }
    }
    void add_element(T val)
    {
        for (int i = 0; i < basis.size(); i++)
        {
            reduce_pair(val, basis[i]);
            if (basis[i] == 1)
            {
                swap(basis[i], basis.back());
                basis.pop_back();
                break;
            }
            if (val == 1)
                return;
            if (gcd(basis[i], val) > 1)
                solve_inner(i, val);
        }
        if (val > 1)
            basis.push_back(val);
    }
    void verify_basis()
    {
        for (int i = 0; i < basis.size(); i++)
        {
            for (int j = i + 1; j < basis.size(); j++)
            {
                assert(gcd(basis[i], basis[j]) == 1);
            }
        }
    }
    void verify_element(T x)
    {
        for (auto &k : basis)
        {
            while (x % k == 0)
                x /= k;
        }
        assert(x == 1);
    }
    vector<int> factorize(T x)
    {
        vector<int> factors(basis.size());
        for (int i = 0; i < basis.size(); i++)
        {
            while (x % basis[i] == 0)
            {
                factors[i]++;
                x /= basis[i];
            }
        }
        return factors;
    }
};
vector<int> lcm(vector<int> a, vector<int> b)
{
    for (int i = 0; i < a.size(); i++)
    {
        a[i] = max(a[i], b[i]);
    }
    return a;
}
using ll = int64_t;
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<ll> a(n);
    PrimeBasis<ll> B;
    for (int i = 0; i < n; i++)
    {
        ll x;
        cin >> x;
        B.add_element(x);
        a[i] = x;
    }
    vector<pair<vector<int>, ll>> v;
    for (int i = 0; i < n; i++)
    {
        v.push_back({B.factorize(a[i]), a[i]});
    }
    vector<ll> ans;
    while (!v.empty())
    {
        bool found = false;
        for (int i = 0; i < v.size(); i++)
        {
            auto [fac, x] = v[i];
            vector<int> cur = vector<int>(B.basis.size(), 0);
            for (int j = 0; j < v.size(); j++)
            {
                if (i == j)
                    continue;
                cur = lcm(cur, v[j].first);
            }
            if (cur != lcm(cur, fac))
            {
                ans.push_back(x);
                v.erase(find(v.begin(), v.end(), v[i]));
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "No\n";
            return 0;
        }
    }
    reverse(ans.begin(), ans.end());
    cout << "Yes\n";
    for (auto x : ans)
    {
        cout << x << ' ';
    }
    cout << '\n';
    return 0;
}
// https://atcoder.jp/contests/arc122/tasks/arc122_e

// Prime counting Function:

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

namespace pcf
{
// initialize once by calling init()
#define MAXN 20000010      // initial sieve limit
#define MAX_PRIMES 2000010 // max size of the prime array for sieve
#define PHI_N 100000
#define PHI_K 100

    int len = 0; // total number of pri generated by sieve
    int pri[MAX_PRIMES];
    int pref[MAXN];       // pref[i] --> number of pri <= i
    int dp[PHI_N][PHI_K]; // precal of yo(n,k)
    bitset<MAXN> f;
    void sieve(int n)
    {
        f[1] = true;
        for (int i = 4; i <= n; i += 2)
            f[i] = true;
        for (int i = 3; i * i <= n; i += 2)
        {
            if (!f[i])
            {
                for (int j = i * i; j <= n; j += i << 1)
                    f[j] = 1;
            }
        }
        for (int i = 1; i <= n; i++)
        {
            if (!f[i])
                pri[len++] = i;
            pref[i] = len;
        }
    }
    void init()
    {
        sieve(MAXN - 1);
        // precalculation of phi upto size (PHI_N,PHI_K)
        for (int n = 0; n < PHI_N; n++)
            dp[n][0] = n;
        for (int k = 1; k < PHI_K; k++)
        {
            for (int n = 0; n < PHI_N; n++)
            {
                dp[n][k] = dp[n][k - 1] - dp[n / pri[k - 1]][k - 1];
            }
        }
    }
    // returns the number of integers less or equal n which are
    // not divisible by any of the first k pri
    // recurrence --> yo(n, k) = yo(n, k-1) - yo(n / p_k , k-1)
    // for sum of pri yo(n, k) = yo(n, k-1) - p_k * yo(n / p_k , k-1)
    int64_t yo(int64_t n, int k)
    {
        if (n < PHI_N && k < PHI_K)
            return dp[n][k];
        if (k == 1)
            return ((++n) >> 1);
        if (pri[k - 1] >= n)
            return 1;
        return yo(n, k - 1) - yo(n / pri[k - 1], k - 1);
    }
    // complexity: n^(2/3).(log n^(1/3))
    int64_t Legendre(int64_t n)
    {
        if (n < MAXN)
            return pref[n];
        int lim = sqrt(n) + 1;
        int k = upper_bound(pri, pri + len, lim) - pri;
        return yo(n, k) + (k - 1);
    }
    // runs under 0.2s for n = 1e12
    int64_t Lehmer(int64_t n)
    {
        if (n < MAXN)
            return pref[n];
        int64_t w, res = 0;
        int b = sqrt(n), c = Lehmer(cbrt(n)), a = Lehmer(sqrt(b));
        b = Lehmer(b);
        res = yo(n, a) + ((1LL * (b + a - 2) * (b - a + 1)) >> 1);
        for (int i = a; i < b; i++)
        {
            w = n / pri[i];
            int lim = Lehmer(sqrt(w));
            res -= Lehmer(w);
            if (i <= c)
            {
                for (int j = i; j < lim; j++)
                {
                    res += j;
                    res -= Lehmer(w / pri[j]);
                }
            }
        }
        return res;
    }
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    pcf::init();
    int64_t n;
    cin >> n;
    cout << pcf::Lehmer(n) << '\n';
    return 0;
}
// https://judge.yosupo.jp/problem/counting_primes

// Prime Number System:

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9, mod = 1e9 + 7;

int spf[N];
vector<int> pri;
void linear_sieve()
{
    for (int i = 2; i < N; i++)
    {
        if (spf[i] == 0)
            spf[i] = i, pri.push_back(i);
        int sz = pri.size();
        for (int j = 0; j < sz && i * pri[j] < N && pri[j] <= spf[i]; j++)
        {
            spf[i * pri[j]] = pri[j];
        }
    }
}
int power(int64_t n, int64_t k)
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
struct base
{ // doesn't support zero
    map<int, int> mp;
    base() {}
    base(int n)
    {
        while (n > 1)
        {
            int k = spf[n], cnt = 0;
            while (n % k == 0)
            {
                n /= k;
                cnt++;
            }
            mp[k] = cnt;
        }
    }
    base(map<int, int> z)
    {
        mp = z;
    }
    int val()
    {
        int ans = 1;
        for (auto x : mp)
        {
            assert(x.second >= 0);
            ans = 1LL * ans * power(x.first, x.second) % mod;
        }
        return ans;
    }
    base pow(int k)
    {
        map<int, int> ans = mp;
        for (auto &x : ans)
        {
            x.second *= k;
        }
        return base(ans);
    }
    base sqrt()
    {
        map<int, int> ans = mp;
        for (auto &x : ans)
        {
            assert(x.second % 2 == 0);
            x.second /= 2;
        }
        return base(ans);
    }
    base operator*(base p)
    {
        map<int, int> ans = mp;
        for (auto x : p.mp)
        {
            ans[x.first] += x.second;
        }
        return base(ans);
    }
    base operator/(base p)
    {
        map<int, int> ans = mp;
        for (auto x : p.mp)
        {
            ans[x.first] -= x.second;
        }
        return base(ans);
    }
    base &operator*=(base p)
    {
        return *this = (*this) * p;
    }
    base &operator/=(base p)
    {
        return *this = (*this) / p;
    }
    void print()
    {
        bool f = 0;
        for (auto x : mp)
        {
            if (x.second)
            {
                f = 1;
                cout << "(" << x.first << ' ' << x.second << ") ";
            }
        }
        if (!f)
        {
            cout << 1;
        }
        cout << '\n';
    }
};
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    linear_sieve();
    base a = base(10), b = base(15);
    a *= a;
    a = a.sqrt();
    cout << a.val();
    return 0;
}