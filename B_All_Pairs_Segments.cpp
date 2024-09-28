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
    ll a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, m = 0, n = 0, q = 0;
    cin >> n >> q;
    vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    map<ll, ll> mp;
    for(i=0;i<n;++i){
        c = i * (n - i) + (n - i - 1);
        mp[c]++;
        if(i) {
            if(ar[i] - ar[i-1] - 1) {
                c = i * (n - i);
                mp[c] += (ar[i] - ar[i - 1] - 1);
            }
        }
    }
    while(q--) {
        cin >> a;
        auto it = mp.find(a);
        if(it!=mp.end())
            cout << it->second << ' ';
        else cout << 0 << ' ';
    }
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}