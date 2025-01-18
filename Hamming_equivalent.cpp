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
    ll n; cin >> n; map<int, int> in;
    vector<ll> ar(n); for (int i = 0; i < n; ++i) { cin >> ar[i]; in[ar[i]] = i; }
    for (int i = 0; i < n; ++i) {
        if (ar[i] == i + 1) continue;
        if (__builtin_popcount(ar[i]) == __builtin_popcount(i + 1)) swap(ar[i], ar[in[i + 1]]);
        else {
            ps(0); return;
        }
    }
    ps(1);
    // cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}