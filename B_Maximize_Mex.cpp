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
    cin >> n >> k;
    // vector<ll> ar(n);
    map<ll, int> mp;
    for (i = 0; i < n; ++i) { cin >> a; ++mp[a]; }
    if(mp.find(0) == mp.end()) {
        cout << 0 << '\n'; return;
    }
    for(i=1;i<N;++i) {
        auto it = mp.find(i);
        if(it==mp.end()) {
            bool ck = 1;
            for(auto &[f, s] : mp) {
                if(f > i) break;
                if(s > 1 and (i - f) % k == 0) {
                    if(s == 2) mp.erase(f);
                    else --mp[f];
                    ck = 0;
                    break;
                }
            }
            if(ck) {
                cout << i << '\n'; return;
            }
        }
        else if (it -> second == 1) mp.erase(i);
    }
    cout << i;
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}