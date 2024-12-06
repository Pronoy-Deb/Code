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
const int L = 21;
long long tab[N][L], ar[N];
void make() {
	for (int i = 1; i < N; ++i) tab[i][0] = ar[i];
	for (int k = 1; k < L; ++k) {
		for (int i = 1; i + (1 << k) - 1 < N; ++i)
			tab[i][k] = min(tab[i][k - 1], tab[i + (1 << (k - 1))][k - 1]);
	}
}
int get(int l, int r) {
    if (l > r) return LLONG_MAX;
	int k = 31 - __builtin_clz(r - l + 1);
	return min(tab[l][k], tab[r - (1 << k) + 1][k]);
}
void test(int32_t tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> m;
    fill(ar, ar + N, M);
    vector<ll> arr(n); for (i = 0; i < n; ++i) { cin >> arr[i];
    if(ar[arr[i]] == M) ar[arr[i]] = i + 1; }
    make();
    // pn(ar, 10);
    while(m--) {
        cin >> a;
        int ans = get(1, a);
        if (ans == M) cout << -1; else cout << ans;
        cout << '\n';
    }
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}