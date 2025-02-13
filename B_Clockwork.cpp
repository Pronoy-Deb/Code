#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ll long long
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const int M = 1e9 + 7, N = 2e5 + 5;

void test(int32_t tc) {
    ll n; cin >> n;
    bool ok = true;
    for (int i = 1; i <= n; ++i) {
        int a; cin >> a;
        int l = (i - 1) * 2, r = (n - i) * 2, mx = max(l, r);
        if (a <= mx) {
            ok = false;
        }
    }
    ps(ok);
    // cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}