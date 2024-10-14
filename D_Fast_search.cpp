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
int lb(auto &v, long long val) {
	int i = -1, n = v.size();
	for (int j = n; j; j >>= 1) {
		while (i + j < n && v[i + j] < val) i += j;
	}
	return i + 1;
}
int ub(auto &v, long long val) {
	int i = -1, n = v.size();
    for (int j = n; j; j >>= 1) {
        while (i + j < n && v[i + j] <= val) i += j;
    }
    return i + 1;
}
void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n;
    vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    sort(ar.begin(), ar.end());
    cin >> q;
    while (q--) {
        cin >> a >> b;
        auto [l, r] = equal_range(ar.begin(), ar.end(), b);
        cout << r - l << ' ';
    }
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}