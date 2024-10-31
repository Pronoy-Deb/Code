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
    ll cnt[n];
    vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i];
        cnt[i] = ar[i];
    }
    cout << ar[0] << ' ';
    for(i=0;i<n-1;++i){
        c = 0;
        while(ar[i]%2==0) {
            ar[i]>>=1;
            c++;
        }
        d += ar[i]; d %= M;
        if(ar[i] < cnt[i+1]) {
            while (c--) cnt[i + 1] = (cnt[i + 1] << 1) % M;
        }
        cout << (d + cnt[i + 1]) % M << ' ';
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