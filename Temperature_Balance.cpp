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
const ll M = 1e9 + 7, N = 2e5 + 5;

void test(int32_t tc) {
    ll n; cin >> n;
    vector<ll> ar(n); for (int i = 0; i < n; ++i) { cin >> ar[i]; }
    if (abs(ar[0]) < abs(ar[n - 1])) {
        ll c = 0;
        for (int i = 1; i < n; ++i) {
            ar[i] += ar[i - 1];
            c += abs(ar[i - 1]);
        }
        // pa(ar);
        cout << c;
    }
    else {
        ll c = 0;
        for (int i = n - 2; i >= 0; --i) {
            ar[i] += ar[i + 1];
            c += abs(ar[i + 1]);
        }
        // pa(ar);
        cout << c;
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