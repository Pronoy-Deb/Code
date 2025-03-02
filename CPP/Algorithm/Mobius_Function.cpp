// Complexity: O(sqrt(n))
// Formula: M(n) = 0 if n has a squared prime factor
// M(n) = 1 if n is a square-free positive integer with an even number of prime factors
// M(n) = -1 if n is a square-free positive integer with an odd number of prime factors

int mob(int64_t n) {
	int p = 0;
	if (~n & 1) {
		n >>= 1; ++p; if (~n & 1) return 0;
	}
	for (int64_t i = 3; i * i <= n; i += 2) {
		if (n % i == 0) {
			n /= i; ++p; if (n % i == 0) return 0;
		}
	}
	return (~p & 1) ? -1 : 1;
}

https://codeforces.com/contest/547/problem/C

#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 9;

int mb[N];
void mob() {
    mb[1] = 1;
    for (int i = 2; i < N; ++i) {
        mb[i]--;
        for (int j = i + i; j < N; j += i) {
            mb[j] -= mb[i];
        }
    }
}
bitset<N> vis;
vector<int> d[N];
int mul[N];
void add(int x, int k)
{
    for (auto y : d[x])
    {
        mul[y] += k;
    }
}
int query(int x)
{
    int ans = 0;
    for (auto y : d[x])
    {
        ans += mul[y] * mb[y];
    }
    return ans;
}
int a[N];
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    mob();
    for (int i = 1; i < N; i++)
    {
        if (mb[i])
        {
            for (int j = i; j < N; j += i)
                d[j].push_back(i);
        }
    }
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    int64_t ans = 0;
    while (q--)
    {
        int i;
        cin >> i;
        if (vis[i])
        {
            ans -= query(a[i]);
            ans += a[i] == 1;
            add(a[i], -1);
        }
        else
        {
            ans += query(a[i]);
            add(a[i], 1);
        }
        vis[i] ^= 1;
        cout << ans << '\n';
    }
    return 0;
}