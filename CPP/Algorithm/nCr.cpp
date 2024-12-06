// Formula: 1. nCr = n! / (r! * (n-r)!)
// 2. nCr + (n+1)Cr + (n+2)Cr + ... + (n+m)Cr = (n+m+1)C(r+1)
// 3. nC0 + nC1 + nC2 + ... + nCn = 2^n
// Complexity: O(r)

long long ncr(long long n, long long r) {
	if (r > n) return 0; if (!r || n == r) return 1;
	if (r == 1) return n; long double ans = 1;
	for (int i = 1; i <= r; ++i) ans *= (n - r + i) / i;
	return (long long)(ans + 0.01);
}

// OR,

long long ncr(long long n, long long r) {
	if (r > n) return 0; if (!r || n == r) return 1; if (r == 1) return n;
	long double res = 0;
	for (int i = 0; i < r; ++i) {
		res += log(n - i) - log(i + 1);
	}
	return (long long)round(exp(res));
}

// Iterative Approach:
// Complexity: O(n)

long long ncr(long long n, long long r) {
	if (r > n) return 0; if (!r || n == r) return 1; if (r == 1) return n;
	long long mx = max(r, n - r), mn = n - mx, x = 1, y = 1;
	for (int i = mx + 1; i <= n; ++i) x *= i;
	for (int i = 2; i <= mn; ++i) y *= i;
	return x / y;
}

// Recursive Approach:
// Complexity: O(n^2)

long long dp[N][N];
long long ncr(long long n, long long r) {
	if (r > n) return 0; if (!r || n == r) return 1; if (r == 1) return n;
	if (dp[n][r] != -1) return dp[n][r];
	return dp[n][r] = (ncr(n - 1, r - 1) + ncr(n - 1, r)) % M;
}

// Modular Multiplicative Inverse(MMI) Appraoch:
// Complexity: O(n)

long long fac[N];
void pre() {
	fac[0] = fac[1] = 1;
	for (int i = 2; i < N; ++i) fac[i] = (fac[i - 1] * i) % M;
}
long long mmi(long long base) {
	long long ans = 1, pow = M - 2;
	while (pow) {
		if (pow & 1) ans = (ans * base) % M;
		base = (base * base) % M; pow >>= 1;
	}
	return ans;
}
long long ncr(long long n, long long r) {
	if (r > n) return 0; if (!r || n == r) return 1; if (r == 1) return n;
	return (fac[n] * mmi((fac[r] * fac[n - r]) % M)) % M;
}

// OR,

long long mmul(long long a, long long b) {
	a %= M; long long res = 0;
	while (b) {
		if (b & 1) res = (res + a) % M;
		a = (a << 1) % M; b >>= 1;
	}
	return res;
}
long long exgcd(long long a, long long b, long long *x, long long *y) {
	if (!a) {
		*x = 0, *y = 1;
		return b;
	}
	long long x1, y1, gcd = exgcd(b % a, a, &x1, &y1);
	*x = y1 - (b / a) * x1;
	*y = x1;
	return gcd;
}
long long modinv(long long b) {
	long long x, y, g = exgcd(b, M, &x, &y);
	if (g != 1)
		return -1;
	return (x % M + M) % M;
}
long long mdv(long long a, long long b) {
	a %= M;
	long long inv = modinv(b);
	if (inv == -1)
		return 0;
	return (inv * a) % M;
}
long long ncr(long long n, long long r) {
	if (r > n) return 0; if (!r || n == r) return 1; if (r == 1) return n;
	if (r > n - r) r = n - r;
	long long x = 1;
	for (int i = 1; i <= r; ++i) x = mdv(mmul(x, (n + 1 - i)), i);
	return x;
}

// Pre-calculation of nCr:
// Complexity: O(N)

long long fac[N], inv[N], finv[N];
void pre() {
	fac[0] = fac[1] = inv[0] = inv[1] = finv[0] = finv[1] = 1;
	for (int i = 2; i < N; ++i) {
		fac[i] = (fac[i - 1] * i) % M;
		inv[i] = inv[M % i] * (M - M / i) % M;
		finv[i] = (inv[i] * finv[i - 1]) % M;
	}
}
long long ncr(long long n, long long r) {
	if (r > n) return 0; if (!r || n == r) return 1; if (r == 1) return n;
	return ((fac[n] * finv[r]) % M * finv[n - r]) % M;
}

// OR, Complexity: O(n ^ 2)

long long ncr[N][N];
void pre() {
	ncr[0][0] = 1;
	for (int i = 1; i < N; ++i) {
		ncr[i][0] = 1;
		for (int j = 1; j <= i; ++j)
			ncr[i][j] = (ncr[i - 1][j] + ncr[i - 1][j - 1]) % M;
	}
}

// Prefix Sum Queries of nCr:

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9, B = 330, mod = 1e9 + 7;
template <const int64_t MOD>
struct modint {
	int64_t val; modint() = default; modint(int64_t value) : val(value % MOD) { if (val < 0) val += MOD; }
	inline modint<MOD> operator+(modint<MOD> other) const { int64_t c = this->val + other.val; return modint<MOD>(c >= MOD ? c - MOD : c); }
	inline modint<MOD> operator-(modint<MOD> other) const { int64_t c = this->val - other.val; return modint<MOD>(c < 0 ? c + MOD : c); }
	inline modint<MOD> operator*(modint<MOD> other) const { int64_t c = (__int128_t)this->val * other.val % MOD; return modint<MOD>(c < 0 ? c + MOD : c); }
	inline modint<MOD> &operator+=(modint<MOD> other) { this->val += other.val; if (this->val >= MOD) this->val -= MOD; return *this; }
	inline modint<MOD> &operator-=(modint<MOD> other) { this->val -= other.val; if (this->val < 0) this->val += MOD; return *this; }
	inline modint<MOD> &operator*=(modint<MOD> other) { this->val = (__int128_t)this->val * other.val % MOD; if (this->val < 0) this->val += MOD; return *this; }
	inline modint<MOD> operator-() const { return modint<MOD>(this->val ? MOD - this->val : 0); }
	modint<MOD> pow(uint64_t k) const { modint<MOD> x = *this, y = 1; for (; k; k >>= 1) { if (k & 1) y *= x; x *= x; } return y; }
	modint<MOD> inv() const { return pow(MOD - 2); }
	inline modint<MOD> operator/(modint<MOD> other) const { return *this * other.inv(); }
	inline modint<MOD> operator/=(modint<MOD> other) { return *this *= other.inv(); }
	inline bool operator==(modint<MOD> other) const { return val == other.val; }
	inline bool operator!=(modint<MOD> other) const { return val != other.val; }
	inline bool operator<(modint<MOD> other) const { return val < other.val; }
	inline bool operator>(modint<MOD> other) const { return val > other.val; }
};
template <int64_t MOD> modint<MOD> operator*(int64_t val, modint<MOD> n) { return modint<MOD>(val) * n; }
template <int64_t MOD> modint<MOD> operator*(int32_t val, modint<MOD> n) { return modint<MOD>(val % MOD) * n; }
template <int64_t MOD> istream &operator>>(istream &in, modint<MOD> &n) { int64_t val; in >> val; n = modint<MOD>(val); return in; }
template <int64_t MOD> ostream &operator<<(ostream &out, modint<MOD> n) { return out << n.val; }
using mint = modint<M>;

