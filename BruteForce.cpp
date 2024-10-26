#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ll long long
#define pe(c) for (auto &e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const ll M = 1e9 + 7, N = 2e5 + 5;
int n; map<pair<vector<ll>, int>, int> mp;
int rec(auto &ar, int i) {
    if (i == (n>>1)) {
        int c = 0;
        for (int i = 0; i < n - 1; ++i) c += (ar[i] == ar[i + 1]);
        return c;
    }
    if (mp.count({ar, i})) return mp[{ar, i}];
    int c = M;
    if(ar[i] != ar[n-i-1]) {
        swap(ar[i], ar[n - i - 1]);
        c = rec(ar, i + 1);
        swap(ar[i], ar[n - i - 1]);
    }
    c = min(c, rec(ar, i + 1));
    return mp[{ar, i}] = c;
}

void test(int tc) {
    ll o = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n;
    vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    cout << rec(ar, 0) << '\n';
    mp.clear();
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}