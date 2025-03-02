// Complexity: O(n * log(n))
// Coprime: gcd(a, b) == 1
// Note: phi[n] tells how many numbers from 1 to n-1 are coprime with n.

// Number of co-primes of a number n:
// n * (1 - 1/a) * (1 - 1/b) * (1 - 1/c) * .......; a,b,c = Prime factors of n
// Ex: Prime factors of 5 -> 5 & 6 -> 2, 3

int64_t phi[N]; bitset<N> sv;
void etf() {
    for (int i = 2; i < N; i += 2) phi[i] = (i >> 1);
    for (int i = 3; i < N; i += 2) {
        if (!sv[i]) {
            for (int j = i; j < N; j += i) {
                sv[j] = true; phi[j] = ((phi[j] ? phi[j] : j) * (i - 1)) / i;
            }
        }
    }
}

// OR,

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9;
int phi[N];
void totient()
{
    for (int i = 1; i < N; i++)
        phi[i] = i;
    for (int i = 2; i < N; i++)
    {
        if (phi[i] == i)
        {
            for (int j = i; j < N; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    return 0;
}

// Phi Field:

struct field
{ // a . 1 + b . sqrt(5)
    mint a, b;
    field(mint a = 0, mint b = 0) : a(a), b(b) {}
    bool operator==(const field &oth) const
    {
        return a == oth.a and b == oth.b;
    }
    field operator+(const field &oth) const
    {
        return field(a + oth.a, b + oth.b);
    }
    field operator-(const field &oth) const
    {
        return field(a - oth.a, b - oth.b);
    }
    field operator*(const field &oth) const
    {
        return field(a * oth.a + 5 * b * oth.b, a * oth.b + b * oth.a);
    }
    field operator*(const mint &oth) const
    {
        return field(a * oth, b * oth);
    }
    field inv()
    {
        mint d = (a * a - b * b * 5).inv();
        return field(a * d, -b * d);
    }
    field operator/(field oth)
    {
        field f = oth.inv();
        return (*this) * f;
    }
    field operator/(const mint &oth) const
    {
        mint p = oth.inv();
        return field(a * p, b * p);
    }
    field pow(ll k)
    {
        field ans(1, 0), cur = *this;
        while (k)
        {
            if (k & 1)
                ans = ans * cur;
            cur = cur * cur;
            k >>= 1;
        }
        return ans;
    }
} phi((mod + 1) / 2, (mod + 1) / 2);

mint fib(ll n)
{
    field ans = phi.pow(n) - (field(1, 0) - phi).pow(n);
    ans = ans / field(0, 1);
    assert(ans.b == 0);
    return ans.a;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 0; i <= 10; i++)
    {
        cout << fib(i) << '\n';
    }
    return 0;
}