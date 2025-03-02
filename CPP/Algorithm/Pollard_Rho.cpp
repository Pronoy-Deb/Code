#include <bits/stdc++.h>
using namespace std;

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
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    PollardRho::init();
    int t;
    cin >> t;
    while (t--)
    {
        int64_t n;
        cin >> n;
        auto f = PollardRho::factorize(n);
        sort(f.begin(), f.end());
        cout << f.size() << ' ';
        for (auto x : f)
            cout << x << ' ';
        cout << '\n';
    }
    return 0;
}
// https://judge.yosupo.jp/problem/factorize