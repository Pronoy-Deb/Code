// Complexity: O(log(min(a, b)))
// Note: Used to determine whether there is an integer solution (x, y) to the equation ax + by = c. For example: 2x + 5y = 1 -> sol: (3, -1) or (-2, 1)

long long lde(long long a, long long b, long long c) {
	return !(c % gcd(a, b));
}
// Linear Diophantine Equation Three Variables with Nonnegative Solutions:

#include <bits/stdc++.h>
using namespace std;

using T = __int128;
T extended_euclid(T a, T b, T &x, T &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	T x1, y1;
	T d = extended_euclid(b, a % b, x1, y1);
	x = y1;
	y = x1 - y1 * (a / b);
	return d;
}
T inverse(T a, T m)
{
	T x, y;
	T g = extended_euclid(a, m, x, y);
	if (g != 1)
		return -1;
	return (x % m + m) % m;
}
T sumsq(T n)
{
	return n / 2 * ((n - 1) | 1);
}
// \sum_{i = 0}^{n - 1}{(a + d * i) / m}, O(log m)
T floor_sum(T a, T d, T m, T n)
{
	T res = d / m * sumsq(n) + a / m * n;
	d %= m;
	a %= m;
	if (!d)
		return res;
	T to = (n * d + a) / m;
	return res + (n - 1) * to - floor_sum(m - 1 - a, m, d, to);
}
// number of solutions to ax + by + cz = n s.t. x, y, z >= 0
// a, b, c >= 1, a, b and c are pairwise coprime
// O(log(max(a, b, c)));
T count(T a, T b, T c, T n)
{
	assert(__gcd(a, b) == 1);
	assert(__gcd(b, c) == 1);
	assert(__gcd(a, c) == 1);
	T b1p = (-n % a * inverse(b, a) % a + a) % a;
	if (b1p == 0)
		b1p = a;
	T c1p = (b % a * inverse(c, a) % a + a) % a;
	if (c1p == 0)
		c1p = a;
	T c2p = (-n % b * inverse(c, b) % b + b) % b;
	if (c2p == 0)
		c2p = b;
	T a2p = (c % b * inverse(a, b) % b + b) % b;
	if (a2p == 0)
		a2p = b;
	T a3p = (-n % c * inverse(a, c) % c + c) % c;
	if (a3p == 0)
		a3p = c;
	T b3p = (a % c * inverse(b, c) % c + c) % c;
	if (b3p == 0)
		b3p = c;
	T N1 = n * (n + a + b + c);
	N1 += c * b * b1p * (a + 1 - c1p * (b1p - 1));
	N1 += a * c * c2p * (b + 1 - a2p * (c2p - 1));
	N1 += b * a * a3p * (c + 1 - b3p * (a3p - 1));
	T ans = N1 / (2 * a * b * c);
	ans += floor_sum(0, c1p, a, b1p);
	ans += floor_sum(0, a2p, b, c2p);
	ans += floor_sum(0, b3p, c, a3p);
	ans -= 2;
	return ans;
}
// number of solutions to ax + by + cz = n s.t. x, y, z >= 0
// a, b, c >= 1
// O(log(max(a, b, c)));
// paper: https://cs.uwaterloo.ca/journals/JIS/VOL23/Binner/binner4.pdf
T yo(T a, T b, T c, T n)
{
	T g = __gcd(__gcd(a, b), c);
	if (n % g != 0)
		return 0;
	a /= g;
	b /= g;
	c /= g;
	n /= g;
	T g1 = __gcd(b, c), g2 = __gcd(c, a), g3 = __gcd(a, b);
	T a1 = inverse(a, g1), b2 = inverse(b, g2), c3 = inverse(c, g3);
	T n1 = n * a1 % g1, n2 = n * b2 % g2, n3 = n * c3 % g3;
	T A = a / g2 / g3, B = b / g3 / g1, C = c / g1 / g2;
	T N = (n - a * n1 - b * n2 - c * n3) / g1 / g2 / g3;
	return count(A, B, C, N);
}
T brute(T a, T b, T c, T n)
{
	T ans = 0;
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			for (int k = 0; k <= n; k++)
			{
				if (i * a + j * b + k * c == n)
					++ans;
			}
		}
	}
	return ans;
}
int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	for (int a = 1; a <= 5; a++)
	{
		for (int b = 1; b <= 5; b++)
		{
			for (int c = 1; c <= 5; c++)
			{
				for (int n = 1; n <= 50; n++)
				{
					T x = yo(a, b, c, n), y = brute(a, b, c, n);
					assert(x == y);
				}
			}
		}
	}
	return 0;
}

