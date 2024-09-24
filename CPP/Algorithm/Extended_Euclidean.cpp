// Complexity: O(log(n))
// Use: Solves the equation: ax + by = gcd(a, b) and determines gcd(a, b), x and y
// Note: The equation ax + by = gcd(a, b) has a solution if and only if gcd(a, b) divides c (c is the gcd of a and b) and the equation is known as linear diophantine equation

long long ee(auto a, auto b, auto &x, auto &y)
{
	if (!a)
	{
		x = 0;
		y = 1;
		return b;
	}
	long long x1, y1, gcd = ee(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return gcd;
}

// Operation:
long long a, b, x, y;
cin >> a >> b;
cout << ee(a, b, x, y) << x << y;

// OR,

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
ll extended_euclid(ll a, ll b, ll &x, ll &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	ll x1, y1;
	ll d = extended_euclid(b, a % b, x1, y1);
	x = y1;
	y = x1 - y1 * (a / b);
	return d;
}
ll inverse(ll a, ll m)
{
	ll x, y;
	ll g = extended_euclid(a, m, x, y);
	if (g != 1)
		return -1;
	return (x % m + m) % m;
}
int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	ll x = 100, m = 37;
	cout << inverse(x, m) << '\n';
	return 0;
}