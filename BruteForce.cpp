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

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n;
    vector<ll> ar(n);
    for (i = 0; i < n; ++i) { cin >> ar[i]; }
    for (i = 0; i < n; ++i) {
        for (j=0;j<n-1;++j) {
            if (ar[j] - ar[j+1] == 1) swap(ar[j], ar[j + 1]);
        }
    }
    // pe(ar);
    for(i=0;i<n-1;++i) {
        if(ar[i+1] != ar[i]+1) {
            ps(0);
            return;
        }
    }
    ps(1);
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}