// Complexity: O(log(n))
// Use: Solves the equation: ax + by = gcd(a, b) and determines gcd(a, b), x and y
// Note: The equation ax + by = gcd(a, b) has a solution if and only if gcd(a, b) divides c (c is the gcd of a and b) and the equation is known as linear diophantine equation

int64_t ee(int64_t a, int64_t b, auto &x, auto &y) {
	if (!a) { x = 0; y = 1; return b; }
	int64_t x1, y1, gcd = ee(b % a, a, x1, y1);
	x = y1 - (b / a) * x1; y = x1; return gcd;
}
int64_t inv(int64_t a, int64_t m) {
	int64_t x, y, g = ee(a, m, x, y);
	if (g != 1) return -1; return (x % m + m) % m;
}

// Operation:
int64_t a, b, x, y;
cin >> a >> b;
cout << ee(a, b, x, y) << x << y;

// OR,

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
int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int64_t x = 100, m = 37;
	cout << inverse(x, m) << '\n';
	return 0;
}