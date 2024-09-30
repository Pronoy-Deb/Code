// Note: Number of divisors of a number is equal to the product of (a + 1) where a is the power of each pri factor of that number.
// Complexity: O(sqrt(n))

auto div(long long n) {
    vector<long long> v;
    for (long long i = 1; i * i <= n; ++i) {
        if (!(n % i)) {
            v.push_back(i); long long tmp = n / i;
            if (i != tmp) v.push_back(tmp);
        }
    }
    return v;
}

// For number of divisors: // O(cbrt(n))
// N = 1e6  + 5 for n = 1e18

long long pri[N], spf[N]; bool sv[N];
void pre() {
    pri[0] = spf[2] = 2;
    for (int i = 4; i < N; i += 2) { sv[i] = true; spf[i] = 2; }
    for (long long i = 3, c = 0; i < N; i += 2) {
        if (!sv[i]) {
            pri[++c] = spf[i] = i;
            for (long long j = i * i; j < N; j += (i << 1)) {
                sv[j] = true; if (!spf[j]) spf[j] = i;
            }
        }
    }
}
long long modmul(long long x, long long y, long long m) {
    long long res = __int128(x) * y % m; return res;
    // long long res = x * y - (long long)((long double)x * y / m + 0.5) * m;
    // return res < 0 ? res + m : res;
}
long long bex(long long x, long long n, long long m) {
    long long res = 1 % m;
    while (n) {
        if (n & 1) res = modmul(res, x, m);
        x = modmul(x, x, m); n >>= 1;
    }
    return res;
}
bool ip(long long n) {
	if (n < 2 || (~n & 1) || !(n % 3)) return (n == 2 || n == 3);
    if (n < N) return spf[n] == n;
    long long s = 0, r = n - 1; while (~r & 1) { r >>= 1; ++s; }
    for (int i = 0; pri[i] < n && pri[i] < 32; ++i) {
        long long c = bex(pri[i], r, n);
        for (int j = 0; j < s; ++j) {
            long long d = modmul(c, c, n);
            if (d == 1 && c != 1 && c != (n - 1)) return false;
            c = d;
        }
        if (c != 1) return false;
    }
    return true;
}
long long sr(long long x) {
	long long p = sqrtl(0.5 + x); while (p * p < x) ++p;
    while (p * p > x) --p; return p;
}
long long div(long long n) {
    long long dv = 1, c = 0;
    for (int i = 0; pri[i] * pri[i] * pri[i] <= n; ++i, c = 0) {
        while (++c and !(n % pri[i]) and n > 1) n /= pri[i]; dv *= c;
    }
    return (ip(n) ? (dv << 1) : ip(sr(n)) ? dv * 3 : n != 1 ? (dv << 2) : dv);
}

// For summation of divisors:

long long dsum(long long n) {
    long long res = 1;
    for (long long i = 2; i * i <= n; ++i) {
        long long csum = 1, cterm = 1;
        while (!(n % i)) {
            n /= i; cterm *= i; csum += cterm;
        }
        res *= csum;
    }
    if (n > 1) res *= (1 + n); return res;
}

// With Divisors:

auto div(long long n) {
    pair<vector<long long>, long long> pr;
    for (long long i = 1; i * i <= n; ++i) {
        if (!(n % i)) {
            (pr.first).push_back(i); pr.second += i;
            long long tmp = n / i;
            if (i != tmp) {
                (pr.first).push_back(tmp); pr.second += tmp;
            }
        }
    }
    return pr;
}

// Sieve Approach:
// Complexity: O(n * log(n))

vector<long long> dv[N];
void div() {
    dv[1].push_back(1);
    for (long long i = 2; i < N; ++i) {
        dv[i].push_back(1);
        for (long long j = i * i; j < N; j += i) {
            dv[j].push_back(i); long long tmp = j / i;
            if (tmp != j) dv[j].push_back(tmp);
        }
        dv[i].push_back(i);
    }
}

// For summation of divisors:

