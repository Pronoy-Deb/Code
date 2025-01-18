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
    ll n, k; cin >> n >> k; int fre[22]{};
    vector<ll> ar(n); for (int i = 0; i < n; ++i) { cin >> ar[i]; fre[ar[i]]++; }
    int mx = 0;
    for (auto e : fre) mx=max(mx, e);
    if (mx == fre[k]) {
        cout << 0 << '\n'; return;
    }
    for (int i = 0; i < n - 1; ++i) {
        fre[ar[i]]--; int maxi = 0;
        for (auto e : fre) maxi = max(maxi, e);
        if (maxi == fre[k]) {
            cout << 1 << '\n'; return;
        }
    }
    fre[ar[n - 1]]--;
    for (auto e : ar) fre[e]++;
    for (int i = n - 1; i > 1; --i) {
        fre[ar[i]]--; int maxi = 0;
        for (auto e : fre) maxi = max(maxi, e);
        if (maxi == fre[k]) {
            cout << 1 << '\n'; return;
        }
    }
    cout << 2 << '\n';
    // cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}