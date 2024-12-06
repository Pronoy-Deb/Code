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

void test(int32_t tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n;
    vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; c += ar[i]; }
    if (c % n) {
        ps(0); return;
    }
    a = c / n;
    for (i=1;i < n-1;++i) {
        if(ar[i-1] < a) {
            b = abs(ar[i-1] - a);
            ar[i-1] += b;
            ar[i+1] -= b;
        }
        else if(ar[i-1] > a) {
            b = abs(ar[i-1] - a);
            ar[i-1] -= b;
            ar[i+1] += b;
        }
    }
    ck(ar);
    if (ar[n-1] != a or ar[n-2] != a or ar[n-3] != a) {
        ps(0); return;
    }
    ps(1);
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}