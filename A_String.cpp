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
    // ll n; cin >> n;
    // vector<ll> ar(n); for (int i = 0; i < n; ++i) { cin >> ar[i]; }
    string s; cin >> s;
    cout << count(s.begin(), s.end(), '1');
    cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}