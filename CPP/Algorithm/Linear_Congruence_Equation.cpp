#include <bits/stdc++.h>
using namespace std;

int64_t extended_euclid(int64_t a, int64_t b, int64_t &x, int64_t &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int64_t x1, y1;
    int64_t d = extended_euclid(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}
int64_t inverse(int64_t a, int64_t m)
{
    int64_t x, y;
    int64_t g = extended_euclid(a, m, x, y);
    if (g != 1)
        return -1;
    return (x % m + m) % m;
}
// ax = b (mod m)
vector<int64_t> congruence_equation(int64_t a, int64_t b, int64_t m)
{
    vector<int64_t> ret;
    int64_t g = gcd(a, m), x;
    if (b % g != 0)
        return ret;
    a /= g, b /= g;
    x = inverse(a, m / g) * b;
    for (int k = 0; k < g; ++k)
    { // exactly g solutions
        ret.push_back((x + m / g * k) % m);
    }
    // minimum solution = (m / g - (m - x) % (m / g)) % (m / g)
    return ret;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    auto ret = congruence_equation(4, 0, 12);
    for (auto x : ret)
    {
        cout << x << ' ';
    }
    return 0;
}
// https://cp-algorithms.com/algebra/linear_congruence_equation.html