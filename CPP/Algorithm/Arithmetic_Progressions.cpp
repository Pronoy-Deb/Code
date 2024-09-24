// Floor Sum of Arithmetic Progressions:

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
ll sumsq(ll n)
{
    return n / 2 * ((n - 1) | 1);
}
// \sum_{i = 0}^{n - 1}{(a + d * i) / m}, O(log m)
ll floor_sum(ll a, ll d, ll m, ll n)
{
    ll res = d / m * sumsq(n) + a / m * n;
    d %= m;
    a %= m;
    if (!d)
        return res;
    ll to = (n * d + a) / m;
    return res + (n - 1) * to - floor_sum(m - 1 - a, m, d, to);
}
// \sum_{i = 0}^{n - 1}{(a + d * i) % m}
ll mod_sum(ll a, ll d, ll m, ll n)
{
    a = ((a % m) + m) % m;
    d = ((d % m) + m) % m;
    return n * a + d * sumsq(n) - m * floor_sum(a, d, m, n);
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll a, d, n;
    while (cin >> a >> n >> d)
    {
        n = (n - a) / d;
        ll ans = 0;
        for (int k = 0; k < 32; k++)
        {
            ll cur = mod_sum(a, d, (1LL << k + 1), n + 1);
            cur -= mod_sum(a, d, (1LL << k), n + 1);
            if (cur / (1LL << k) & 1)
            {
                ans += 1LL << k;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
// http://poj.org/problem?id=3495

// Generalized Floor Sum of Arithmetic Progressions:

#include <bits/stdc++.h>
using namespace std;

const int N = 25, mod = 1e9 + 7;

using ll = long long;
ll power(ll n, ll k)
{
    int ans = 1 % mod;
    n %= mod;
    if (n < 0)
        n += mod;
    while (k)
    {
        if (k & 1)
            ans = (ll)ans * n % mod;
        n = (ll)n * n % mod;
        k >>= 1;
    }
    return ans;
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

// generates the polynomial explicitely
vector<mint> Lagrange(vector<mint> &x, vector<mint> &y)
{
    int n = x.size();
    vector<mint> ans(n, 0);
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
        down = down.inv() * y[i];
        for (int j = 0; j < n; j++)
            ans[j] += up[j] * down;
    }
    return ans;
}
ll ncr[N][N], d[N][N]; // N > k1 + k2
void prec()
{
    for (int i = 0; i < N; i++)
        ncr[i][0] = 1;
    for (int i = 1; i < N; i++)
    {
        for (int j = 1; j < N; j++)
        {
            ncr[i][j] = (ncr[i - 1][j - 1] + ncr[i - 1][j]) % mod;
        }
    }
    for (int k = 0; k < N; k++)
    {
        vector<mint> y, x;
        mint sum = 0;
        y.push_back(0);
        x.push_back(0);
        for (int i = 1; i <= k + 1; i++)
        {
            sum += mint(i).pow(k);
            y.push_back(sum);
            x.push_back(i);
        }
        auto p = Lagrange(x, y);
        assert(p.size() > k + 1);
        for (int i = 0; i <= k + 1; i++)
            d[k][i] = p[i].value;
    }
    d[0][0] = 1; // to satisfy 0^0 = 1
}
ll power_sum(ll n, int k)
{
    assert(k >= 0);
    ll ans = 0;
    for (int i = 0; i <= k + 1; i++)
    {
        ans += d[k][i] * power(n, i) % mod;
        ans %= mod;
    }
    return ans;
}
// \sum{x=0}^{n}{x^k1 * ((ax + b)/c)^k2} //floor division
// 0^0 = 1
// it solves for all _k1, _k2 s.t. _k1 + _k2 <= k1 + k2
// (a * n + b) should fit in long long
// total complexity: O((k1 + k2)^3 * log(n) * log(mod)
vector<vector<ll>> solve(ll k1, ll k2, ll a, ll b, ll c, ll n)
{
    if (n < 0)
    {
        vector<vector<ll>> ret(k1 + k2 + 1, vector<ll>(k1 + k2 + 1, 0));
        return ret;
    }
    if (!a)
    {
        vector<vector<ll>> ret(k1 + k2 + 1, vector<ll>(k1 + k2 + 1, 0));
        for (int _k1 = 0; _k1 <= k1 + k2; ++_k1)
        {
            ret[_k1][0] = power_sum(n, _k1);
            for (int _k2 = 1; _k1 + _k2 <= k1 + k2; ++_k2)
            {
                ret[_k1][_k2] = (ret[_k1][0] * power(b / c, _k2)) % mod;
            }
        }
        return ret;
    }
    vector<vector<ll>> ret(k1 + k2 + 1, vector<ll>(k1 + k2 + 1, 0));
    assert(c != 0);
    if (a >= c)
    {
        vector<vector<ll>> nxt = solve(k1, k2, a % c, b, c, n);
        for (int _k1 = 0; _k1 <= k1 + k2; ++_k1)
        {
            ret[_k1][0] = power_sum(n, _k1);
            for (int _k2 = 1; _k1 + _k2 <= k1 + k2; ++_k2)
            {
                ret[_k1][_k2] = 0;
                for (int y = 0; y <= _k2; ++y)
                {
                    ret[_k1][_k2] += ((ncr[_k2][y] * power(a / c, y)) % mod) * nxt[_k1 + y][_k2 - y];
                    ret[_k1][_k2] %= mod;
                }
            }
        }
    }
    else if (b >= c)
    {
        vector<vector<ll>> nxt = solve(k1, k2, a, b % c, c, n);
        for (int _k1 = 0; _k1 <= k1 + k2; ++_k1)
        {
            ret[_k1][0] = power_sum(n, _k1);
            for (int _k2 = 1; _k1 + _k2 <= k1 + k2; ++_k2)
            {
                ret[_k1][_k2] = 0;
                for (int y = 0; y <= _k2; ++y)
                {
                    ret[_k1][_k2] += ((ncr[_k2][y] * power(b / c, y)) % mod) * nxt[_k1][_k2 - y];
                    ret[_k1][_k2] %= mod;
                }
            }
        }
    }
    else
    {
        ll m = (a * n + b) / c;
        vector<vector<ll>> nxt = solve(k1, k2, c, c - b - 1, a, m - 1);
        vector<ll> psum(k1 + k2 + 1), pre(k1 + k2 + 1);
        for (int i = 0; i <= k1 + k2; ++i)
            psum[i] = power_sum(m - 1, i);
        for (int _k1 = 0; _k1 <= k1 + k2; ++_k1)
        {
            for (int i = 0; i <= k1 + k2; ++i)
            {
                pre[i] = 0;
                for (int j = 0; j <= _k1 + 1; ++j)
                {
                    pre[i] += (d[_k1][j] * nxt[i][j]) % mod;
                    pre[i] %= mod;
                }
            }
            ret[_k1][0] = power_sum(n, _k1);
            for (int _k2 = 1; _k1 + _k2 <= k1 + k2; ++_k2)
            {
                ret[_k1][_k2] = 0;
                for (int i = 0; i < _k2; ++i)
                {
                    ret[_k1][_k2] += ((ncr[_k2][i] * psum[i]) % mod) * ret[_k1][0];
                    ret[_k1][_k2] -= ncr[_k2][i] * pre[i];
                    ret[_k1][_k2] %= mod;
                }
            }
        }
    }
    return ret;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    prec();
    int t;
    cin >> t;
    while (t--)
    {
        ll k1, k2, a, b, c, n;
        cin >> n >> a >> b >> c >> k1 >> k2;
        auto ret = solve(k1, k2, a, b, c, n);
        cout << ret[k1][k2] << '\n';
    }
    return 0;
}
// https://asfjwd.github.io/2020-04-24-floor-sum-ap/
// https://loj.ac/problem/138

// Intersection of Arithmetic Progressions:

#include <bits/stdc++.h>
using namespace std;

using T = __int128;
using ll = long long;
// ax + by = __gcd(a, b)
// returns __gcd(a, b)
T extended_euclid(T a, T b, T &x, T &y)
{
    T xx = y = 0;
    T yy = x = 1;
    while (b)
    {
        T q = a / b;
        T t = b;
        b = a % b;
        a = t;
        t = xx;
        xx = x - q * xx;
        x = t;
        t = yy;
        yy = y - q * yy;
        y = t;
    }
    return a;
}
// finds x such that x % m1 = a1, x % m2 = a2. m1 and m2 may not be coprime
// here, x is unique modulo m = lcm(m1, m2). returns (x, m). on failure, m = -1.
pair<T, T> CRT(T a1, T m1, T a2, T m2)
{
    T p, q;
    T g = extended_euclid(m1, m2, p, q);
    if (a1 % g != a2 % g)
        return make_pair(0, -1);
    T m = m1 / g * m2;
    p = (p % m + m) % m;
    q = (q % m + m) % m;
    return make_pair((p * a2 % m * (m1 / g) % m + q * a1 % m * (m2 / g) % m) % m, m);
}
// intersecting AP of two APs: (a1 + d1x) and (a2 + d2x)
pair<ll, ll> intersect(ll a1, ll d1, ll a2, ll d2)
{
    auto x = CRT(a1 % d1, d1, a2 % d2, d2);
    ll a = x.first, d = x.second;
    if (d == -1)
        return {0, 0}; // empty
    ll st = max(a1, a2);
    a = a < st ? a + ((st - a + d - 1) / d) : a; // while (a < st) a += d;
    return {a, d};
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    auto x = intersect(7, 9, 13, 12);
    cout << x.first << ' ' << x.second << '\n';
    return 0;
}

// Sum of Arithmetic Progression Modular and Divided:

#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;
/*
Sums of arithmetic progressions.
mod_sum(n, a, d, m) = \sum_{i = 0}^{n - 1}{(a + d * i) % m}.
floor_sum(n, a, d, m) = \sum_{i = 0}^{n - 1}{(a + d * i) / m}.
log(m), with a large constant.
*/
long long sumsq(long long n) {
    return n / 2 * ((n - 1) | 1);
}
long long floor_sum(long long a, long long d, long long m, long long n) {
    long long res = d / m * sumsq(n) + a / m * n;
    d %= m; a %= m;
    if (!d) return res;
    long long to = (n * d + a) / m;
    return res + (n - 1) * to - floor_sum(m - 1 - a, m, d, to);
}
long long mod_sum(long long a, long long d, long long m, long long n) {
    a = ((a % m) + m) % m;
    d = ((d % m) + m) % m;
    return n * a + d * sumsq(n) - m * floor_sum(a, d, m, n);
}
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t; cin >> t;
    while (t--) {
    	int n, m, a, b; cin >> n >> m >> a >> b;
    	cout << floor_sum(b, a, m, n) << '\n';
    }
    return 0;
}

// Sum of Arithmetic Progression Powers Divided:

#include<bits/stdc++.h>
using namespace std;

const int N = 25, mod = 1e9 + 7;

long long power(long long n, long long k) {
    int ans = 1 % mod;
    n %= mod;
    if (n < 0) n += mod;
    while (k) {
        if (k & 1) ans = (long long) ans * n % mod;
        n = (long long) n * n % mod;
        k >>= 1;
    }
    return ans;
}
template <const int32_t MOD>
struct modint {
    int32_t value;
    modint() = default;
    modint(int32_t value_) : value(value_) {}
    inline modint<MOD> operator + (modint<MOD> other) const { int32_t c = this->value + other.value; return modint<MOD>(c >= MOD ? c - MOD : c); }
    inline modint<MOD> operator - (modint<MOD> other) const { int32_t c = this->value - other.value; return modint<MOD>(c <    0 ? c + MOD : c); }
    inline modint<MOD> operator * (modint<MOD> other) const { int32_t c = (int64_t)this->value * other.value % MOD; return modint<MOD>(c < 0 ? c + MOD : c); }
    inline modint<MOD> & operator += (modint<MOD> other) { this->value += other.value; if (this->value >= MOD) this->value -= MOD; return *this; }
    inline modint<MOD> & operator -= (modint<MOD> other) { this->value -= other.value; if (this->value <    0) this->value += MOD; return *this; }
    inline modint<MOD> & operator *= (modint<MOD> other) { this->value = (int64_t)this->value * other.value % MOD; if (this->value < 0) this->value += MOD; return *this; }
    inline modint<MOD> operator - () const { return modint<MOD>(this->value ? MOD - this->value : 0); }
    modint<MOD> pow(uint64_t k) const { modint<MOD> x = *this, y = 1; for (; k; k >>= 1) { if (k & 1) y *= x; x *= x; } return y; }
    modint<MOD> inv() const { return pow(MOD - 2); }  // MOD must be a prime
    inline modint<MOD> operator /  (modint<MOD> other) const { return *this *  other.inv(); }
    inline modint<MOD> operator /= (modint<MOD> other)       { return *this *= other.inv(); }
    inline bool operator == (modint<MOD> other) const { return value == other.value; }
    inline bool operator != (modint<MOD> other) const { return value != other.value; }
    inline bool operator < (modint<MOD> other) const { return value < other.value; }
    inline bool operator > (modint<MOD> other) const { return value > other.value; }
};
template <int32_t MOD> modint<MOD> operator * (int64_t value, modint<MOD> n) { return modint<MOD>(value) * n; }
template <int32_t MOD> modint<MOD> operator * (int32_t value, modint<MOD> n) { return modint<MOD>(value % MOD) * n; }
template <int32_t MOD> istream & operator >> (istream & in, modint<MOD> &n) { return in >> n.value; }
template <int32_t MOD> ostream & operator << (ostream & out, modint<MOD> n) { return out << n.value; }

using mint = modint<mod>;

//generates the polynomial explicitely
vector<mint> Lagrange(vector<mint> &x, vector<mint> &y) {
    int n = x.size();
    vector<mint> ans(n, 0);
    vector<mint> all(n + 1, 0); //(x - x0) * (x - x1) * ... * (x - x(n-1))
    all[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = n; j >= 0; j--) {
            all[j] *= -x[i];
            if (j) all[j] += all[j - 1];
        }
    }
    for (int i = 0; i < n; i++) {
        vector <mint> up(n); //all / (x - xi)
        mint rem = all[n];
        for (int j = n - 1; j >= 0; --j) {
            up[j] = rem;
            rem = all[j] + rem * x[i];
        }
        mint down = 1;
        for (int j = 0; j < n; j++) if (i != j) down *= x[i] - x[j];
        up.resize(n);
        down = down.inv() * y[i];
        for (int j = 0; j < n; j++) ans[j] += up[j] * down;
    }
    return ans;
}
long long ncr[N][N], d[N][N]; // N > k1 + k2
void prec() {
    for (int i = 0; i < N; i++) ncr[i][0]=1;
    for (int i = 1; i < N; i++) {
        for(int j = 1; j < N; j++) {
          ncr[i][j] = (ncr[i - 1][j - 1] + ncr[i - 1][j]) % mod;
        }
    }
  for (int k = 0; k < N; k++) {
    vector<mint> y, x;
      mint sum = 0; y.push_back(0); x.push_back(0);
      for (int i = 1; i <= k + 1; i++) {
        sum += mint(i).pow(k);
        y.push_back(sum); x.push_back(i);
      }
      auto p = Lagrange(x, y);
      assert(p.size() > k + 1);
      for (int i = 0; i <= k + 1; i++) d[k][i] = p[i].value;
  }
  d[0][0] = 1; //to satisfy 0^0 = 1
}
long long power_sum(long long n, int k) {
  assert(k >= 0);
  long long ans = 0;
    for (int i = 0; i <= k + 1; i++) {
      ans += d[k][i] * power(n, i) % mod;
      ans %= mod;
    }
    return ans;
}
// \sum{x=0}^{n}{x^k1 * ((ax + b)/c)^k2} //floor division
// 0^0 = 1
// it solves for all _k1, _k2 s.t. _k1 + _k2 <= k1 + k2
// (a * n + b) should fit in long long
// total complexity: O((k1 + k2)^3 * log(n) * log(mod)
vector<vector<long long>> solve(long long k1, long long k2, long long a, long long b, long long c, long long n) {
    if (n < 0) {
      vector<vector<long long>> ret(k1 + k2 + 1, vector<long long> (k1 + k2 + 1, 0));
      return ret;
    }
    if (!a) {
        vector<vector<long long>> ret(k1 + k2 + 1, vector<long long> (k1 + k2 + 1, 0));
        for (int _k1 = 0; _k1 <= k1 + k2; ++_k1) {
            ret[_k1][0] = power_sum(n, _k1);
            for (int _k2 = 1; _k1 + _k2 <= k1 + k2; ++_k2) {
                ret[_k1][_k2] = (ret[_k1][0] * power(b / c, _k2)) % mod;
            }
        }
        return ret;
    }

    vector<vector<long long>> ret(k1 + k2 + 1, vector<long long> (k1 + k2 + 1, 0));
    assert(c != 0);
    if (a >= c) {
        vector<vector<long long>> nxt = solve(k1, k2, a % c, b, c, n);
        for (int _k1 = 0; _k1 <= k1 + k2; ++_k1) {
            ret[_k1][0] = power_sum(n, _k1);
            for (int _k2 = 1; _k1 + _k2 <= k1 + k2; ++_k2) {
                ret[_k1][_k2] = 0;
                for (int y = 0; y <= _k2; ++y) {
                    ret[_k1][_k2] += ((ncr[_k2][y] * power(a / c, y) ) % mod) * nxt[_k1 + y][_k2 - y];
                    ret[_k1][_k2] %= mod;
                }
            }
        }
    }

    else if (b >= c) {
        vector<vector<long long>> nxt = solve(k1, k2, a, b % c, c, n);
        for (int _k1 = 0; _k1 <= k1 + k2; ++_k1) {
            ret[_k1][0] = power_sum(n, _k1);
            for (int _k2 = 1; _k1 + _k2 <= k1 + k2; ++_k2) {
                ret[_k1][_k2] = 0;
                for (int y = 0; y <= _k2; ++y) {
                    ret[_k1][_k2] += ((ncr[_k2][y] * power(b / c, y) ) % mod) * nxt[_k1][_k2 - y];
                    ret[_k1][_k2] %= mod;
                }
            }
        }
    }

    else {
        long long m = (a * n + b) / c;
        vector<vector<long long>> nxt = solve(k1, k2, c, c - b - 1, a, m - 1);
        vector<long long> psum(k1 + k2 + 1), pre(k1 + k2 + 1);
        for (int i = 0; i <= k1 + k2; ++i) psum[i] = power_sum(m - 1, i);
        for (int _k1 = 0; _k1 <= k1 + k2; ++_k1) {
            for (int i = 0; i <= k1 + k2; ++i) {
                pre[i] = 0;
                for (int j = 0; j <= _k1 + 1; ++j) {
                    pre[i] += (d[_k1][j] * nxt[i][j]) % mod;
                    pre[i] %= mod;
                }
            }
            ret[_k1][0] = power_sum(n, _k1);
            for (int _k2 = 1; _k1 + _k2 <= k1 + k2; ++_k2) {
                ret[_k1][_k2] = 0;
                for (int i = 0; i < _k2; ++i) {
                    ret[_k1][_k2] += ( (ncr[_k2][i] * psum[i]) % mod) * ret[_k1][0];
                    ret[_k1][_k2] -= ncr[_k2][i] * pre[i];
                    ret[_k1][_k2] %= mod;
                }
            }
        }
    }
    return ret;
}
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    prec();
    int t; cin >> t;
    while (t--) {
        long long k1, k2, a, b, c, n; cin >> n >> a >> b >> c >> k1 >> k2;
        auto ret = solve(k1, k2, a, b, c, n);
        cout << ret[k1][k2] << '\n';
    }
    return 0;
}
// https://asfjwd.github.io/2020-04-24-floor-sum-ap/
// https://loj.ac/problem/138