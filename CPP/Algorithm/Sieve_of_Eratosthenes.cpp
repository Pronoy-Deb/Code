// Index: 1-based, Note: if (!sv[n]) --> prime
// Comlexity: O(n * (log(log(n))))

bool sv[N];
void pre()
{
	sv[0] = sv[1] = true;
	for (int i = 4; i < N; i += 2)
		sv[i] = true;
	for (long long i = 3; i * i < N; i += 2)
	{
		if (!sv[i])
		{
			for (long long j = i * i; j < N; j += (i << 1))
				sv[j] = 1;
		}
	}
}

// To store the primes:

bool sv[N];
vector<long long> pri;
void pre()
{
	pri.push_back(2);
	for (long long i = 3; i < N; i += 2)
	{
		if (!sv[i])
		{
			pri.push_back(i);
			for (long long j = i * i; j < N; j += (i << 1))
				sv[j] = 1;
		}
	}
}

// Comlexity: O(n)

bool sv[N];
long long spf[N];
vector<long long> pri;
void pre()
{
	sv[0] = sv[1] = true;
	for (int i = 2; i < N; ++i)
	{
		if (!sv[i])
		{
			pri.push_back(i);
			spf[i] = i;
		}
		int sz = pri.size();
		for (int j = 0; j < sz && i * pri[j] < N && pri[j] <= spf[i]; ++j)
		{
			sv[i * pri[j]] = true;
			spf[i * pri[j]] = pri[j];
		}
	}
}

// OR,

#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 9;

vector<int> primes;
bool is_prime[N];
// use bitset<N> is_prime; to have O(N/64) memory complexity
// using bitset you can solve upto around N = 10^8 in 1s
void sieve_v0()
{
	for (int i = 2; i < N; i++)
	{
		is_prime[i] = true;
	}
	for (int i = 2; i * i < N; i++)
	{
		if (is_prime[i])
		{
			for (int j = i * i; j < N; j += i)
			{
				is_prime[j] = false;
			}
		}
	}
	for (int i = 2; i < N; i++)
	{
		if (is_prime[i])
		{
			primes.push_back(i);
		}
	}
}

// sieve with smallest prime factors (spf)
int spf[N];
void sieve()
{
	for (int i = 2; i < N; i++)
	{
		spf[i] = i;
	}
	for (int i = 2; i * i < N; i++)
	{
		if (spf[i] == i)
		{
			for (int j = i * i; j < N; j += i)
			{
				spf[j] = min(spf[j], i);
			}
		}
	}
	for (int i = 2; i < N; i++)
	{
		if (spf[i] == i)
		{
			primes.push_back(i);
		}
	}
}

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	sieve_v0();
	cout << primes.size() << '\n';
	primes.clear();
	sieve();
	cout << primes.size() << '\n';
	return 0;
}

// Alternate (Slower):

bool sv[N];
void pre()
{
	sv[0] = sv[1] = true;
	for (int i = 2; i < N; ++i)
	{
		if (!sv[i])
		{
			for (int j = (i << 1); j < N; j += i)
				sv[j] = true;
		}
	}
}

// Bitwise Sieve:
// Note: if (sv(n)) --> pri

long long sv[(N >> 5) + 2];
bool sv(auto n) { return !(sv[n >> 5] & (1 << (n & 31))); }
void pre()
{
	for (int i = 4; i <= N; i += 2)
		sv[i >> 5] = (sv[i >> 5] = sv[i >> 5] | (1 << (i & 31)));
	for (long long i = 3; i * i <= N; i += 2)
	{
		if (sv(i))
		{
			for (long long j = i * i; j <= N; j += (i << 1))
				sv[j >> 5] = (sv[j >> 5] = sv[j >> 5] | (1 << (j & 31)));
		}
	}
}

// Segmented Sieve:

bool sv[N];
vector<long long> pri;
void pre()
{
	pri.push_back(2);
	for (long long i = 3; i < N; i += 2)
	{
		if (!sv[i])
		{
			pri.push_back(i);
			for (long long j = i * i; j < N; j += (i << 1))
				sv[j] = 1;
		}
	}
}
bool pri[N];
void seg(auto l, auto r)
{
	for (int i = 0; i < r - l + 1; ++i)
		pri[i] = true;
	if (l == 1)
		pri[0] = false;
	for (int i = 0; pri[i] * pri[i] <= r; ++i)
	{
		long long cur = pri[i], base = (l / cur) * cur;
		if (base < l)
			base += cur;
		for (long long j = base; j <= r; j += cur)
			pri[j - l] = 0;
		if (base == cur)
			pri[base - l] = true;
	}
	for (int i = 0; i < r - l + 1; ++i)
	{
		if (pri[i])
			cout << (i + l) << '\n';
	}
}