struct Combi {
	int n;
	vector<mint> facts, finvs, invs;
	Combi(int _n) : n(_n), facts(_n), finvs(_n), invs(_n) {
		facts[0] = finvs[0] = 1;
		invs[1] = 1;
		for (int i = 2; i < n; i++)
			invs[i] = invs[mod % i] * (-mod / i);
		for (int i = 1; i < n; i++)
		{
			facts[i] = facts[i - 1] * i;
			finvs[i] = finvs[i - 1] * invs[i];
		}
	}
	inline mint fact(int n) { return facts[n]; }
	inline mint finv(int n) { return finvs[n]; }
	inline mint inv(int n) { return invs[n]; }
	inline mint ncr(int n, int k) { return n < k ? 0 : facts[n] * finvs[k] * finvs[n - k]; }
};
Combi C(N);

struct query {
	int l, r, id;
	bool operator<(const query &x) const {
		if (l / B == x.l / B)
			return ((l / B) & 1) ? r > x.r : r < x.r;
		return l / B < x.l / B;
	}
} Q[N];

mint ans[N];
// compute f(n, k) = C(n, 0) + C(n, 1) + ... + C(n, k)
// use the identity: f(n + 1, k) = 2 * f(n, k) - C(n, k)
int32_t main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int q;
	cin >> q;
	for (int i = 1; i <= q; i++) {
		int n, k;
		cin >> n >> k;
		Q[i] = {n, k, i};
	}
	sort(Q + 1, Q + q + 1);
	int n = 1, k = 0;
	mint sum = 1, i2 = (mod + 1) / 2;
	for (int i = 1; i <= q; i++) {
		int L = Q[i].l, R = Q[i].r;
		while (n < L)
		{
			sum = sum * 2 - C.ncr(n, k);
			n++;
		}
		while (n > L)
		{
			--n;
			sum += C.ncr(n, k);
			sum *= i2;
		}
		while (k < R)
		{
			++k;
			sum += C.ncr(n, k);
		}
		while (k > R)
		{
			sum -= C.ncr(n, k);
			k--;
		}
		ans[Q[i].id] = sum;
	}
	for (int i = 1; i <= q; i++) {
		cout << ans[i] << '\n';
	}
	return 0;
}
// https://vjudge.net/problem/HDU-6333

// Sum of C(a(i), k) for each k from 1 to n:

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 9, mod = 924844033;

