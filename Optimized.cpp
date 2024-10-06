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
const ll M = 1e9 + 7, N = 1e7 + 200;
bitset<N> ip; vector<long long> pri;
void pre() {
	pri.push_back(2);
	for (long long i = 3; i < N; i += 2) {
		if (!ip[i]) {
			if(i>=5 and !ip[i - 2]) pri.push_back(i - 2);
			for (long long j = i * i; j < N; j += (i << 1)) ip[j] = 1;
		}
	}
}
void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cout << "Case #" << tc << ": ";
    cin >> n;
    if(n<=4) {
        cout << 0 << '\n'; return;
    }
    // vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    a = lower_bound(pri.begin(), pri.end(), n - 1) - pri.begin();
    // if(pri[a] == n) a--;
    cout << a;
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    pre();
    // pn(pri, 20);
    // ck(pri);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}