vector<long long> dv[N]; long long sdv[N];
auto div() {
    dv[1].push_back(1); sdv[1] = 1;
    for (long long i = 2; i < N; ++i) {
        dv[i].push_back(1);
        for (long long j = i * i; j < N; j += i) {
            dv[j].push_back(i); sdv[j] += i; long long tmp = j / i;
            if (i != tmp) {
                dv[j].push_back(tmp); sdv[j] += tmp;
            }
        }
        dv[i].push_back(i); sdv[i] += (i + 1);
    }
}

// DP over Divisors:

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

#define pii pair<int, int>
#define pll pair<ll, ll>
#define eb emplace_back
#define ll long long
#define nl '\n'
#define deb(x) cerr << #x " = " << x << nl
#define in() ({ int a ; scanf("%d",&a); a; })

const int N = 3e3 + 9;
const int mod = 1e9 + 7;

vector<int> d[N];
int cnt[N], ans[N];
int32_t main()
{
    for (int i = 1; i < N; i++)
        for (int j = i; j < N; j += i)
            d[j].eb(i);
    int n = 72;
    vector<int> di = d[n];
    int s = di.size();
    map<int, int> id;
    for (int i = 0; i < s; i++)
        id[di[i]] = i;
    for (int i = 0; i < s; i++)
        ans[i] = rand(), cnt[i] = ans[i];
    for (int i = 0; i < s; i++)
        cout << ans[i] << ' ';
    cout << nl;
    vector<int> P = {2, 3};
    for (auto k : P)
    {
        for (int i = 0; i < s; i++)
        {
            if (di[i] % k == 0)
            {
                ans[id[di[i] / k]] -= ans[i];
                // assert(id[di[i]/x.F]<i);
            }
        }
    }
    for (int i = s - 1; i >= 0; i--)
    {
        for (int j = i + 1; j < s; j++)
            if (di[j] % di[i] == 0)
                cnt[i] -= cnt[j];
    }
    for (int i = 0; i < s; i++)
        cout << ans[i] << ' ';
    cout << nl;
    for (int i = 0; i < s; i++)
        cout << cnt[i] << ' ';
    cout << nl;
    return 0;
}

// K Divisors:

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
namespace pcf
{
// initialize once by calling init()
#define MAXN 10000010      // initial sieve limit
#define MAX_PRIMES 1000010 // max size of the pri array for sieve
#define PHI_N 100000
#define PHI_K 100

