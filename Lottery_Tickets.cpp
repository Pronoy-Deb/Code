#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ll long long
#define pe(c) for (auto e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const ll M = 1e9 + 7, N = 1e6;

void test(int32_t tc) {
    ll n; cin >> n;
    vector<ll> ar(n); for (int i = 0; i < n; ++i) { cin >> ar[i]; }
    sort(ar.begin() + 1, ar.end());
    int l = upper_bound(ar.begin() + 1, ar.end(), ar[0]) - ar.begin();
    if (l == 1) {
        cout << ((ar[0] + ar[1]) >> 1);
    }
    else if (l == n) {
        int a = (ar[0] + ar[n - 1] + 1) >> 1;
        cout << N - a + 1;
    }
    else {
        int a = (ar[0] + ar[l - 1] + 1) >> 1;
        int b = (ar[0] + ar[l]) >> 1;
        cout << b - a + 1;
    }
    cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}