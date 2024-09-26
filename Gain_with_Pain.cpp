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
    cin >> n;
    // vector<array<ll, 3>> ar[n]; for (i = 0; i < n; ++i) { cin >> ar[j]; }
    int ar[n][5][3];
    bool ck = 1; int ar1[] = {2, 2, 2, 1, 3 };
    for(i=0;i<n;++i) {
        for(k=0;k<5;++k){
            for(j=0;j<3;++j) cin>>ar[i][k][j];;
        }
    }
    for(i=0;i<n;++i) {
        for(k=0;k<5;++k){
            if(ar[i][k][0] != ar1[k]) {
                ck = 0; break;
            }
        }
    }
    for(i=0;i<n;++i) {
        for(k=0;k<5;++k){
            if(ar[i][k][1] != 3) {
                ck = 0; break;
            }
        }
    }
    for(i=0;i<n;++i) {
        for(k=0;k<5;++k){
            if(ar[i][k][2] != 10) {
                ck = 0; break;
            }
        }
    }
    cout << (ck ? "Consistent" : "Inconsistent") << '\n';
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}