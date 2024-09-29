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
const ll M = 1e9 + 7, N = 2e5 + 5;

const int L = 21;
int tab[N][L], ar[N], n;
void make() {
	for (int i = 1; i <= n; ++i) tab[i][0] = ar[i];
	for (int k = 1; k < L; ++k) {
		for (int i = 1; i + (1 << k) - 1 <= n; ++i) {
			tab[i][k] = tab[i][k - 1]+tab[i + (1 << (k - 1))][k - 1];
		}
	}
}
int get(int l, int r) {
	int k = 31 - __builtin_clz(r - l + 1);
	return tab[l][k]+tab[r - (1 << k) + 1][k];
}

void test(int tc) {
    ll o = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    // cin >> n;
    // vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
	cin >> n >> q;
	for (i = 1; i <= n; ++i) cin >> ar[i];
	make();
	while (q--) {
		int l, r; cin >> l >> r;
		cout << get(l, r) << '\n';
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