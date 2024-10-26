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
const ll M = 1e9 + 7, N = 4e3 + 5;

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    // cin >> n;
    // vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    for(i=1;i<N;++i) {
        set<tuple<ll, ll, ll>> st;
        for(j=1;j<N;++j) {
            for(k=1;k<N;++k) {
                ll ar[3] = {i, j, k};
                sort(ar, ar + 3);
                if(ar[0] == i or ar[1] == i) {
                    if(ar[0]*ar[0] + ar[1]*ar[1] == ar[2]*ar[2]) {
                        st.insert({ar[0], ar[1], ar[2]});
                    }
                }
            }
        }
        if(st.size()==47547) {
            cout << i;
            cout << '\n';
            return;
        }
    }
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}