struct base {
	double x, y;
	base() { x = y = 0; }
	base(double x, double y) : x(x), y(y) {}
};
inline base operator+(base a, base b) { return base(a.x + b.x, a.y + b.y); }
inline base operator-(base a, base b) { return base(a.x - b.x, a.y - b.y); }
inline base operator*(base a, base b) { return base(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
inline base conj(base a) { return base(a.x, -a.y); }
int lim = 1;
vector<base> roots = {{0, 0}, {1, 0}};
vector<int> rev = {0, 1};
const double PI = acosl(-1.0);
void ensure_base(int p) {
	if (p <= lim)
		return;
	rev.resize(1 << p);
	for (int i = 0; i < (1 << p); i++)
		rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (p - 1));
	roots.resize(1 << p);
	while (lim < p) {
		double angle = 2 * PI / (1 << (lim + 1));
		for (int i = 1 << (lim - 1); i < (1 << lim); i++)
		{
			roots[i << 1] = roots[i];
			double angle_i = angle * (2 * i + 1 - (1 << lim));
			roots[(i << 1) + 1] = base(cos(angle_i), sin(angle_i));
		}
		lim++;
	}
}
void fft(vector<base> &a, int n = -1) {
	if (n == -1)
		n = a.size();
	assert((n & (n - 1)) == 0);
	int zeros = __builtin_ctz(n);
	ensure_base(zeros);
	int shift = lim - zeros;
	for (int i = 0; i < n; i++)
		if (i < (rev[i] >> shift))
			swap(a[i], a[rev[i] >> shift]);
	for (int k = 1; k < n; k <<= 1) {
		for (int i = 0; i < n; i += 2 * k)
		{
			for (int j = 0; j < k; j++)
			{
				base z = a[i + j + k] * roots[j + k];
				a[i + j + k] = a[i + j] - z;
				a[i + j] = a[i + j] + z;
			}
		}
	}
}
// eq = 0: 4 FFTs in total
// eq = 1: 3 FFTs in total
vector<int> multiply(vector<int> &a, vector<int> &b, int eq = 0) {
	int need = a.size() + b.size() - 1;
	int p = 0;
	while ((1 << p) < need)
		p++;
	ensure_base(p);
	int sz = 1 << p;
	vector<base> A, B;
	if (sz > (int)A.size())
		A.resize(sz);
	for (int i = 0; i < (int)a.size(); i++) {
		int x = (a[i] % mod + mod) % mod;
		A[i] = base(x & ((1 << 15) - 1), x >> 15);
	}
	fill(A.begin() + a.size(), A.begin() + sz, base{0, 0});
	fft(A, sz);
	if (sz > (int)B.size())
		B.resize(sz);
	if (eq)
		copy(A.begin(), A.begin() + sz, B.begin());
	else {
		for (int i = 0; i < (int)b.size(); i++)
		{
			int x = (b[i] % mod + mod) % mod;
			B[i] = base(x & ((1 << 15) - 1), x >> 15);
		}
		fill(B.begin() + b.size(), B.begin() + sz, base{0, 0});
		fft(B, sz);
	}
	double ratio = 0.25 / sz;
	base r2(0, -1), r3(ratio, 0), r4(0, -ratio), r5(0, 1);
	for (int i = 0; i <= (sz >> 1); i++) {
		int j = (sz - i) & (sz - 1);
		base a1 = (A[i] + conj(A[j])), a2 = (A[i] - conj(A[j])) * r2;
		base b1 = (B[i] + conj(B[j])) * r3, b2 = (B[i] - conj(B[j])) * r4;
		if (i != j)
		{
			base c1 = (A[j] + conj(A[i])), c2 = (A[j] - conj(A[i])) * r2;
			base d1 = (B[j] + conj(B[i])) * r3, d2 = (B[j] - conj(B[i])) * r4;
			A[i] = c1 * d1 + c2 * d2 * r5;
			B[i] = c1 * d2 + c2 * d1;
		}
		A[j] = a1 * b1 + a2 * b2 * r5;
		B[j] = a1 * b2 + a2 * b1;
	}
	fft(A, sz);
	fft(B, sz);
	vector<int> res(need);
	for (int i = 0; i < need; i++) {
		long long aa = A[i].x + 0.5;
		long long bb = B[i].x + 0.5;
		long long cc = A[i].y + 0.5;
		res[i] = (aa + ((bb % mod) << 15) + ((cc % mod) << 30)) % mod;
	}
	return res;
}
int power(long long n, long long k) {
	int ans = 1 % mod;
	n %= mod;
	if (n < 0)
		n += mod;
	while (k) {
		if (k & 1)
			ans = (long long)ans * n % mod;
		n = (long long)n * n % mod;
		k >>= 1;
	}
	return ans;
}
vector<int> g[N];
int sz[N];
void dfs(int u, int p = 0) {
	sz[u] = 1;
	for (auto v : g[u]) {
		if (v == p)
			continue;
		dfs(v, u);
		sz[u] += sz[v];
	}
}
int f[N], ifac[N];
// ans_k = sum_(C(a_i, k))
vector<int> yo(int n, vector<int> a) {
	vector<int> cnt(N, 0);
	for (auto x : a)
		cnt[x]++;
	for (int i = 0; i < N; i++)
		cnt[i] = 1LL * cnt[i] * f[i] % mod;
	vector<int> b(N, 0);
	for (int i = 0; i < N; i++)
		b[i] = ifac[i];
	reverse(b.begin(), b.end());
	auto ans = multiply(cnt, b);
	ans.erase(ans.begin(), ans.begin() + N - 1);
	ans.resize(n + 1);
	for (int i = 0; i <= n; i++)
		ans[i] = 1LL * ans[i] * power(f[i], mod - 2) % mod;
	return ans;
}
int ncr(int n, int k) {
	return 1LL * f[n] * ifac[k] % mod * ifac[n - k] % mod;
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	f[0] = 1;
	for (int i = 1; i < N; i++)
		f[i] = 1LL * i * f[i - 1] % mod;
	for (int i = 0; i < N; i++)
		ifac[i] = power(f[i], mod - 2);
	int n;
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1);
	vector<int> a;
	for (int i = 2; i <= n; i++)
		a.push_back(sz[i]);
	vector<int> ans(n + 1, 0);
	for (int i = 1; i <= n; i++)
		ans[i] = 1LL * ncr(n, i) * n % mod;
	auto p = yo(n, a);
	for (int i = 1; i <= n; i++)
		ans[i] = (ans[i] - p[i] + mod) % mod;
	for (auto &x : a)
		x = n - x;
	p = yo(n, a);
	for (int i = 1; i <= n; i++)
		ans[i] = (ans[i] - p[i] + mod) % mod;
	for (int i = 1; i <= n; i++)
		cout << ans[i] << '\n';
	return 0;
}
// https://atcoder.jp/contests/agc005/tasks/agc005_f

// Sum of nCi for a Fixed Large n:

#pragma GCC optimize("O3")
#pragma GCC target("avx")

#include <cstdio>
#include <cassert>
#include <cmath>
#include <cstring>

#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>

#ifdef __x86_64__
#define NTT64
#endif

#define _rep(_1, _2, _3, _4, name, ...) name
#define rep2(i, n) rep3(i, 0, n)
#define rep3(i, a, b) rep4(i, a, b, 1)
#define rep4(i, a, b, c) for (int i = int(a); i < int(b); i += int(c))
#define rep(...) _rep(__VA_ARGS__, rep4, rep3, rep2, _)(__VA_ARGS__)

using namespace std;

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;
using f80 = long double;

namespace ntt {

#ifdef NTT64
	using word_t = u64;
	using dword_t = __uint128_t;
#else
	using word_t = u32;
	using dword_t = u64;
#endif
	static const int word_bits = 8 * sizeof(word_t);

	template <word_t mod, word_t prim_root>
	class Mod {
	private:
		static constexpr word_t mul_inv(word_t n, int e = 6, word_t x = 1)
		{
			return e == 0 ? x : mul_inv(n, e - 1, x * (2 - x * n));
		}

	public:
		static constexpr word_t inv = mul_inv(mod);
		static constexpr word_t r2 = -dword_t(mod) % mod;
		static constexpr int level = __builtin_ctzll(mod - 1);
		static_assert(inv * mod == 1, "invalid 1/M modulo 2^@.");