// Linear Diophantine Equation with Nonnegative Solutions:

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll inf = 1e18;

struct LDE
{ // sum(a[i] * x[i]) = k, x[i] >= 0
	int n, x;
	vector<ll> d;
	LDE() {}
	LDE(vector<int> a)
	{ // O(min(a[i]) * n * log(min(a[i])))
		n = a.size();
		priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
		x = *min_element(a.begin(), a.end());
		assert(x > 0);
		d.resize(x);
		fill(d.begin(), d.end(), inf);
		d[0] = 0;
		q.push(pair<ll, int>(0, 0));
		while (!q.empty())
		{
			pair<ll, int> nw = q.top();
			q.pop();
			int u = nw.second;
			ll val = nw.first;
			if (d[u] != val)
				continue;
			for (int i = 0; i < n; ++i)
			{
				ll tmp = val + a[i];
				int v = tmp % x;
				if (d[v] > tmp)
				{
					d[v] = tmp;
					q.push(pair<ll, int>(tmp, v));
				}
			}
		}
	}
	bool can(ll k)
	{ // if a solution exists
		return d[k % x] <= k;
	}
	ll count(ll l, ll r)
	{ // count of l <= k <= r s.t. solution for k exists
		ll ans = 0;
		for (int i = 0; i < x; i++)
		{ // d[i], d[i] + x, d[i] + 2 * x, ... are achievable
			ans += d[i] <= r ? (r - d[i]) / x + 1 : 0;
			ans -= d[i] <= l - 1 ? (l - 1 - d[i]) / x + 1 : 0;
		}
		return ans;
	}
};
int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	ll l, r;
	cin >> n >> l >> r;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	LDE t(a);
	cout << t.count(l, r) << '\n';
	return 0;
}
// https://www.lydsy.com/JudgeOnline/problem.php?id=2118
// https://codeforces.com/blog/entry/71230?#comment-556761

