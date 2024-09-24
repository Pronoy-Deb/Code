// Complexity: O(n * logn)
// Use: Used to determine the minimum number x such that: x % val[i] = rem[i] for all i. Here, val[i] are pairwise coprime.
// Note: If val[i] are not pairwise coprime, then: x % lcm(val[i]) = rem[i] for all i

long long val[N], rem[N], n;
long long inv(auto a, auto m)
{
	if (m == 1)
		return 0;
	long long m0 = m, x0 = 0, x1 = 1;
	while (a > 1)
	{
		long long q = a / m, t = m;
		m = a % m, a = t;
		t = x0;
		x0 = x1 - q * x0;
		x1 = t;
	}
	return (x1 < 0 ? x1 + m0 : x1);
}
long long minv(auto pro)
{
	long long res = 0;
	for (int i = 0; i < n; ++i)
	{
		long long pp = pro / val[i];
		res += rem[i] * inv(pp, val[i]) * pp;
	}
	return res % pro;
}

// Operation:
cin >> n;
long long pro = 1;
for (i = 0; i < n; ++i)
{
	cin >> val[i];
	pro *= val[i];
}
for (i = 0; i < n; ++i)
	cin >> rem[i];
cout << minv(pro);

// OR,

#include <bits/stdc++.h>
using namespace std;

using T = __int128;
// ax + by = __gcd(a, b)
// returns __gcd(a, b)
T extended_euclid(T a, T b, T &x, T &y)
{
	T xx = y = 0;
	T yy = x = 1;
	while (b)
	{
		T q = a / b;
		T t = b;
		b = a % b;
		a = t;
		t = xx;
		xx = x - q * xx;
		x = t;
		t = yy;
		yy = y - q * yy;
		y = t;
	}
	return a;
}
// finds x such that x % m1 = a1, x % m2 = a2. m1 and m2 may not be coprime
// here, x is unique modulo m = lcm(m1, m2). returns (x, m). on failure, m = -1.
pair<T, T> CRT(T a1, T m1, T a2, T m2)
{
	T p, q;
	T g = extended_euclid(m1, m2, p, q);
	if (a1 % g != a2 % g)
		return make_pair(0, -1);
	T m = m1 / g * m2;
	p = (p % m + m) % m;
	q = (q % m + m) % m;
	return make_pair((p * a2 % m * (m1 / g) % m + q * a1 % m * (m2 / g) % m) % m, m);
}

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout << (int)CRT(1, 31, 0, 7).first << '\n';
	return 0;
}