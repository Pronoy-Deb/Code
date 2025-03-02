#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
int64_t power(int64_t n, int64_t k, const int64_t mod)
{
    int64_t ans = 1 % mod;
    n %= mod;
    while (k)
    {
        if (k & 1)
            ans = __int128(ans) * n % mod;
        n = __int128(n) * n % mod;
        k >>= 1;
    }
    return ans;
}
namespace PollardRho
{
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    const int P = 1e6 + 9;
    int64_t seq[P];
    int primes[P], spf[P];
    inline int64_t add_mod(int64_t x, int64_t y, int64_t m)
    {
        return (x += y) < m ? x : x - m;
    }
    inline int64_t mul_mod(int64_t x, int64_t y, int64_t m)
    {
        int64_t res = __int128(x) * y % m;
        return res;
        // int64_t res = x * y - (int64_t)((long double)x * y / m + 0.5) * m;
        // return res < 0 ? res + m : res;
    }
    inline int64_t pow_mod(int64_t x, int64_t n, int64_t m)
    {
        int64_t res = 1 % m;
        for (; n; n >>= 1)
        {
            if (n & 1)
                res = mul_mod(res, x, m);
            x = mul_mod(x, x, m);
        }
        return res;
    }
    // O(it * (logn)^3), it = number of rounds performed
    inline bool miller_rabin(int64_t n)
    {
        if (n <= 2 || (n & 1 ^ 1))
            return (n == 2);
        if (n < P)
            return spf[n] == n;
        int64_t c, d, s = 0, r = n - 1;
        for (; !(r & 1); r >>= 1, s++)
        {
        }
        // each iteration is a round
        for (int i = 0; primes[i] < n && primes[i] < 32; i++)
        {
            c = pow_mod(primes[i], r, n);
            for (int j = 0; j < s; j++)
            {
                d = mul_mod(c, c, n);
                if (d == 1 && c != 1 && c != (n - 1))
                    return false;
                c = d;
            }
            if (c != 1)
                return false;
        }
        return true;
    }
    void init()
    {
        int cnt = 0;
        for (int i = 2; i < P; i++)
        {
            if (!spf[i])
                primes[cnt++] = spf[i] = i;
            for (int j = 0, k; (k = i * primes[j]) < P; j++)
            {
                spf[k] = primes[j];
                if (spf[i] == spf[k])
                    break;
            }
        }
    }
    // returns O(n^(1/4))
    int64_t pollard_rho(int64_t n)
    {
        while (1)
        {
            int64_t x = rnd() % n, y = x, c = rnd() % n, u = 1, v, t = 0;
            int64_t *px = seq, *py = seq;
            while (1)
            {
                *py++ = y = add_mod(mul_mod(y, y, n), c, n);
                *py++ = y = add_mod(mul_mod(y, y, n), c, n);
                if ((x = *px++) == y)
                    break;
                v = u;
                u = mul_mod(u, abs(y - x), n);
                if (!u)
                    return __gcd(v, n);
                if (++t == 32)
                {
                    t = 0;
                    if ((u = __gcd(u, n)) > 1 && u < n)
                        return u;
                }
            }
            if (t && (u = __gcd(u, n)) > 1 && u < n)
                return u;
        }
    }
    vector<int64_t> factorize(int64_t n)
    {
        if (n == 1)
            return vector<int64_t>();
        if (miller_rabin(n))
            return vector<int64_t>{n};
        vector<int64_t> v, w;
        while (n > 1 && n < P)
        {
            v.push_back(spf[n]);
            n /= spf[n];
        }
        if (n >= P)
        {
            int64_t x = pollard_rho(n);
            v = factorize(x);
            w = factorize(n / x);
            v.insert(v.end(), w.begin(), w.end());
        }
        return v;
    }
}
int64_t fib(int64_t n, int64_t mod)
{
    if (n <= 1)
        return n;
    int64_t a = 0;
    int64_t b = 1;
    int64_t i = 1ll << (63 - __builtin_clzll(n) - 1);
    for (; i; i >>= 1)
    {
        int64_t na = (__int128(a) * a % mod + __int128(b) * b % mod) % mod;
        int64_t nb = __int128(2ll * a + b) * b % mod;
        a = na;
        b = nb;
        if (n & i)
        {
            int64_t c = a + b;
            if (c >= mod)
                c -= mod;
            a = b;
            b = c;
        }
    }
    return b;
}
int64_t pisano_period_prime(int64_t p)
{
    if (p == 2)
        return 3;
    if (p == 5)
        return 20;
    int64_t x = p % 5 == 1 or p % 5 == 4 ? p - 1 : 2 * p + 2;
    auto v = PollardRho::factorize(x);
    map<int64_t, int> mp;
    for (auto x : v)
    {
        mp[x]++;
    }
    vector<int64_t> d;
    d.push_back(1);
    for (auto [p, e] : mp)
    {
        int64_t cur = 1;
        int sz = d.size();
        for (int i = 0; i < e; i++)
        {
            cur *= p;
            for (int j = 0; j < sz; j++)
            {
                d.push_back(d[j] * cur);
            }
        }
    }
    sort(d.begin(), d.end());
    for (auto x : d)
    {
        if (fib(x, p) == 0 and fib(x + 1, p) == 1)
        {
            return x;
        }
    }
    assert(0);
    return -1;
}
// returns pisano period of n i.e. the period with which the sequence of Fibonacci numbers taken modulo n repeats
int64_t pisano_period(int64_t n)
{
    auto v = PollardRho::factorize(n);
    map<int64_t, int> mp;
    for (auto x : v)
    {
        mp[x]++;
    }
    int64_t ans = 1;
    for (auto [p, e] : mp)
    {
        int64_t cur = pisano_period_prime(p);
        for (int i = 1; i < e; i++)
        {
            cur *= p;
        }
        ans = ans / __gcd(ans, cur) * cur;
    }
    return ans;
}
// returns k s.t. fib(i * k) (for i >= 0) are the only fib numbers which are divisible by n
int64_t divisor_gap(int64_t n)
{
    int64_t k = pisano_period(n);
    if (k % 4 == 0 and fib(k / 4, n) == 0)
        return k / 4;
    if (k % 2 == 0 and fib(k / 2, n) == 0)
        return k / 2;
    return k;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    PollardRho::init();
    int t;
    cin >> t;
    while (t--)
    {
        int64_t a, b, n;
        cin >> a >> b >> n;
        int64_t k = divisor_gap(n);
        int64_t ans = power(a, b, mod) - power(a, b, k) % mod;
        ans = (ans + mod) % mod;
        ans = ans * power(k, mod - 2, mod);
        ans = (ans + 1) % mod;
        cout << ans << '\n';
    }
    return 0;
}
// https://www.spoj.com/problems/DIVFIBS2/