    int len = 0; // total number of primes generated by sieve
    int primes[MAX_PRIMES];
    int pref[MAXN];       // pref[i] --> number of primes <= i
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
                primes[len++] = i;
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
                dp[n][k] = dp[n][k - 1] - dp[n / primes[k - 1]][k - 1];
            }
        }
    }
    // returns the number of integers less or equal n which are
    // not divisible by any of the first k primes
    // recurrence --> yo(n, k) = yo(n, k-1) - yo(n / p_k , k-1)
    // for sum of primes yo(n, k) = yo(n, k-1) - p_k * yo(n / p_k , k-1)
    long long yo(long long n, int k)
    {
        if (n < PHI_N && k < PHI_K)
            return dp[n][k];
        if (k == 1)
            return ((++n) >> 1);
        if (primes[k - 1] >= n)
            return 1;
        return yo(n, k - 1) - yo(n / primes[k - 1], k - 1);
    }
    // complexity: n^(2/3).(log n^(1/3))
    long long Legendre(long long n)
    {
        if (n < MAXN)
            return pref[n];
        int lim = sqrt(n) + 1;
        int k = upper_bound(primes, primes + len, lim) - primes;
        return yo(n, k) + (k - 1);
    }
    // runs under 0.5s for n = 1e12
    long long Lehmer(long long n)
    {
        if (n < MAXN)
            return pref[n];
        long long w, res = 0;
        int b = sqrt(n), c = Lehmer(cbrt(n)), a = Lehmer(sqrt(b));
        b = Lehmer(b);
        res = yo(n, a) + ((1LL * (b + a - 2) * (b - a + 1)) >> 1);
        for (int i = a; i < b; i++)
        {
            w = n / primes[i];
            int lim = Lehmer(sqrt(w));
            res -= Lehmer(w);
            if (i <= c)
            {
                for (int j = i; j < lim; j++)
                {
                    res += j;
                    res -= Lehmer(w / primes[j]);
                }
            }
        }
        return res;
    }
}
using namespace pcf;
const ll inf = 1e12 + 9; // > max n
const int M = 2020;      // maximum number of divisors
const int C = 1010;      // 4th root of max n
const int L = 41;        // 2^L >= max n
ll pw[C][L];
int s[M];
ll power(ll n, int k)
{
    if (k >= L)
        return inf;
    if (n < C)
        return pw[n][k];
    if (k == 1)
        return n;
    if (k == 2)
        return n * n;
    if (k == 3)
        return n * n * n;
    return inf;
}
vector<int> d[M];
// returns the count of numbers <= n s.t. each has exactly k divisors and isn't divisible by the first 'last' primes
// pretty fast!
ll backtrack(ll n, int k, int last = 0)
{
    if (k >= M)
        return 0;
    if (n <= 0)
        return 0;
    if (k == 1)
        return 1;
    if (n == 1)
        return 0;
    if (k == 2)
        return max(0LL, Lehmer(n) - last);
    if (d[k].size() == 1)
    {
        if (d[k][0] - 1 >= L)
            return 0;
        if (power(primes[last], d[k][0] - 1) > n)
            return 0;
        int ans = last - 1, l = last, r = pow(n, 1.0 / (d[k][0] - 1)) + 1;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            ll p = power(primes[mid], d[k][0] - 1);
            if (p > n)
                r = mid - 1;
            else
                l = mid + 1, ans = mid;
        }
        return ans - last + 1;
    }
    ll ans = 0;
    for (auto x : d[k])
    {
        for (int i = last; i < len; i++)
        {
            ll p = power(primes[i], x - 1);
            if (p > n)
                break;
            if (k / x == 1)
            {
                ++ans;
                continue;
            }
            if (power(primes[i + 1], s[k / x]) > n / p)
                break;
            ans += backtrack(n / p, k / x, i + 1);
        }
    }
    return ans;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    init();
    for (int i = 2; i < M; i++)
    {
        for (int j = i; j < M; j += i)
        {
            d[j].push_back(i);
        }
        reverse(d[i].begin(), d[i].end());
        for (int j = 0; j < len; j++)
        {
            if (primes[j] > i)
                break;
            int cur = i;
            while (cur % primes[j] == 0)
            {
                cur /= primes[j];
                s[i] += primes[j] - 1;
            }
        }
    }
    for (int i = 2; i < C; i++)
    {
        pw[i][0] = 1;
        for (int j = 1; j < L; j++)
        {
            pw[i][j] = pw[i][j - 1] * i;
            if (pw[i][j] > inf)
                pw[i][j] = inf;
        }
    }
    int t, cs = 0;
    cin >> t;
    while (t--)
    {
        ll l, r, k;
        cin >> l >> r >> k;
        ll ans = backtrack(r, k);
        ans -= backtrack(l - 1, k);
        cout << "Case " << ++cs << ": " << ans << '\n';
    }
    return 0;
}
// https://algo.codemarshal.org/contests/mist-ncpc-2020/problems/E

// Smallest Number Having Exactly K Divisors:

#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 9, mod = 1e9 + 7;

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
int spf[N];
vector<int> primes;
void sieve()
{
    for (int i = 2; i < N; i++)
    {
        if (spf[i] == 0)
            spf[i] = i, primes.push_back(i);
        int sz = primes.size();
        for (int j = 0; j < sz && i * primes[j] < N && primes[j] <= spf[i]; j++)
        {
            spf[i * primes[j]] = primes[j];
        }
    }
}
double lgp[N];
vector<long long> v;
unordered_map<long long, pair<double, int>> dp[100];
pair<double, int> yo(int i, long long n)
{ // it solves for odd divisors
    if (n == 1)
    {
        return {0, 1};
    }
    if (dp[i].find(n) != dp[i].end())
    {
        return dp[i][n];
    }
    pair<double, int> ans = {1e50, 0};
    for (auto x : v)
    {
        if (x > n)
            break;
        if (n % x != 0)
            continue;
        auto z = lgp[i + 1] * (x - 1); // i for all divisors
        if (z > ans.first)
        {
            break;
        }
        auto cur = yo(i + 1, n / x);
        cur.first += z;
        cur.second = 1LL * cur.second * power(primes[i + 1], x - 1) % mod; // i for all divisors
        ans = min(ans, cur);
    }
    return dp[i][n] = ans;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    sieve();
    for (int i = 0; i < 100; i++)
    {
        lgp[i] = log(primes[i]);
    }
    int t, cs = 0;
    cin >> t;
    while (t--)
    {
        long long n;
        cin >> n;
        ++n;
        if (n == 1)
        {
            cout << "Case " << ++cs << ": " << 1 << '\n';
            continue;
        }
        v.clear();
        for (int i = 1; 1LL * i * i <= n; i++)
        {
            if (n % i == 0)
            {
                if (i > 1)
                    v.push_back(i);
                if (i != n / i)
                {
                    v.push_back(n / i);
                }
            }
        }
        sort(v.begin(), v.end());
        cout << "Case " << ++cs << ": " << yo(0, n).second << '\n';
    }
    return 0;
}
// https://lightoj.com/problem/politeness

// Sum of The Number of Divisors in cbrt(n):

#include <bits/stdc++.h>
using namespace std;

using uint32 = unsigned int;
using uint64 = unsigned long long;
using uint128 = __uint128_t;

// credit: zimpha
// compute \sum_{i=1}^{n} sigma0(i) in ~O(n^{1/3}) time.
// it is also equal to \sum_{i=1}^{n} floor(n / i)
// takes ~100 ms for n = 1e18
uint128 sum_sigma0(uint64 n)
{
    auto out = [n](uint64 x, uint32 y)
    {
        return x * y > n;
    };
    auto cut = [n](uint64 x, uint32 dx, uint32 dy)
    {
        return uint128(x) * x * dy >= uint128(n) * dx;
    };
    const uint64 sn = sqrtl(n);
    const uint64 cn = pow(n, 0.34); // cbrtl(n);
    uint64 x = n / sn;
    uint32 y = n / x + 1;
    uint128 ret = 0;
    stack<pair<uint32, uint32>> st;
    st.emplace(1, 0);
    st.emplace(1, 1);
    while (true)
    {
        uint32 lx, ly;
        tie(lx, ly) = st.top();
        st.pop();
        while (out(x + lx, y - ly))
        {
            ret += x * ly + uint64(ly + 1) * (lx - 1) / 2;
            x += lx, y -= ly;
        }
        if (y <= cn)
            break;
        uint32 rx = lx, ry = ly;
        while (true)
        {
            tie(lx, ly) = st.top();
            if (out(x + lx, y - ly))
                break;
            rx = lx, ry = ly;
            st.pop();
        }
        while (true)
        {
            uint32 mx = lx + rx, my = ly + ry;
            if (out(x + mx, y - my))
            {
                st.emplace(lx = mx, ly = my);
            }
            else
            {
                if (cut(x + mx, lx, ly))
                    break;
                rx = mx, ry = my;
            }
        }
    }
    for (--y; y > 0; --y)
        ret += n / y;
    return ret * 2 - sn * sn;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        long long n;
        cin >> n;
        auto ans = sum_sigma0(n);
        string s = "";
        while (ans > 0)
        {
            s += char('0' + ans % 10);
            ans /= 10;
        }
        reverse(s.begin(), s.end());
        cout << s << '\n';
    }
    return 0;
}
// https://www.spoj.com/problems/DIVCNT1/en/