		Mod() {}
		Mod(word_t n) : x(init(n)) {};
		static word_t modulus() { return mod; }
		static word_t init(word_t w) { return reduce(dword_t(w) * r2); }
		static word_t reduce(const dword_t w) { return word_t(w >> word_bits) + mod - word_t((dword_t(word_t(w) * inv) * mod) >> word_bits); }
		static Mod omega() { return Mod(prim_root).pow((mod - 1) >> level); }
		Mod &operator+=(Mod rhs)
		{
			this->x += rhs.x;
			return *this;
		}
		Mod &operator-=(Mod rhs)
		{
			this->x += 3 * mod - rhs.x;
			return *this;
		}
		Mod &operator*=(Mod rhs)
		{
			this->x = reduce(dword_t(this->x) * rhs.x);
			return *this;
		}
		Mod operator+(Mod rhs) const { return Mod(*this) += rhs; }
		Mod operator-(Mod rhs) const { return Mod(*this) -= rhs; }
		Mod operator*(Mod rhs) const { return Mod(*this) *= rhs; }
		word_t get() const { return reduce(this->x) % mod; }
		void set(word_t n) const { this->x = n; }
		Mod pow(word_t exp) const
		{
			Mod ret = Mod(1);
			for (Mod base = *this; exp; exp >>= 1, base *= base)
				if (exp & 1)
					ret *= base;
			return ret;
		}
		Mod inverse() const { return pow(mod - 2); }
		friend ostream &operator<<(ostream &os, const Mod &m) { return os << m.get(); }
		static void debug()
		{
			printf("%llu %llu %llu %llu\n", mod, inv, r2, omega().get());
		}
		word_t x;
	};

	const int size = 1 << 16;

#ifdef NTT64
	using m64_1 = ntt::Mod<709143768229478401, 31>;
	using m64_2 = ntt::Mod<711416664922521601, 19>; // <= 712e15 (sub.D = 3)
	m64_1 f1[size], g1[size];
	m64_2 f2[size], g2[size];
#else
	using m32_1 = ntt::Mod<138412033, 5>;
	using m32_2 = ntt::Mod<155189249, 6>;
	using m32_3 = ntt::Mod<163577857, 23>; // <=  16579e4 (sub.D = 3)
	m32_1 f1[size], g1[size];
	m32_2 f2[size], g2[size];
	m32_3 f3[size], g3[size];
#endif

	template <typename mod_t>
	void convolve(mod_t *A, int s1, mod_t *B, int s2, bool cyclic = false) {
		int s = (cyclic ? max(s1, s2) : s1 + s2 - 1);
		int size = 1;
		while (size < s)
			size <<= 1;
		mod_t roots[mod_t::level] = {mod_t::omega()};
		rep(i, 1, mod_t::level) roots[i] = roots[i - 1] * roots[i - 1];
		fill(A + s1, A + size, 0);
		ntt_dit4(A, size, 1, roots);
		if (A == B && s1 == s2)
		{
			rep(i, size) A[i] *= A[i];
		}
		else
		{
			fill(B + s2, B + size, 0);
			ntt_dit4(B, size, 1, roots);
			rep(i, size) A[i] *= B[i];
		}
		ntt_dit4(A, size, -1, roots);
		mod_t inv = mod_t(size).inverse();
		rep(i, cyclic ? size : s) A[i] *= inv;
	}

	template <typename mod_t>
	void rev_permute(mod_t *A, int n) {
		int r = 0, nh = n >> 1;
		rep(i, 1, n)
		{
			for (int h = nh; !((r ^= h) & h); h >>= 1)
				;
			if (r > i)
				swap(A[i], A[r]);
		}
	}

	template <typename mod_t>
	void ntt_dit4(mod_t *A, int n, int sign, mod_t *roots) {
		rev_permute(A, n);
		int logn = __builtin_ctz(n);
		assert(logn <= mod_t::level);

		if (logn & 1)
			rep(i, 0, n, 2)
			{
				mod_t a = A[i], b = A[i + 1];
				A[i] = a + b;
				A[i + 1] = a - b;
			}
		mod_t imag = roots[mod_t::level - 2];
		if (sign < 0)
			imag = imag.inverse();

		mod_t one = mod_t(1);
		rep(e, 2 + (logn & 1), logn + 1, 2)
		{
			const int m = 1 << e;
			const int m4 = m >> 2;
			mod_t dw = roots[mod_t::level - e];
			if (sign < 0)
				dw = dw.inverse();

			const int block_size = min(n, max(m, (1 << 15) / int(sizeof(A[0]))));
			rep(k, 0, n, block_size)
			{
				mod_t w = one, w2 = one, w3 = one;
				rep(j, m4)
				{
					rep(i, k + j, k + block_size, m)
					{
						mod_t a0 = A[i + m4 * 0] * one, a2 = A[i + m4 * 1] * w2;
						mod_t a1 = A[i + m4 * 2] * w, a3 = A[i + m4 * 3] * w3;
						mod_t t02 = a0 + a2, t13 = a1 + a3;
						A[i + m4 * 0] = t02 + t13;
						A[i + m4 * 2] = t02 - t13;
						t02 = a0 - a2, t13 = (a1 - a3) * imag;
						A[i + m4 * 1] = t02 + t13;
						A[i + m4 * 3] = t02 - t13;
					}
					w *= dw;
					w2 = w * w;
					w3 = w2 * w;
				}
			}
		}
	}

} // namespace ntt

using R = int;
using R64 = i64;

class poly {
public:
#ifdef NTT64
	static const int ntt_threshold = 900; // deg(f * g)
#else
	static const int ntt_threshold = 1500; // deg(f * g)
#endif

