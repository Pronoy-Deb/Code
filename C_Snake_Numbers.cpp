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

long long bex(long long base, long long pow = M - 2) {
    long long ans = 1;
    while (pow) {
        if (pow & 1) ans = (ans * base);
        base = (base * base); pow >>= 1;
    }
    return ans;
}

void test(int32_t tc) {
    string l, r; cin >> l, r;
    // vector<ll> ar(n); for (int i = 0; i < n; ++i) { cin >> ar[i]; }
    int d1 = l.size(), d2 = r.size();
    ll ans = 0, c = 0; int f = r[0] - '0';
    int d = 2;
    while (d < d2) {
        for (int i = 1; i < 10; ++i) {
            c += bex(i, d - 1);
        }
        ++d;
    }
    for (int i = 1; i < f; ++i) {
        c += bex(i, d2 - 1);
    }
    vector<int> v;
    for (int i = 1; i < d2; ++i) {
        v.push_back(min(f - 1, r[i] - '0') + 1);
    }
    for (int i = 0; i < v.size() - 1; ++i) {
        
    }
    // while (d1)

    cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}