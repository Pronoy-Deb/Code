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
    // vector<ll> ar(n); for (int i = 0; i < n; ++i) { cin >> ar[i]; }
    string s; cin >> s;
    int c = n;
    for (int i = 1; i < n; ++i) {
        if (s[i] != s[i - 1]) --c;
    }
    int d = n; char prev = s.front();
    for (int i = 1; i < n; ++i) {
        if (s[i] != prev) --d;
        else prev = s[i];
    }
    int a = n; prev = s.back();
    for (int i = n - 2; i >= 0; --i) {
        if (s[i] != prev) --a;
        else prev = s[i];
    }
    int b = n;
    for (int i = n - 2; i >= 0; --i) {
        if (s[i] != s[i + 1]) --b;
    }
    cout << min({c, d, a, b}) << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}