// Operation:
pre();
cin >> q;
while (q--)
{
	int l, r;
	cin >> l >> r;
	seg(l, r);
}

// Linear Sieve for Multiplicative Functions:

#include <bits/stdc++.h>
using namespace std;

const int N = 1e7 + 9;

// f is multiplicative with f(p^k) = k
int spf[N], f[N], cnt[N]; // cnt[i] = power of spf[i] in i
vector<int> primes;
void sieve()
{
	f[1] = 1;
	for (int i = 2; i < N; i++)
	{
		if (spf[i] == 0)
		{ // i is prime
			spf[i] = i, primes.push_back(i);
			f[i] = 1;
			cnt[i] = 1;
		}
		int sz = primes.size();
		for (int j = 0; j < sz && i * primes[j] < N && primes[j] <= spf[i]; j++)
		{
			int p = i * primes[j];
			spf[p] = primes[j];
			if (primes[j] == spf[i])
			{										 // primes[j] divides i
				f[p] = f[i] / cnt[i] * (cnt[i] + 1); // f(i * primes[j]) = f(i / (primes[j]^cnt[i])) * f(primes[j]^(cnt[i] + 1))
				cnt[p] = cnt[i] + 1;
			}
			else
			{ // primes[j] does not divide i
				f[p] = f[i] * f[primes[j]];
				cnt[p] = 1;
			}
		}
	}
}

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	sieve();
	for (int i = 1; i <= 10; i++)
	{
		cout << f[i] << '\n';
	}
	return 0;
}
// https://codeforces.com/blog/entry/54090

// Min 25 Sieve:

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 9, D = 3; // N >= 2 * sqrt(n)
const int mod = 1e9 + 7;
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

using T = mint;

/**
Let f(x) be a multiplicative function and
when p is a prime, f(p) has a polynomial representation
and f(p^k) can be calculated quickly

We can compute the prefix sum of f(n) in O((n^(3/4)) / logn) using Min_25 sieve
Takes ~1s for n = 10^10 (deg = 3) in CF
unfold the loops over poly to make the code faster
Tutorial: https://www.luogu.com.cn/problem/solution/P5325
**/
int primes[N], p, deg;
T pref[D][N];
T poly[D]; // polynomial representation of f(p)
void sieve(int n)
{
	vector<bool> f(n + 1, false);
	p = 0;
	for (int i = 2; i <= n; i++)
	{
		if (!f[i])
		{
			primes[++p] = i;
			T cur = 1;
			// pref[k][p] = sum of primes[i]^k s.t. i <= p
			for (int k = 0; k < deg; k++)
			{
				pref[k][p] = pref[k][p - 1] + cur;
				cur *= i;
			}
		}
		for (int j = 1; j <= p and primes[j] * i <= n; j++)
		{
			f[i * primes[j]] = 1;
			if (i % primes[j] == 0)
				break;
		}
	}
}

int r, id1[N], id2[N];
ll n;
int get_id(ll x)
{
	return x <= r ? id1[x] : id2[n / x];
}
int tot;
T g[D][N];
ll a[N];

// f(p^k) in O(1)
inline T eval(int p, int k, ll pw)
{ // pw = p^k, pw <= n
	T ans = pw % mod;
	return ans * (ans - 1);
}

// no memorization needed!
// sum of f(i) s.t. spf[i] > primes[j]
T yo(ll x, int j)
{
	if (primes[j] >= x)
		return 0;
	int id = get_id(x);
	T ans = 0;
	// initialization: ans = g(x) - g(primes[j])
	for (int k = 0; k < deg; k++)
	{
		ans += poly[k] * g[k][id];
		;
	}
	for (int k = 0; k < deg; k++)
	{
		ans -= poly[k] * pref[k][j];
	}
	for (int i = j + 1; i <= p and primes[i] <= x / primes[i]; i++)
	{
		ll pw = primes[i];
		for (int e = 1; pw <= x; e++)
		{
			ans += eval(primes[i], e, pw) * (yo(x / pw, i) + (e != 1));
			if (!(pw <= x / primes[i]))
				break;
			pw *= primes[i];
		}
	}
	return ans;
}

// Min_25: Say my name
// Dirichlet: You're heisenberg
// Min_25: You're goddamn right

