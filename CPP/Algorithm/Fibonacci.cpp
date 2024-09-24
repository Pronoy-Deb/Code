// Using Matrix Exponentiation to determine n-th fibonacci number:
// Complexity: O(logn)

void mul(auto a[3][3], auto b[3][3])
{
	long long mul[3][3];
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			mul[i][j] = 0;
			for (int k = 0; k < 3; k++)
				mul[i][j] += a[i][k] * b[k][j];
		}
	}
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
			a[i][j] = mul[i][j];
	}
}
long long power(auto F[3][3], auto n)
{
	long long M[3][3] = {{1, 1, 0}, {1, 0, 0}, {0, 1, 0}};
	if (n == 1)
		return F[0][0] + F[0][1];
	power(F, n >> 1);
	mul(F, F);
	if (n & 1)
		mul(F, M);
	return F[0][0] + F[0][1];
}
long long fib(auto n)
{
	long long F[3][3] = {{1, 1, 0}, {1, 0, 0}, {0, 1, 0}};
	if (!n)
		return 0;
	if (n <= 2)
		return 1;
	return power(F, n - 2);
}

// Operation:
cout << fib(n);

// Using DP: Complexity: O(n)
// Bottom Up Approach:

long long fib(auto n)
{
	long long dp[N];
	dp[0] = 0;
	dp[1] = 1;
	for (int i = 2; i <= n; ++i)
		dp[i] = dp[i - 1] + dp[i - 2];
	return dp[n];
}

// Top Down Approach:

long long dp[N];
long long fib(auto n)
{
	if (!n || n == 1)
		return n;
	if (dp[n] != -1)
		return dp[n];
	return dp[n] = fib(n - 1) + fib(n - 2);
}

// Operation:
memset(dp, -1, sizeof dp);
cout << fib(n);

// Fibonacci Number Faster:

#include <bits/stdc++.h>
using namespace std;

int fib(long long n, int mod)
{
	assert(n >= 0);
	if (n <= 1)
		return n;
	int a = 0, b = 1;
	long long i = 1ll << (63 - __builtin_clzll(n) - 1);
	for (; i; i >>= 1)
	{
		int na = (a * (long long)a + b * (long long)b) % mod;
		int nb = (2ll * a + b) * b % mod;
		a = na;
		b = nb;
		if (n & i)
		{
			int c = a + b;
			if (c >= mod)
				c -= mod;
			a = b;
			b = c;
		}
	}
	return b;
}
int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout << fib(10, 100) << '\n';
	return 0;
}

// LCM of Fibonacci Numbers:

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9, mod = 1e9 + 7;

int power(long long n, long long k)
{
	int ans = 1 % mod;
	n %= mod;
	if (n < 0)
		n += mod;
	while (k)
	{
		if (k & 1)
			ans = (long long)ans * n % mod;
		n = (long long)n * n % mod;
		k >>= 1;
	}
	return ans;
}
int fib(long long n)
{
	assert(n >= 0);
	if (n <= 1)
		return n;
	int a = 0;
	int b = 1;
	long long i = 1ll << (63 - __builtin_clzll(n) - 1);
	for (; i; i >>= 1)
	{
		int na = (a * (long long)a + b * (long long)b) % mod;
		int nb = (2ll * a + b) * b % mod;
		a = na;
		b = nb;
		if (n & i)
		{
			int c = a + b;
			if (c >= mod)
				c -= mod;
			a = b;
			b = c;
		}
	}
	return b;
}
map<vector<int>, int> dp;
/**
O((max number of divisors of a[i]) * n * log(max a[i])) but faster in practice
lcm(a1, a2, ... an)
= lcm(lcm(a1, ..., a[n-1]), an)
= lcm(a1, ..., a[n-1]) * an / gcd(lcm(a1, ..., a[n-1]), an)
= lcm(a1, ..., a[n-1]) * an / lcm(gcd(a1, an), ... gcd(a[n-1], an))
**/
int yo(vector<int> a)
{
	sort(a.rbegin(), a.rend());
	while (!a.empty() && a.back() <= 2)
		a.pop_back();
	a.resize(unique(a.begin(), a.end()) - a.begin());
	if (a.empty())
		return 1;
	if (a.size() == 1)
		return fib(a[0]);
	if (dp.count(a))
		return dp[a];
	vector<int> b(a.begin(), a.end() - 1);
	long long res = yo(b);
	for (int i = 0; i < b.size(); ++i)
		b[i] = __gcd(b[i], a.back());
	res = res * fib(a.back()) % mod * power(yo(b), mod - 2) % mod;
	dp[a] = res;
	return res;
}
int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &x : a)
		cin >> x;
	cout << yo(a) << '\n';
	return 0;
}
// https://www.hackerrank.com/contests/infinitum10/challenges/fibonacci-lcm/problem