	static R add_mod(R a, R b) { return int(a += b - mod) < 0 ? a + mod : a; }
	static R sub_mod(R a, R b) { return int(a -= b) < 0 ? a + mod : a; }
	static R64 sub_mul_mod(R64 a, R b, R c) {
		i64 t = i64(a) - i64(int(b)) * int(c);
		return t < 0 ? t + lmod : t;
	}
	static R mul_mod(R a, R b) { return R64(a) * b % fast_mod; }
	static R pow_mod(R a, int e) {
		R ret = 1 % fast_mod;
		for (; e; e >>= 1, a = mul_mod(a, a))
		{
			if (e & 1)
				ret = mul_mod(ret, a);
		}
		return ret;
	}
	static R mod_inv(R a) {
		R b = mod, s = 1, t = 0;
		while (b > 0)
		{
			swap(s -= t * (a / b), t);
			swap(a %= b, b);
		}
		if (a > 1)
		{
			fprintf(stderr, "Error: invalid modular inverse\n");
			exit(1);
		};
		return int(s) < 0 ? s + mod : s;
	}
	inline static void vec_add(R64 *res, int s, const R *f, R c) {
		rep(i, s) res[i] = sub_mul_mod(res[i], mod - c, f[i]);
	}
	inline static void vec_sub(R64 *res, int s, const R *f, R c) {
		rep(i, s) res[i] = sub_mul_mod(res[i], c, f[i]);
	}

#ifdef NTT64
	struct fast_div {
		using u128 = __uint128_t;
		fast_div() {}
		fast_div(u64 n) : m(n)
		{
			s = (n == 1) ? 0 : 127 - __builtin_clzll(n - 1);
			x = ((u128(1) << s) + n - 1) / n;
		}
		friend u64 operator/(u64 n, fast_div d) { return u128(n) * d.x >> d.s; }
		friend u64 operator%(u64 n, fast_div d) { return n - n / d * d.m; }
		u64 m, s, x;
	};
#else
	struct fast_div {
		fast_div() {}
		fast_div(u32 n) : m(n) {}
		friend u32 operator%(u64 n, fast_div d) { return n % d.m; }
		u32 m;
	};
#endif

public:
	poly() {}
	poly(int n) : coefs(n) {}
	poly(int n, int c) : coefs(n, c % mod) {}
	poly(const R *ar, int s) : coefs(ar, ar + s) {}
	poly(const vector<R> &v) : coefs(v) {}
	poly(const poly &f, int beg, int end = -1) {
		if (end < 0)
			end = beg, beg = 0;
		resize(end - beg);
		rep(i, beg, end) if (i < f.size()) coefs[i - beg] = f[i];
	}

	static int ilog2(u64 n) {
		return 63 - __builtin_clzll(n);
	}
	int size() const { return coefs.size(); }
	void resize(int s) { coefs.resize(s); }
	void push_back(R c) { coefs.push_back(c); }

	const R *data() const { return coefs.data(); }
	R *data() { return coefs.data(); }
	const R &operator[](int i) const { return coefs[i]; }
	R &operator[](int i) { return coefs[i]; }

	void reverse() { std::reverse(coefs.begin(), coefs.end()); }

	poly operator-() {
		poly ret = *this;
		rep(i, ret.size()) ret[i] = (ret[i] == 0 ? 0 : mod - ret[i]);
		return ret;
	}
	poly &operator+=(const poly &rhs) {
		if (size() < rhs.size())
			resize(rhs.size());
		rep(i, rhs.size()) coefs[i] = add_mod(coefs[i], rhs[i]);
		return *this;
	}
	poly &operator-=(const poly &rhs) {
		if (size() < rhs.size())
			resize(rhs.size());
		rep(i, rhs.size()) coefs[i] = sub_mod(coefs[i], rhs[i]);
		return *this;
	}
	poly &operator*=(const poly &rhs) { return *this = *this * rhs; }

	poly &rev_add(const poly &rhs) {
		if (size() < rhs.size())
		{
			int s = size();
			resize(rhs.size());
			rep(i, s) coefs[size() - 1 - i] = coefs[s - 1 - i];
			rep(i, size() - s) coefs[i] = 0;
		}
		rep(i, rhs.size()) coefs[size() - 1 - i] =
			add_mod(coefs[size() - 1 - i], rhs.coefs[rhs.size() - 1 - i]);
		return *this;
	}

	poly operator+(const poly &rhs) const { return poly(*this) += rhs; }
	poly operator-(const poly &rhs) const { return poly(*this) -= rhs; }
	poly operator*(const poly &rhs) const { return this->mul(rhs); }

	static void set_mod(R m, int N = 2) {
		mod = m;
		lmod = R64(m) << 32;
		N = max(2, N);
		fast_mod = fast_div(mod);
		invs.assign(N + 1, 1);
		facts.assign(N + 1, 1);
		ifacts.assign(N + 1, 1);
		invs[1] = 1;
		rep(i, 2, N + 1)
		{
			invs[i] = mul_mod(invs[mod % i], mod - mod / i);
			facts[i] = mul_mod(facts[i - 1], i);
			ifacts[i] = mul_mod(ifacts[i - 1], invs[i]);
		}
	}

private:
#ifdef NTT64
	static poly mul_crt(int beg, int end) {
		using namespace ntt;
		auto inv = m64_2(m64_1::modulus()).inverse();
		auto mod1 = m64_1::modulus() % fast_mod;
		poly ret(end - beg);
		rep(i, ret.size())
		{
			u64 r1 = f1[i + beg].get(), r2 = f2[i + beg].get();
			ret[i] = (r1 + (m64_2(r2 + m64_2::modulus() - r1) * inv).get() % fast_mod * mod1) % fast_mod;
		}
		return ret;
	}

	static void mul2(const poly &f, const poly &g, bool cyclic = false) {
		using namespace ntt;
		if (&f == &g)
		{
			rep(i, f.size()) f1[i] = f[i];
			convolve(f1, f.size(), f1, f.size(), cyclic);
			rep(i, f.size()) f2[i] = f[i];
			convolve(f2, f.size(), f2, f.size(), cyclic);
		}
		else
		{
			rep(i, f.size()) f1[i] = f[i];
			rep(i, g.size()) g1[i] = g[i];
			convolve(f1, f.size(), g1, g.size(), cyclic);
			rep(i, f.size()) f2[i] = f[i];
			rep(i, g.size()) g2[i] = g[i];
			convolve(f2, f.size(), g2, g.size(), cyclic);
		}
	}
#else
	static poly mul_crt(int beg, int end) {
		using namespace ntt;
		auto m1 = m32_1::modulus();
		auto m2 = m32_2::modulus();
		auto m3 = m32_3::modulus();
		auto m12 = u64(m1) * m2;

		poly ret(end - beg);
		u32 m12m = m12 % mod;
		u32 inv1 = m32_2(m1).inverse().get();
		u32 inv12 = m32_3(m12 % m3).inverse().get();

		rep(i, ret.size())
		{
			u32 r1 = f1[i + beg].get(), r2 = f2[i + beg].get(), r3 = f3[i + beg].get();
			u64 r = r1 + u64(r2 + m2 - r1) * inv1 % m2 * m1;
			ret[i] = (r + u64(r3 + m3 - r % m3) * inv12 % m3 * m12m) % mod;
		}
		return ret;
	}

