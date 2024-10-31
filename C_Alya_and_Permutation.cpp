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
    if(n&1) {
        cout << n << '\n';
        cout << 2 << ' ' << 1;
        for (i = 3; i <= n; ++i) cout << ' ' << i;
    }
    else{
        a = (int)(log2(n)) + 1;
        cout << (1ll << a) - 1 << '\n';
        a--;
        b = (1ll << a) - 1;
        if(b==n-1) {
            cout << 2 << ' ' << 1;
            for (i = 3; i <= n; ++i) cout << ' ' << i;
        }
        else{
            for(i=1;i<=n;++i) {
                if(i==b or i==n-1) continue;
                cout << i << ' ';
            }
            cout << n - 1 << ' ' << b;
        }
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