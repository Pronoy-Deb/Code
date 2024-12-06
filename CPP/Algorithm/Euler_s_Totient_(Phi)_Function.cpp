// Complexity: O(n * log(n))
// Coprime: gcd(a, b) == 1
// Note: phi[n] tells how many numbers from 1 to n-1 are coprime with n.

// Number of co-primes of a number n:
// n * (1 - 1/a) * (1 - 1/b) * (1 - 1/c) * .......; a,b,c = Prime factors of n
// Ex: Prime factors of 5 -> 5 & 6 -> 2, 3

long long phi[N]; bitset<N> sv;
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

#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
using ll = long long;

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