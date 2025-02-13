#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ll int64_t
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const int M = 1e9 + 7, N = 2e5 + 5;

map<vector<ll>, ll> dp;
ll rec(vector<ll> &ar) {
    int n = ar.size();
    if (n == 1) return ar[0];
    auto it = dp.find(ar);
    if (it != dp.end()) return it -> second;
    vector<ll> v(n - 1); ll ans = ar[0];
    for (int i = 0; i < n - 1; ++i) v[i] = ar[i + 1] - ar[i], ans += ar[i + 1];
    ans = max(ans, rec(v));
    auto ar1 = ar;
    reverse(ar.begin(), ar.end());
    for (int i = 0; i < n - 1; ++i) v[i] = ar[i + 1] - ar[i];
    ans = max(ans, rec(v));
    return dp[ar1] = ans;
}

void test(int32_t tc) {
    ll n; cin >> n;
    vector<ll> ar(n); for (int i = 0; i < n; ++i) { cin >> ar[i]; }
    cout << rec(ar);
    cout << '\n';
    dp.clear();
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}