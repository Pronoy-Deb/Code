// Square Root using binary search:

long double sr(long long n) {
    long double lo = 1, hi = n;
    while (hi - lo > 1e-6) {
        long double mid = (lo + hi) / 2;
        if (mid * mid < n) lo = mid;
        else hi = mid;
    }
    return lo;
}

// OR,

long long sr(long long x) {
	long long p = sqrtl(0.5 + x); while (p * p < x) ++p;
	while (p * p > x) --p; return p;
}

// Cube Root using binary search:

long double cr(long long n) {
    long double lo = 1, hi = n;
    while (hi - lo > 1e-6) {
        long double mid = (lo + hi) / 2;
        if (mid * mid * mid < n) lo = mid;
        else hi = mid;
    }
    return lo;
}

// OR,

long long cr(long long x) {
	long long p = cbrtl(0.5 + x); while (p * p * p < x) ++p;
	while (p * p * p > x) --p; return p;
}

// N-th root of a number with 5 decimal accuracy
// Complexity: O(n*log(num*(10^d))); for n-th root of number num with d decimal accuracy
// Built-in: powl(num, 1.0/n)

auto nr(long long num, int n) {
    long double lo = 1, hi = num;
    while (hi - lo > 1e-6) {
        long double mid = (hi + lo) / 2, pro = 1;
        for (int i = 0; i < n; ++i) pro *= mid;
        if (pro < num) lo = mid;
        else hi = mid;
    }
    return lo;
}

// Discrete Root:

#include <bits/stdc++.h>
using namespace std;

int power(int a, int b, int m) {
    int res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = 1LL * res * a % m;
        a = 1LL * a * a % m;
        b >>= 1;
    }
    return res;
}
// p is prime
int primitive_root(int p)
{
    vector<int> fact;
    int phi = p - 1, n = phi;
    for (int i = 2; i * i <= n; ++i)
    {
        if (n % i == 0)
        {
            fact.push_back(i);
            while (n % i == 0)
                n /= i;
        }
    }
    if (n > 1)
        fact.push_back(n);
    for (int res = 2; res <= p; ++res)
    { // this loop will run at most (logp ^ 6) times i.e. until a root is found
        bool ok = true;
        // check if this is a primitive root modulo p
        for (size_t i = 0; i < fact.size() && ok; ++i)
            ok &= power(res, phi / fact[i], p) != 1;
        if (ok)
            return res;
    }
    return -1;
}
// returns any or all numbers x such that x ^ k = a (mod m)
// existence: a = 0 is trivial, and if a > 0: a ^ (phi(m) / gcd(k, phi(m))) == 1 mod m
// if solution exists, then number of solutions = gcd(k, phi(m)).
// here m is prime, but it will work for any integer which has a primitive root
int discrete_root(int k, int a, int m)
{
    if (a == 0)
        return 1;
    int g = primitive_root(m);
    int phi = m - 1; // m is prime
    // run baby step-giant step
    int sq = (int)sqrt(m + .0) + 1;
    vector<pair<int, int>> dec(sq);
    for (int i = 1; i <= sq; ++i)
        dec[i - 1] = make_pair(power(g, 1LL * i * sq % phi * k % phi, m), i);
    sort(dec.begin(), dec.end());
    int any_ans = -1;
    for (int i = 0; i < sq; ++i)
    {
        int my = power(g, 1LL * i * k % phi, m) * 1LL * a % m;
        auto it = lower_bound(dec.begin(), dec.end(), make_pair(my, 0));
        if (it != dec.end() && it->first == my)
        {
            any_ans = it->second * sq - i;
            break;
        }
    }
    if (any_ans == -1)
        return -1; // no solution
    // for any answer
    int delta = (m - 1) / __gcd(k, m - 1);
    return power(g, any_ans % delta, m);

    // // for all possible answers
    // int delta = (m - 1) / __gcd(k, m - 1);
    // vector<int> ans;
    // for (int cur = any_ans % delta; cur < m-1; cur += delta) ans.push_back(power(g, cur, m));
    // sort(ans.begin(), ans.end());
    // // assert(ans.size() == __gcd(k, m - 1))
    // return ans;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    return 0;
}