	static void mul2(const poly &f, const poly &g, bool cyclic = false) {
		using namespace ntt;
		if (&f == &g)
		{
			rep(i, f.size()) f1[i] = f[i] % m32_1::modulus();
			convolve(f1, f.size(), f1, f.size(), cyclic);
			rep(i, f.size()) f2[i] = f[i] % m32_2::modulus();
			convolve(f2, f.size(), f2, f.size(), cyclic);
			rep(i, f.size()) f3[i] = f[i] % m32_3::modulus();
			convolve(f3, f.size(), f3, f.size(), cyclic);
		}
		else
		{
			rep(i, f.size()) f1[i] = f[i] % m32_1::modulus();
			rep(i, g.size()) g1[i] = g[i] % m32_1::modulus();
			convolve(f1, f.size(), g1, g.size(), cyclic);
			rep(i, f.size()) f2[i] = f[i] % m32_2::modulus();
			rep(i, g.size()) g2[i] = g[i] % m32_2::modulus();
			convolve(f2, f.size(), g2, g.size(), cyclic);
			rep(i, f.size()) f3[i] = f[i] % m32_3::modulus();
			rep(i, g.size()) g3[i] = g[i] % m32_3::modulus();
			convolve(f3, f.size(), g3, g.size(), cyclic);
		}
	}
#endif

public:
	static void amul(const R *f, int s1, const R *g, int s2, R *res) {
		int s = s1 + s2 - 1;
		tmp64.assign(s, 0);
		rep(i, s2) if (g[i]) vec_add(tmp64.data() + i, s1, f, g[i]);
		rep(i, s) res[i] = tmp64[i] % fast_mod;
	}

	poly mul_basecase(const poly &g) const {
		const auto &f = *this;
		int s = size() + g.size() - 1;
		poly ret(s);
		amul(f.data(), f.size(), g.data(), g.size(), ret.data());
		return ret;
	}

	// 1.0 * M(n)
	poly mul(const poly &g) const {
		const auto &f = *this;
		if (f.size() == 0 || g.size() == 0)
			return poly();
		if (f.size() + g.size() <= ntt_threshold)
		{
			return f.mul_basecase(g);
		}
		else
		{
			mul2(f, g, false);
			return mul_crt(0, f.size() + g.size() - 1);
		}
	}

	// 1.0 * M(n)
	poly middle_product(const poly &g) const {
		const poly &f = *this;
		if (f.size() == 0 || g.size() == 0)
			return poly();
		mul2(f, g, true);
		return mul_crt(f.size(), g.size());
	}

	void print() const {
		printf("[");
		if (size())
		{
			printf("%u", coefs[0]);
			rep(i, 1, size()) printf(", %u", coefs[i]);
		}
		puts("]");
	}

public:
	vector<R> coefs;
	static vector<R> tmp32;
	static vector<R64> tmp64;
	static vector<R> invs, facts, ifacts;
	static R mod;
	static R64 lmod;
	static fast_div fast_mod;
};
R poly::mod;
R64 poly::lmod;
poly::fast_div poly::fast_mod;
vector<R> poly::tmp32;
vector<R64> poly::tmp64;
vector<R> poly::invs, poly::facts, poly::ifacts;

int pow_mod(int b, int e, int mod) {
	int ret = 1;
	for (; e; e >>= 1, b = i64(b) * b % mod) {
		if (e & 1)
			ret = i64(ret) * b % mod;
	}
	return ret;
}

