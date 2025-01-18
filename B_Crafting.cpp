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
    vector<ll> ar1(n); for (int i = 0; i < n; ++i) { cin >> ar1[i]; }
    int c = 0, in = -1;
    for (int i = 0; i < n; ++i) {
        if (ar[i] < ar1[i]) {
            ++c; if (in == -1) in = i;
        }
        if (c == 2) {
            cout << "NO\n";
            return;
        }
    }
    if (!c) cout << "YES\n";
    else {
        for (int i = 0; i < n; ++i) {
            if (i == in) continue;
            ar[i] -= (ar1[in] - ar[in]);
            if (ar[i] < ar1[i]) {
                ck(in, ar);
                cout << "NO\n";
                return;
            }
        }
        cout << "YES\n";
    }
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}