// Discrete Root Faster:

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
ll power(ll a, ll n, ll p)
{
    ll r = 1;
    for (; n > 0; n >>= 1, a = a * a % p)
        if (n % 2 == 1)
            r = r * a % p;
    return r;
}
int cnt(ll a, ll base, ll p)
{
    int ret = 0;
    while (a != 1)
    {
        a = power(a, base, p);
        ++ret;
    }
    return ret;
}
ll inverse(ll a, ll p)
{
    a %= p;
    ll u = 1, v = 0;
    ll b = p;
    while (b > 0)
    {
        ll q = a / b;
        a %= b;
        u -= v * q % p;
        u = (u % p + p) % p;
        u ^= v;
        v ^= u;
        u ^= v;
        a ^= b;
        b ^= a;
        a ^= b;
    }
    return u < 0 ? u + p : u;
}
ll gcd(ll a, ll b)
{
    return a == 0 ? b : gcd(b % a, a);
}
ll peth_root(ll a, ll p, int e, ll mod)
{
    ll q = mod - 1;
    int s = 0;
    while (q % p == 0)
    {
        q /= p;
        ++s;
    }
    ll pe = power(p, e, mod);
    ll ans = power(a, ((pe - 1) * inverse(q, pe) % pe * q + 1) / pe, mod);
    ll c = 2;
    while (power(c, (mod - 1) / p, mod) == 1)
        ++c;
    c = power(c, q, mod);
    map<ll, int> mp;
    ll add = 1;
    int v = (int)sqrt((double)(s - e) * p) + 1;
    ll mul = power(c, v * power(p, s - 1, mod - 1) % (mod - 1), mod);
    for (int i = 0; i <= v; ++i)
    {
        mp[add] = i;
        add = add * mul % mod;
    }
    mul = inverse(power(c, power(p, s - 1, mod - 1), mod), mod);
    for (int i = e; i < s; ++i)
    {
        ll err = inverse(power(ans, pe, mod), mod) * a % mod;
        ll target = power(err, power(p, s - 1 - i, mod - 1), mod);
        for (int j = 0; j <= v; ++j)
        {
            if (mp.find(target) != mp.end())
            {
                int x = mp[target];
                ans = ans * power(c, (j + v * x) * power(p, i - e, mod - 1) % (mod - 1), mod) % mod;
                break;
            }
            target = target * mul % mod;
            assert(j != v);
        }
    }
    return ans;
}
// returns any x such that x ^ k  =  a (mod p),  p is a prime
// 0^0 = 1 mod p
// Complexity: O(p ^ (1 / 4))
ll discrete_root(ll k, ll a, ll p)
{
    if (k > 0 && a == 0)
        return 0;
    k %= p - 1;
    ll g = gcd(k, p - 1);
    if (power(a, (p - 1) / g, p) != 1)
        return -1; // checking existence
    a = power(a, inverse(k / g, (p - 1) / g), p);
    for (ll div = 2; div * div <= g; ++div)
    {
        int sz = 0;
        while (g % div == 0)
            g /= div, ++sz;
        if (sz > 0)
        {
            ll b = peth_root(a, div, sz, p);
            a = b;
        }
    }
    if (g > 1)
        a = peth_root(a, g, 1, p);
    return a;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        ll k, a, p;
        cin >> k >> a >> p;
        cout << discrete_root(k, a, p) << '\n';
    }
}
// https://judge.yosupo.jp/problem/kth_root_mod

// Primitive Root:

#include <bits/stdc++.h>
using namespace std;

int totient(int n)
{
    int ans = n;
    for (int i = 2; i * i <= n; i++)
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
int power(int a, int b, int m)
{
    int res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = 1LL * res * a % m;
        a = 1LL * a * a % m;
        b >>= 1;
    }
    return res;
}
// g is a primitive root modulo p if and only if for any integer a such that
// gcd(a, p) = 1, there exists an integer k such that: g^k = a(mod p).
// primitive root modulo n exists iff n = 1, 2, 4 or n = p^k or 2 * p^k for some odd prime p
int primitive_root(int p)
{
    // first check if primitive root exists or not. I have omitted this part here
    vector<int> fact;
    int phi = totient(p), n = phi;
    for (int i = 2; i * i <= n; ++i)
    {
        if (n % i == 0)
        {
            fact.push_back(i);
            while (n % i == 0)
                n /= i;
        }
    }
    if (n > 1)
        fact.push_back(n);
    for (int res = 2; res <= p; ++res)
    { // this loop will run at most (logp ^ 6) times i.e. until a root is found
        bool ok = true;
        // check if this is a primitive root modulo p
        for (size_t i = 0; i < fact.size() && ok; ++i)
            ok &= power(res, phi / fact[i], p) != 1;
        if (ok)
            return res;
    }
    return -1;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << primitive_root(200003) << '\n';
    return 0;
}
// https://cp-algorithms.com/algebra/primitive-root.html