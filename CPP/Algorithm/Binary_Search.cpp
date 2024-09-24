// Complexity: O(log(n))
// Returns: (0 / 1) whether the element is present or not
// -> Works only on monotonic (sorted) arrays
// Built-in: binary_search(v.begin(), v.end(), n);

bool bs(auto &v, auto val)
{
	long long lo = 0, hi = v.size() - 1;
	while (lo < hi)
	{
		long long mid = (hi + lo + 1) >> 1;
		if (v[mid] < val)
			lo = mid + 1;
		else
			hi = mid;
	}
	return (v[lo] == val);
}

// OR,

bool bs(auto &v, auto val)
{
	long long lo = 0, hi = v.size() - 1;
	while (lo <= hi)
	{
		long long mid = (hi + lo) >> 1;
		if (v[mid] == val)
			return true;
		if (v[mid] < val)
			lo = mid + 1;
		else
			hi = mid - 1;
	}
	return false;
}

// Fraction Binary Search:

#include <bits/stdc++.h>
using namespace std;

/**
Given a function f and n, finds the smallest fraction p / q in [0, 1] or [0,n]
such that f(p / q) is true, and p, q <= n.
Time: O(log(n))
**/
struct frac
{
	long long p, q;
};
bool f(frac x)
{
	return 6 + 8 * x.p >= 17 * x.q + 12;
}
frac fracBS(long long n)
{
	bool dir = 1, A = 1, B = 1;
	frac lo{0, 1}, hi{1, 0}; // Set hi to 1/0 to search within [0, n] and {1, 1} to search within [0, 1]
	if (f(lo))
		return lo;
	assert(f(hi)); // checking if any solution exists or not
	while (A || B)
	{
		long long adv = 0, step = 1; // move hi if dir, else lo
		for (int si = 0; step; (step *= 2) >>= si)
		{
			adv += step;
			frac mid{lo.p * adv + hi.p, lo.q * adv + hi.q};
			if (abs(mid.p) > n || mid.q > n || dir == !f(mid))
			{
				adv -= step;
				si = 2;
			}
		}
		hi.p += lo.p * adv;
		hi.q += lo.q * adv;
		dir = !dir;
		swap(lo, hi);
		A = B;
		B = !!adv;
	}
	return dir ? hi : lo;
}

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	frac ans = fracBS(10);
	cout << ans.p << ' ' << ans.q << '\n';
	return 0;
}
// Relevant Problem: https://codeforces.com/gym/102354/submission/69260720

// Parallel Binary Search:

#include <bits/stdc++.h>
using namespace std;

#define ll long long
namespace IO
{
#define in() ({ int a ; scanf("%d",&a); a; })
#define LL() ({ ll a ; scanf("%lld",&a); a; })
#define ULL() ({ ull a ; scanf("%llu",&a); a; })
#define DD() ({ double a; scanf("%lf", &a); a; })
#define CC() ({ char a ; scanf("%c",&a); a; })
#define pf1(a) printf("%d\n", a)
#define pf1ll(a) printf("%lld\n", a)
}
using namespace IO;
const int N = 3e5 + 9;
template <class T>
struct BIT
{
	// 1-indexed
	int sz;
	vector<T> t;

	void init(int n)
	{ // max size of array
		sz = n;
		t.assign(sz, 0);
	}

	T query(int idx)
	{
		T ans = 0;
		for (; idx >= 1; idx -= (idx & -idx))
			ans += t[idx];
		return ans;
	}

	void upd(int idx, T val)
	{
		if (idx <= 0)
			return;
		for (; idx < sz; idx += (idx & -idx))
			t[idx] += val;
	}

	void upd(int l, int r, T val)
	{
		upd(l, val);
		upd(r + 1, -val);
	}

	T query(int l, int r)
	{
		return query(r) - query(l - 1);
	}
};
vector<int> a[N];
int amount[N], want[N], st[N], en[N], l[N], r[N], ans[N];
vector<int> mid[N];
int32_t main()
{
	// freopen("meteors.in","r",stdin);
	// freopen("meteors.out","w",stdout);
	int n = in(), m = in();
	for (int i = 1; i <= m; i++)
	{
		int k = in();
		a[k].push_back(i);
	}
	for (int i = 1; i <= n; i++)
		want[i] = in();
	int q = in();
	for (int i = 1; i <= q; i++)
	{
		st[i] = in(), en[i] = in();
		amount[i] = in();
	}
	for (int i = 1; i <= n; i++)
		l[i] = 1, r[i] = q;
	for (int i = 1; i <= n; i++)
		mid[l[i] + r[i] >> 1].push_back(i);
	for (int i = 1; i <= n; i++)
		ans[i] = -1;
	while (1)
	{
		BIT<ll> t;
		t.init(m + 1);
		for (int i = 1; i <= q; i++)
		{
			if (st[i] <= en[i])
				t.upd(st[i], en[i], amount[i]);
			else
				t.upd(1, en[i], amount[i]), t.upd(st[i], m, amount[i]);
			for (auto x : mid[i])
			{
				ll cnt = 0;
				for (auto y : a[x])
				{
					cnt += t.query(y);
					if (cnt >= want[x])
						break;
				}
				if (cnt >= want[x])
					r[x] = i - 1, ans[x] = i;
				else
					l[x] = i + 1;
			}
		}
		for (int i = 1; i <= q; i++)
			mid[i].clear();
		int ok = 1;
		for (int i = 1; i <= n; i++)
			if (l[i] <= r[i])
				mid[l[i] + r[i] >> 1].push_back(i), ok = 0;
		if (ok)
			break;
	}
	for (int i = 1; i <= n; i++)
	{
		if (ans[i] == -1)
			puts("NIE");
		else
			pf1(ans[i]);
	}
	return 0;
}
// https://www.spoj.com/problems/METEORS/