// sum of f(i) for 1 <= i <= n
// pol is the polynomial representation of f(p)
T solve(ll _n, vector<T> pol)
{
	n = _n;
	deg = pol.size();
	for (int i = 0; i < deg; i++)
	{
		poly[i] = pol[i];
	}
	r = sqrt(n);
	while (1LL * r * r < n)
		++r;
	while (1LL * r * r > n)
		--r;
	sieve(r);
	tot = 0;
	ll i = 1;
	while (i <= n)
	{
		ll x = n / i;
		ll j = n / x;
		a[++tot] = x;

		// initialization g[k][tot] = sum of i^k for 2 <= i <= x
		T z = x % mod; // remove this mod if not needed
		for (int k = 0; k < deg; k++)
		{
			if (k == 0)
			{
				g[k][tot] = z - 1;
			}
			if (k == 1)
			{
				g[k][tot] = z * (z + 1) / 2 - 1;
			}
			if (k == 2)
			{
				g[k][tot] = z * (z + 1) * (2 * z + 1) / 6 - 1;
			}
			// compute for larger values using lagrange if needed
		}

		if (x <= r)
			id1[x] = tot;
		else
			id2[n / x] = tot;
		i = j + 1;
	}

	// an integer x belongs to the array a iff for some integer z, n / z = x
	// g[k][i] = sum of prime^k for prime <= a[i]
	for (int i = 1; i <= p; i++)
	{
		for (int j = 1; j <= tot && primes[i] <= a[j] / primes[i]; j++)
		{
			int id = get_id(a[j] / primes[i]);
			T cur = 1;
			for (int k = 0; k < deg; k++)
			{
				g[k][j] -= cur * (g[k][id] - pref[k][i - 1]);
				cur *= primes[i];
			}
		}
	}
	return yo(n, 0) + 1; // add f(1)
}

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	vector<T> p({0, -1, 1});
	ll n;
	cin >> n;
	cout << solve(n, p) << '\n';
	return 0;
}

// https://www.luogu.com.cn/problem/P5325

// Powerful Number Sieve:

#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 9;
using ll = long long;

/**
 * Tutorial: https://oi-wiki.org/math/number-theory/powerful-number/
 * - f() is multiplicative, need to find prefix sum of f
 * - Consider two functions g() and h() such that f = g [*] h (dirichlet convolution)
 * - So f(n) = sum_{d | n}{g(d) * h(n / d)}
 * - Condition: This g() is special
 *    => for all primes p, f(p) = g(p)
 *    => prefix sum of g() is easy to calculate
 * - We have f(n) = sum_{d = 1 to n}{h(d) * g_prefix_sum(floor(n / d))}
 * - But h(p) is 0 from all primes (check the blog)
 * - So we can brute over all powerful numbers only and there are only O(sqrt(n)) powerful number upto n
 *
 * General approach:
 * - Find suitable g() and fast prefix sum of g()
 * - Calculate h(p^k) using the method described in the blog, generally its like this:
 *   => Expand f(p^k) = sum_{i = 0 to k}{g(p^(k-i)) * h(p^i)}
 *   => Separate the h(p^k) term and get its recurrence relation
 *   => Then subtract equations from h(p^k) to h(p^(k-1))
 * - Finally brute over all powerful numbers and get the result
 *
 * Total complexity: O(sqrt(n) * complexity of prefix sum of g())
 **/

const ll mod = 4179340454199820289;
inline ll mul(ll x, ll y)
{
	return __int128(x) * y % mod;
}
inline ll add(ll x, ll y)
{
	return (x += y) >= mod ? x - mod : x;
}
ll power(ll x, ll n)
{
	ll ans = 1;
	for (; n; n >>= 1, x = mul(x, x))
	{
		if (n & 1)
			ans = mul(ans, x);
	}
	return ans;
}

// sieve upto sqrt(n)
int spf[N];
vector<int> primes;
void sieve()
{
	for (int i = 2; i < N; i++)
	{
		if (spf[i] == 0)
			spf[i] = i, primes.push_back(i);
		int sz = primes.size();
		for (int j = 0; j < sz && i * primes[j] < N && primes[j] <= spf[i]; j++)
		{
			spf[i * primes[j]] = primes[j];
		}
	}
}

ll inv[60];

// g(x) = x
ll g_prefix_sum(ll n)
{ // return prefix sum of g()
	return mul(mul(n, n + 1), inv[2]);
}

// h(p^k) = -p^k / (k * (k - 1))
ll get_h(int p, int k, ll pk)
{ // return h(p^k), k >= 2
	return mod - mul(mul(pk, inv[k]), inv[k - 1]);
}

ll n;
// generate all powerful numbers and add up the results
// params: current prime index, current number generated, and h(m)
ll brute(int i, ll m, ll h)
{
	ll ans = mul(h, g_prefix_sum(n / m));
	ll lim = n / m;
	while (i < primes.size() and 1LL * primes[i] * primes[i] <= lim)
	{
		int k = 2;
		ll pk = 1LL * primes[i] * primes[i];
		while (pk <= lim)
		{
			ans = add(ans, brute(i + 1, m * pk, mul(h, get_h(primes[i], k, pk))));
			++k;
			pk *= primes[i];
		}
		++i;
	}
	return ans;
}

