#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pe(c) for (auto &e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
const ll M = 1e9 + 7, N = 2e5 + 5;

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n;
    // vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    map<string, int> mp;
    while (n--) {
        string s; cin >> s;
        mp[s]++;
    }
    cin >> q;
    while (q--) {
        c = 0; string r(10, 'z');
        string s; cin >> s; a = s.size();
        for (auto &[e, f] : mp) {
            if (e.size() < a) continue;
            if (e.substr(0, a) == s) {
                if (mp[e] == c) r = min(r, e);
                else if (mp[e] > c) {
                    c = f; r = e;
                }
            }
        }
        if (!c) cout << "-1\n";
        else cout << r << ' ' << c << '\n';
    }
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}