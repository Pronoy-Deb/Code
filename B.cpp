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
    vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    sort(ar.begin(), ar.end());
    bool ok = 1;
    for(i=1;i<n;++i) {
        if(ar[i]%ar[0]) {
            ok = 0;
            break;
        }
    }
    if(ok) {
        cout << ar[0] << '\n';
        return;
    }
    a = ar[0];
    b = ar[1];
    while(a>1) {
        b = (b - 1) >> 1;
        if(b>=a) {
            cout << a << '\n';
            return;
        }
        swap(a, b);
    }
    cout << 1;
    // while(a>1) {
    //     for(i=1;i<n;++i) {
    //         if(((ar[i]-1) >> 1) < a){
    //             ok = false;
    //             break;
    //         }
    //     }
    //     if(ok or a==1) {
    //         cout << a << '\n';
    //         return;
    //     }
    //     a = (a-1) >> 1;
    // }
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}