int binomial_sum_mod_p(int N, int K, int mod) {
	if (K == 0)
		return 1 % mod;
	if (N <= K)
		return pow_mod(2, N, mod);
	if (i64(K) * 2 > N) {
		return (pow_mod(2, N, mod) + i64(mod) - binomial_sum_mod_p(N, N - K - 1, mod)) % mod;
	}
	assert(N < mod);

	const int sqrt_K = sqrt(K);
	poly::set_mod(mod, sqrt_K);

	auto mod_invs = [&](vector<int> &f) {
		int n = f.size();
		vector<int> ret(f);
		if (n > 0)
		{
			rep(i, 1, n) ret[i] = i64(ret[i - 1]) * ret[i] % mod;
			int inv = poly::mod_inv(ret[n - 1]);
			for (int i = n - 1; i > 0; --i)
			{
				ret[i] = i64(ret[i - 1]) * inv % mod;
				inv = i64(inv) * f[i] % mod;
			}
			ret[0] = inv;
		}
		return ret;
	};

	auto conv = [&](vector<int> &f) -> poly {
		int n = f.size();
		const auto &ifacts = poly::ifacts;
		auto g = poly(f);
		rep(i, n)
		{
			int d = i64(ifacts[i]) * ifacts[(n - 1) - i] % mod;
			if ((n - 1 - i) & 1)
				d = mod - d;
			g[i] = i64(g[i]) * d % mod;
		}
		return g;
	};

	auto shift = [&](const poly &cf, const poly &f, i64 dx) {
		if ((dx %= mod) < 0)
			dx += mod;
		const int n = f.size();
		const int a = i64(dx) * poly::mod_inv(sqrt_K) % mod;

		auto g = poly(2 * n);
		rep(i, g.size()) g[i] = (i64(mod) + a + i - n) % mod;
		rep(i, g.size()) if (g[i] == 0) g[i] = 1;

		g.coefs = mod_invs(g.coefs);
		auto ret = cf.middle_product(g);
		int prod = 1;
		rep(i, n) prod = i64(prod) * (i64(mod) + a + n - 1 - i) % mod;
		for (int i = n - 1; i >= 0; --i)
		{
			ret[i] = i64(ret[i]) * prod % mod;
			prod = i64(prod) * g[n + i] % mod * (i64(mod) + a + i - n) % mod;
		}
		if (dx % sqrt_K == 0)
		{
			int k = n - dx / sqrt_K;
			rep(i, k) ret[i] = f[n - k + i];
		}
		return ret.coefs;
	};

	using Pair = pair<vector<int>, vector<int>>;
	function<Pair(int)> rec = [&](int n) -> Pair {
		if (n == 1)
		{
			return Pair({N, N - sqrt_K}, {1, sqrt_K + 1});
		}
		int nh = n >> 1;
		auto res = rec(nh);
		auto &f11 = res.first, &g11 = res.second;

		auto f = conv(f11), g = conv(g11);
		auto g12 = shift(g, g11, nh);
		auto g21 = shift(g, g11, i64(sqrt_K) * nh);
		auto g22 = shift(g, g11, i64(sqrt_K) * nh + nh);

		auto f12 = shift(f, f11, N - nh * i64(sqrt_K + 2));
		auto f21 = shift(f, f11, i64(sqrt_K) * nh);
		auto f22 = shift(f, f11, N - i64(2) * nh * (sqrt_K + 1));
		rep(i, nh + 1)
		{
			g11[i] = (i64(g11[i]) * f12[nh - i] + i64(g12[i]) * f11[i]) % mod;
		}
		rep(i, 1, nh + 1)
		{
			g11.push_back((i64(g21[i]) * f22[nh - i] + i64(g22[i]) * f21[i]) % mod);
		}

		f12 = shift(f, f11, nh);
		f22 = shift(f, f11, i64(sqrt_K) * nh + nh);

		rep(i, nh + 1) f11[i] = i64(f11[i]) * f12[i] % mod;
		rep(i, 1, nh + 1) f11.push_back(i64(f21[i]) * f22[i] % mod);

		if (n & 1)
		{
			rep(i, n)
			{
				g11[i] = (i64(g11[i]) + f11[i]) * (n + i64(i) * sqrt_K) % mod;
			}
			rep(i, n)
			{
				f11[i] = i64(f11[i]) * (i64(N) + mod - sqrt_K * i - n + 1) % mod;
			}
			vector<int> vals(n);
			rep(i, n) vals[i] = (i64(sqrt_K) * n + i + 1) % mod;
			if (i64(sqrt_K + 1) * n < mod)
			{
				int prod = 1;
				rep(i, n) prod = i64(prod) * vals[i] % mod;
				auto invs = mod_invs(vals);
				i64 s = 0;
				rep(i, n)
				{
					s += prod;
					prod = i64(prod) * invs[i] % mod * (i64(N) + mod - i64(sqrt_K) * n - i) % mod;
				}
				g11.push_back(s % mod);
				f11.push_back(prod);
			}
			else
			{
				g11.push_back(0);
				f11.push_back(0);
			}
		}
		return {f11, g11};
	};

	auto res = rec(sqrt_K);
	auto &f1 = res.first, &g1 = res.second;
	auto f2 = shift(conv(f1), f1, N - i64(sqrt_K) * (sqrt_K + 1));
	reverse(f2.begin(), f2.end());
	f2.resize(f2.size() - 1);
	f2 = mod_invs(f2);

	i64 ret = 0;
	rep(i, sqrt_K) {
		ret = (ret * f1[sqrt_K - 1 - i] + g1[sqrt_K - 1 - i]) % mod;
		ret = ret * f2[sqrt_K - 1 - i] % mod;
	}

	int prod = 1;
	rep(i, sqrt_K) {
		prod = i64(prod) * f1[i] % mod * f2[i] % mod;
	}

	const int rest = max(0, K - sqrt_K * sqrt_K);
	ret += prod;
	vector<int> invs(rest);
	rep(i, rest) invs[i] = i + 1 + sqrt_K * sqrt_K;
	invs = mod_invs(invs);
	rep(i, rest) {
		prod = i64(prod) * (N - sqrt_K * sqrt_K - i) % mod * invs[i] % mod;
		ret += prod;
	}
	ret %= mod;
	return ret;
}

// credit: Min_25
void solve() {
	const u32 p = u32(-1) >> 1; // 2^31
	printf("%d\n", binomial_sum_mod_p(2e9, 1e9, p));
}

int main() {
	// clock_t beg = clock();
	solve();
	// clock_t end = clock();
	// fprintf(stderr, "%.3f sec\n", double(end - beg) / CLOCKS_PER_SEC);
	return 0;
}
// https://discuss.codechef.com/t/how-to-calculate-sum-of-binomial-coefficients-efficiently/12846/4

// Sum of nCi over a Fixed Congruence Class:

