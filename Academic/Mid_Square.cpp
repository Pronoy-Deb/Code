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

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n;
    // vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    while (n) {
        cout << tc - 1 << ' ' << n << ' ';
        if (tc == 1) cout << " -- ";
        else cout << n / 10000.0 << ' ';
        n *= n; string s = to_string(n);
        while (s.size() < 8) s = '0' + s;
        cout << s << '\n';
        s.erase(6); s.erase(s.begin()); s.erase(s.begin());
        n = stoi(s); ++tc;
    }
    cout << tc - 1 << ' ' << 0 << ' ' << 0 << ' ' << "00000000" << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}