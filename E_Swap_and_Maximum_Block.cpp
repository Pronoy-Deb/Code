#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pe(c) for (auto &e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
const ll M = 1e9 + 7, N = 20;
long long ar[N], n;
bool vis[N];
long long kad() {
	long long mx = ar[0], res = 0;
	for (int i = 0; i < n; ++i) {
		res += ar[i]; mx = max(mx, res); res = max(res, 0ll);
	}
	return mx;
}
void test(int tc) {
    ll a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, m = 0, n = 0, q = 0;
    cin >> n;
    for (i = 0; i < n; ++i) { cin >> ar[i]; }
    cin >> q;
    while(q--) {
        cin >> a;
        for(i=0; i + (1<<a) < n; ++i) {
            if(!vis[i]) {
                swap(ar[i], ar[i + (1<<a)]);
                vis[i] = vis[i + (1<<a)] = 1;
            }
        }
        cout << kad() << '\n';
    }
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}