#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 16;
const int mod = 998244353;
const int root = 3;
using ll = long long;
int lim, rev[N], w[N], wn[N], inv_lim;
void reduce(int &x) { x = (x + mod) % mod; }
int POW(int x, int y, int ans = 1) {
	for (; y; y >>= 1, x = (long long)x * x % mod)
		if (y & 1)
			ans = (long long)ans * x % mod;
	return ans;
}
void precompute(int len) {
	lim = wn[0] = 1;
	int s = -1;
	while (lim < len)
		lim <<= 1, ++s;
	for (int i = 0; i < lim; ++i)
		rev[i] = rev[i >> 1] >> 1 | (i & 1) << s;
	const int g = POW(root, (mod - 1) / lim);
	inv_lim = POW(lim, mod - 2);
	for (int i = 1; i < lim; ++i)
		wn[i] = (long long)wn[i - 1] * g % mod;
}
void ntt(vector<int> &a, int typ) {
	for (int i = 0; i < lim; ++i)
		if (i < rev[i])
			swap(a[i], a[rev[i]]);
	for (int i = 1; i < lim; i <<= 1) {
		for (int j = 0, t = lim / i / 2; j < i; ++j)
			w[j] = wn[j * t];
		for (int j = 0; j < lim; j += i << 1)
			for (int k = 0; k < i; ++k)
			{
				const int x = a[k + j], y = (long long)a[k + j + i] * w[k] % mod;
				reduce(a[k + j] += y - mod), reduce(a[k + j + i] = x - y);
			}
	}
	if (!typ) {
		reverse(a.begin() + 1, a.begin() + lim);
		for (int i = 0; i < lim; ++i)
			a[i] = (long long)a[i] * inv_lim % mod;
	}
}
vector<int> multiply(vector<int> &f, vector<int> &g) {
	int n = (int)f.size() + (int)g.size() - 1;
	precompute(n);
	vector<int> a = f, b = g;
	a.resize(lim);
	b.resize(lim);
	ntt(a, 1), ntt(b, 1);
	for (int i = 0; i < lim; ++i)
		a[i] = (long long)a[i] * b[i] % mod;
	ntt(a, 0);
	while ((int)a.size() && a.back() == 0)
		a.pop_back();
	return a;
}
int m;
void fix(vector<int> &ans) {
	int k = ans.size();
	if (k < m)
		return;
	for (int i = k - 1; i >= m; i--) {
		ans[i % m] += ans[i];
		ans[i % m] %= mod;
	}
	ans.resize(m);
}
int32_t main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	ll n;
	cin >> n;
	int x;
	cin >> x >> m;
	vector<int> a({1, 1}), ans({1});
	while (n) {
		if (n & 1)
		{
			ans = multiply(ans, a);
			fix(ans);
		}
		a = multiply(a, a);
		fix(a);
		n >>= 1;
	}
	ans.resize(m);
	// ans[i] = sum of nCk s.t. k % m = i (0 <= k <= n)
	int cur = 1, res = 0;
	for (int i = 0; i < m; i++) {
		res += 1LL * cur * ans[i] % mod;
		res %= mod;
		cur = 1LL * cur * x % mod;
	}
	cout << res << '\n';
	return 0;
}
// https://toph.co/p/abcdefgh

// nCr Modulo Any MOD:

#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 9;
using ll = long long;

int power(long long n, long long k, const int mod) {
	int ans = 1 % mod;
	n %= mod;
	if (n < 0)
		n += mod;
	while (k) {
		if (k & 1)
			ans = (long long)ans * n % mod;
		n = (long long)n * n % mod;
		k >>= 1;
	}
	return ans;
}
ll extended_euclid(ll a, ll b, ll &x, ll &y) {
	if (b == 0) {
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
ll inverse(ll a, ll m) {
	ll x, y;
	ll g = extended_euclid(a, m, x, y);
	if (g != 1)
		return -1;
	return (x % m + m) % m;
}
// returns n! % mod without taking all the multiple factors of p into account that appear in the factorial
// mod = multiple of p
// O(mod) * log(n)
int factmod(ll n, int p, const int mod) {
	vector<int> f(mod + 1);
	f[0] = 1 % mod;
	for (int i = 1; i <= mod; i++) {
		if (i % p)
			f[i] = 1LL * f[i - 1] * i % mod;
		else
			f[i] = f[i - 1];
	}
	int ans = 1 % mod;
	while (n > 1) {
		ans = 1LL * ans * f[n % mod] % mod;
		ans = 1LL * ans * power(f[mod], n / mod, mod) % mod;
		n /= p;
	}
	return ans;
}
ll multiplicity(ll n, int p) {
	ll ans = 0;
	while (n) {
		n /= p;
		ans += n;
	}
	return ans;
}
// C(n, r) modulo p^k
// O(p^k log n)
int ncr(ll n, ll r, int p, int k) {
	if (n < r or r < 0)
		return 0;
	int mod = 1;
	for (int i = 0; i < k; i++) {
		mod *= p;
	}
	ll t = multiplicity(n, p) - multiplicity(r, p) - multiplicity(n - r, p);
	if (t >= k)
		return 0;
	int ans = 1LL * factmod(n, p, mod) * inverse(factmod(r, p, mod), mod) % mod * inverse(factmod(n - r, p, mod), mod) % mod;
	ans = 1LL * ans * power(p, t, mod) % mod;
	return ans;
}
// finds x such that x % m1 = a1, x % m2 = a2. m1 and m2 may not be coprime
// here, x is unique modulo m = lcm(m1, m2). returns (x, m). on failure, m = -1.
pair<ll, ll> CRT(ll a1, ll m1, ll a2, ll m2) {
	ll p, q;
	ll g = extended_euclid(m1, m2, p, q);
	if (a1 % g != a2 % g)
		return make_pair(0, -1);
	ll m = m1 / g * m2;
	p = (p % m + m) % m;
	q = (q % m + m) % m;
	return make_pair((p * a2 % m * (m1 / g) % m + q * a1 % m * (m2 / g) % m) % m, m);
}
int spf[N];
vector<int> primes;
void sieve() {
	for (int i = 2; i < N; i++) {
		if (spf[i] == 0)
			spf[i] = i, primes.push_back(i);
		int sz = primes.size();
		for (int j = 0; j < sz && i * primes[j] < N && primes[j] <= spf[i]; j++)
		{
			spf[i * primes[j]] = primes[j];
		}
	}
}
// O(m log(n) log(m))
int ncr(ll n, ll r, int m) {
	if (n < r or r < 0)
		return 0;
	pair<ll, ll> ans({0, 1});
	while (m > 1) {
		int p = spf[m], k = 0, cur = 1;
		while (m % p == 0)
		{
			m /= p;
			cur *= p;
			++k;
		}
		ans = CRT(ans.first, ans.second, ncr(n, r, p, k), cur);
	}
	return ans.first;
}
int32_t main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	sieve();
	int t;
	cin >> t;
	while (t--) {
		ll n, k;
		cin >> n >> k;
		int m;
		cin >> m;
		ll r = (n + k - 1) / k;
		cout << r << ' ' << ncr((k - n % k) % k + r - 1, r - 1, m) << '\n';
	}
	return 0;
}
// https://www.codechef.com/problems/SANDWICH
// https://cp-algorithms.com/combinatorics/binomial-coefficients.html#mod-prime-pow