// Using Matrix Exponentiation to determine n-th fibonacci number:
// Complexity: O(logn)

void mul(auto a[3][3], auto b[3][3]) {
	int64_t mul[3][3];
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			mul[i][j] = 0;
			for (int k = 0; k < 3; ++k) mul[i][j] += a[i][k] * b[k][j];
		}
	}
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) a[i][j] = mul[i][j];
	}
}
int64_t power(auto F[3][3], auto n) {
	int64_t M[3][3] = {{1, 1, 0}, {1, 0, 0}, {0, 1, 0}};
	if (n == 1) return F[0][0] + F[0][1];
	power(F, n >> 1); mul(F, F);
	if (n & 1) mul(F, M); return F[0][0] + F[0][1];
}
int64_t fib(auto n) {
	int64_t F[3][3] = {{1, 1, 0}, {1, 0, 0}, {0, 1, 0}};
	return (!n ? 0 : n <= 2 ? 1 : power(F, n - 2));
}

// Using DP: Complexity: O(n)
// Bottom Up Approach:

int64_t fib[N];
void pre() {
	fib[0] = 0; fib[1] = 1;
	for (int i = 2; i < N; ++i) fib[i] = fib[i - 1] + fib[i - 2];
}

// Top Down Approach:

int64_t dp[N];
int64_t fib(auto n) {
	if (!n || n == 1) return n;
	if (~dp[n]) return dp[n];
	return dp[n] = fib(n - 1) + fib(n - 2);
}

// Fibonacci Number Faster:

#include <bits/stdc++.h>
using namespace std;

int fib(int64_t n, int mod) {
	assert(n >= 0); if (n <= 1) return n;
	int a = 0, b = 1;
	int64_t i = 1ll << (63 - __builtin_clzll(n) - 1);
	for (; i; i >>= 1) {
		int na = (a * (int64_t)a + b * (int64_t)b) % mod;
		int nb = (2ll * a + b) * b % mod;
		a = na; b = nb;
		if (n & i) {
			int c = a + b;
			if (c >= mod) c -= mod;
			a = b; b = c;
		}
	}
	return b;
}
int32_t main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout << fib(10, 100) << '\n';
	return 0;
}

// LCM of Fibonacci Numbers:

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9, mod = 1e9 + 7;

int power(int64_t n, int64_t k) {
	int ans = 1 % mod;
	n %= mod;
	if (n < 0)
		n += mod;
	while (k) {
		if (k & 1)
			ans = (int64_t)ans * n % mod;
		n = (int64_t)n * n % mod;
		k >>= 1;
	}
	return ans;
}
int fib(int64_t n) {
	assert(n >= 0);
	if (n <= 1)
		return n;
	int a = 0;
	int b = 1;
	int64_t i = 1ll << (63 - __builtin_clzll(n) - 1);
	for (; i; i >>= 1) {
		int na = (a * (int64_t)a + b * (int64_t)b) % mod;
		int nb = (2ll * a + b) * b % mod;
		a = na;
		b = nb;
		if (n & i) {
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
int yo(vector<int> a) {
	sort(a.rbegin(), a.rend());
	while (!a.empty() && a.back() <= 2)
		a.pop_back();
	a.resize(unique(a.begin(), a.end()) - a.begin());
	if (a.empty())
		return 1;
	if (a.size() == 1)
		return fib(a[0]);
	if (dp.count(a))
		return fib[a];
	vector<int> b(a.begin(), a.end() - 1);
	int64_t res = yo(b);
	for (int i = 0; i < b.size(); ++i)
		b[i] = __gcd(b[i], a.back());
	res = res * fib(a.back()) % mod * power(yo(b), mod - 2) % mod;
	fib[a] = res;
	return res;
}
int32_t main() {
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