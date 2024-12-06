#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ll long long
#define pe(c) for (auto &e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const ll M = 1e9 + 7, N = 2e5 + 5;

long long m;
long long gp(long long a, long long n) {
	if (n == 0) return 0;
	if (n & 1) return (1 + (a * gp(a, n - 1)) % m) % m;
	return (gp((a * a) % m, n >> 1) * (a + 1)) % m;
}
void test(int32_t tc) {
    ll n = 0, mm = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> a >> b >> m;
    // vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    cout << gp(a, b);
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}