void solve()
{
	cin >> n;
	ll prefix_sum = brute(0, 1, 1);
	ll ans = mul(power(n, mod - 2), prefix_sum);
	cout << ans << '\n';
}

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	inv[1] = 1;
	for (int i = 2; i < 60; i++)
	{
		inv[i] = power(i, mod - 2);
	}
	sieve();

	int t = 1;
	cin >> t;
	while (t--)
	{
		solve();
	}
	return 0;
}
// https://vjudge.net/problem/HDU-7186

// Sieve Linear:

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9;

int spf[N];
vector<int> primes;
void sieve()
{
	for (int i = 2; i < N; i++)
	{
		if (spf[i] == 0)
			spf[i] = i, primes.push_back(i);
		int sz = primes.size();
		for (int j = 0; j < sz && i * primes[j] < N && primes[j] <= spf[i]; j++)
		{
			spf[i * primes[j]] = primes[j];
		}
	}
}

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	sieve();
	cout << primes.back() << '\n';
	return 0;
}

// Sieve upto 1e9:

#include <bits/stdc++.h>
using namespace std;

// credit: min_25
// takes 0.5s for n = 1e9
vector<int> sieve(const int N, const int Q = 17, const int L = 1 << 15)
{
	static const int rs[] = {1, 7, 11, 13, 17, 19, 23, 29};
	struct P
	{
		P(int p) : p(p) {}
		int p;
		int pos[8];
	};
	auto approx_prime_count = [](const int N) -> int
	{
		return N > 60184 ? N / (log(N) - 1.1)
						 : max(1., N / (log(N) - 1.11)) + 1;
	};

	const int v = sqrt(N), vv = sqrt(v);
	vector<bool> isp(v + 1, true);
	for (int i = 2; i <= vv; ++i)
		if (isp[i])
		{
			for (int j = i * i; j <= v; j += i)
				isp[j] = false;
		}

	const int rsize = approx_prime_count(N + 30);
	vector<int> primes = {2, 3, 5};
	int psize = 3;
	primes.resize(rsize);

	vector<P> sprimes;
	size_t pbeg = 0;
	int prod = 1;
	for (int p = 7; p <= v; ++p)
	{
		if (!isp[p])
			continue;
		if (p <= Q)
			prod *= p, ++pbeg, primes[psize++] = p;
		auto pp = P(p);
		for (int t = 0; t < 8; ++t)
		{
			int j = (p <= Q) ? p : p * p;
			while (j % 30 != rs[t])
				j += p << 1;
			pp.pos[t] = j / 30;
		}
		sprimes.push_back(pp);
	}

	vector<unsigned char> pre(prod, 0xFF);
	for (size_t pi = 0; pi < pbeg; ++pi)
	{
		auto pp = sprimes[pi];
		const int p = pp.p;
		for (int t = 0; t < 8; ++t)
		{
			const unsigned char m = ~(1 << t);
			for (int i = pp.pos[t]; i < prod; i += p)
				pre[i] &= m;
		}
	}

	const int block_size = (L + prod - 1) / prod * prod;
	vector<unsigned char> block(block_size);
	unsigned char *pblock = block.data();
	const int M = (N + 29) / 30;

	for (int beg = 0; beg < M; beg += block_size, pblock -= block_size)
	{
		int end = min(M, beg + block_size);
		for (int i = beg; i < end; i += prod)
		{
			copy(pre.begin(), pre.end(), pblock + i);
		}
		if (beg == 0)
			pblock[0] &= 0xFE;
		for (size_t pi = pbeg; pi < sprimes.size(); ++pi)
		{
			auto &pp = sprimes[pi];
			const int p = pp.p;
			for (int t = 0; t < 8; ++t)
			{
				int i = pp.pos[t];
				const unsigned char m = ~(1 << t);
				for (; i < end; i += p)
					pblock[i] &= m;
				pp.pos[t] = i;
			}
		}
		for (int i = beg; i < end; ++i)
		{
			for (int m = pblock[i]; m > 0; m &= m - 1)
			{
				primes[psize++] = i * 30 + rs[__builtin_ctz(m)];
			}
		}
	}
	assert(psize <= rsize);
	while (psize > 0 && primes[psize - 1] > N)
		--psize;
	primes.resize(psize);
	return primes;
}

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, a, b;
	cin >> n >> a >> b;
	auto primes = sieve(n);
	vector<int> ans;
	for (int i = b; i < primes.size() && primes[i] <= n; i += a)
		ans.push_back(primes[i]);
	cout << primes.size() << ' ' << ans.size() << '\n';
	for (auto x : ans)
		cout << x << ' ';
	cout << '\n';
	return 0;
}
// https://judge.yosupo.jp/problem/enumerate_primes