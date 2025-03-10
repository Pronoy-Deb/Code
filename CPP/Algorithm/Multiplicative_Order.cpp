#include <bits/stdc++.h>
using namespace std;

int64_t power(int64_t n, int64_t k, const int64_t mod)
{
    int64_t res = 1;
    while (k)
    {
        if (k & 1)
            res = __int128(res) * n % mod;
        n = __int128(n) * n % mod;
        k >>= 1;
    }
    return res;
}
int64_t totient(int64_t n)
{
    int64_t ans = n;
    for (int64_t i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            while (n % i == 0)
                n /= i;
            ans = ans / i * (i - 1);
        }
    }
    if (n > 1)
        ans = ans / n * (n - 1);
    return ans;
}
// returns the minimum positive k s.t. a^ k = 1 modulo mod. On failure, returns -1
// we just have to check the divisors of phi(mod) as candidates of k (Lagranges Theorem)
// which can still be optimized further. Check: https://cp-algorithms.com/algebra/primitive-root.html#toc-tgt-3
// it always exists if a and mod are coprime
// O((log(mod)^2)) + sqrt(mod) for calculating totient
// it can still be optimized. Check: https://brilliant.org/wiki/carmichaels-lambda-function/
int64_t multiplicative_order(int64_t a, int64_t mod)
{
    if (__gcd(a, mod) != 1)
        return -1;
    int64_t m = totient(mod), p = m;
    int64_t ans = 2e18;
    if (power(a, p, mod) == 1)
        ans = p;
    vector<int64_t> fac;
    for (int64_t i = 2; i * i <= m; i++)
    {
        if (m % i == 0)
        {
            while (m % i == 0)
                m /= i, fac.push_back(i);
        }
    }
    if (m > 1)
        fac.push_back(m);
    for (auto x : fac)
    {
        if (power(a, p / x, mod) == 1)
            p /= x, ans = p;
    }
    assert(ans != 2e18);
    return ans;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        int64_t x, m;
        cin >> x >> m;
        int64_t nw = x, st = x;
        int64_t mul = 1;
        while (x > 0)
        {
            x /= 10;
            mul *= 10;
        }
        m *= mul - 1;
        m /= __gcd(m, st);
        int64_t ans = multiplicative_order(mul, m);
        cout << ans << '\n';
    }
    return 0;
}
// https://toph.co/p/i-am-good