// Linear Diophantine Equation with Two Variables:

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
ll extended_euclid(ll a, ll b, ll &x, ll &y)
{
	ll xx = y = 0;
	ll yy = x = 1;
	while (b)
	{
		ll q = a / b;
		ll t = b;
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
// a*x+b*y=c. returns valid x and y if possible.
// all solutions are of the form (x0 + k * b / g, y0 - k * b / g)
bool find_any_solution(ll a, ll b, ll c, ll &x0, ll &y0, ll &g)
{
	if (a == 0 and b == 0)
	{
		if (c)
			return false;
		x0 = y0 = g = 0;
		return true;
	}
	g = extended_euclid(abs(a), abs(b), x0, y0);
	if (c % g != 0)
		return false;
	x0 *= c / g;
	y0 *= c / g;
	if (a < 0)
		x0 *= -1;
	if (b < 0)
		y0 *= -1;
	return true;
}
void shift_solution(ll &x, ll &y, ll a, ll b, ll cnt)
{
	x += cnt * b;
	y -= cnt * a;
}
// returns the number of solutions where x is in the range[minx, maxx] and y is in the range[miny, maxy]
ll find_all_solutions(ll a, ll b, ll c, ll minx, ll maxx, ll miny, ll maxy)
{
	ll x, y, g;
	if (find_any_solution(a, b, c, x, y, g) == 0)
		return 0;
	if (a == 0 and b == 0)
	{
		assert(c == 0);
		return 1LL * (maxx - minx + 1) * (maxy - miny + 1);
	}
	if (a == 0)
	{
		return (maxx - minx + 1) * (miny <= c / b and c / b <= maxy);
	}
	if (b == 0)
	{
		return (maxy - miny + 1) * (minx <= c / a and c / a <= maxx);
	}
	a /= g, b /= g;
	ll sign_a = a > 0 ? +1 : -1;
	ll sign_b = b > 0 ? +1 : -1;
	shift_solution(x, y, a, b, (minx - x) / b);
	if (x < minx)
		shift_solution(x, y, a, b, sign_b);
	if (x > maxx)
		return 0;
	ll lx1 = x;
	shift_solution(x, y, a, b, (maxx - x) / b);
	if (x > maxx)
		shift_solution(x, y, a, b, -sign_b);
	ll rx1 = x;
	shift_solution(x, y, a, b, -(miny - y) / a);
	if (y < miny)
		shift_solution(x, y, a, b, -sign_a);
	if (y > maxy)
		return 0;
	ll lx2 = x;
	shift_solution(x, y, a, b, -(maxy - y) / a);
	if (y > maxy)
		shift_solution(x, y, a, b, sign_a);
	ll rx2 = x;
	if (lx2 > rx2)
		swap(lx2, rx2);
	ll lx = max(lx1, lx2);
	ll rx = min(rx1, rx2);
	if (lx > rx)
		return 0;
	return (rx - lx) / abs(b) + 1;
}

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t, cs = 0;
	cin >> t;
	while (t--)
	{
		ll a, b, c, x1, x2, y1, y2;
		cin >> a >> b >> c >> x1 >> x2 >> y1 >> y2;
		cout << "Case " << ++cs << ": " << find_all_solutions(a, b, -c, x1, x2, y1, y2) << '\n';
	}
	return 0;
}
// https://lightoj.com/problem/solutions-to-an-equation

// Linear Diophantine With N Unknowns and Two Equations:

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/**
given are a[i], b[i], p and q:
sum(x[i] * a[i]) = p --- (i)
sum(x[i] * b[i]) = q --- (ii)
x[i]s can only be integers.

does a solution exist?
**/
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
ll a, b, coeff; // possible points that can be generated are of the form (a * m, b * m + k * coeff)
// add (a[i], b[i])
void add(ll c, ll d)
{
	if (c == 0 and d == 0)
		return;
	if (a == 0 and b == 0)
	{
		a = c;
		b = d;
		return;
	}
	ll x0, y0;
	// a * x0 + c * y0 = m * gcd(a, c)
	// all solutions are of the form (x0 + k * (c / g), y0 - k * (a / g))
	ll g = extended_euclid(a, c, x0, y0);
	// replace (x, y) to the equation b * x + d * y = z
	ll tmp_m = b * x0 + d * y0;
	ll tmp_coeff = abs(b * (c / g) - d * (a / g));
	coeff = __gcd(coeff, tmp_coeff);
	a = g;
	b = tmp_m % coeff;
}
// check if solution exists for some (p, q)
bool can(ll x, ll y)
{
	if (x == 0 and y == 0)
		return true;
	if (coeff == 0)
	{
		if (a == 0 or x % a)
			return false;
		if (b == 0 or y % b)
			return false;
		return x / a == y / b;
	}
	if (a == 0 or x % a)
		return false;
	return (y - (x / a) * b) % coeff == 0;
}
int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t, cs = 0;
	cin >> t;
	while (t--)
	{
		int q;
		cin >> q;
		a = b = coeff = 0;
		ll ans = 0;
		while (q--)
		{
			int ty;
			cin >> ty;
			if (ty == 1)
			{
				ll c, d;
				cin >> c >> d;
				add(c, d);
			}
			else
			{
				ll x, y, w;
				cin >> x >> y >> w;
				if (can(x, y))
				{
					ans += w;
				}
			}
		}
		cout << "Case #" << ++cs << ": " << ans << '\n';
	}
	return 0;
}
// https://codeforces.com/gym/102769/problem/I