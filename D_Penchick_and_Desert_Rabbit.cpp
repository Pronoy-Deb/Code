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
const ll M = 1e9 + 7, N = 5e5 + 5;
const int L = 21;
long long tab[N][L], tab1[N][L], ar[N], n;
void make() {
	for (int i = 1; i <= n; ++i) tab[i][0] = tab1[i][0] = ar[i];
	for (int k = 1; k < L; ++k) {
		for (int i = 1; i + (1 << k) - 1 <= n; ++i) {
			tab[i][k] = max(tab[i][k - 1], tab[i + (1 << (k - 1))][k - 1]);
			tab1[i][k] = min(tab1[i][k - 1], tab1[i + (1 << (k - 1))][k - 1]);
        }
	}
}
int mx(int l, int r) {
    if (l > r) return -M;
	int k = 31 - __builtin_clz(r - l + 1);
	return max(tab[l][k], tab[r - (1 << k) + 1][k]);
}
int mn(int l, int r) {
    if (l > r) return M;
	int k = 31 - __builtin_clz(r - l + 1);
	return min(tab1[l][k], tab1[r - (1 << k) + 1][k]);
}
void test(int tc) {
    ll o = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n;
    set<int> st[n + 5];
    for (i = 1; i <= n; ++i) { cin >> ar[i]; st[ar[i]].insert(i); }
    make();
    for (i = 1; i <= n; ++i) {
        c = ar[i];
        
        bool ck = 1;
        a = i, b = n+1;
        while(a+1<b-1) {
            if(ck) {
                d = mn(a+1, b-1);
                c = max(c, d);
                // ck(tc, d, st[d]);
                if(!st[d].empty()) {
                    b = *prev(st[d].end());
                    st[d].erase(--st[d].end());
                }
            }
            else {
                d = mx(a + 1, b - 1);
                c = max(c, d);
                // ck(tc, d, st[d]);
                if(!st[d].empty()) {
                    a = *(st[d].begin());
                    st[d].erase(st[d].begin());
                }
            }
            ck = !ck;
        }
        if (a + 1 == b - 1 and a + 1 <= n and a + 1 > 0) c = max(c, ar[a + 1]);
        cout << c << ' ';
    }
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}