#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ll long long
#define pe(c) for (auto &e : c) cout << e << ' '
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const ll M = 1e9 + 7, N = 2e5 + 5;

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n;
    // vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    if(~n&1) {
        for (i = 0; i < (n >> 1); ++i) cout << i + 1 << ' ' << i + 1 << ' ';
    }
    else {
        if (n < 27) cout << -1;
        else {
            vector<int> v(n);
            v[0] = 1;
            v[9] = 1;
            v[25] = 1;
            v[22] = 2;
            v[26] = 2;
            c = 3;
            for (i = 0; i < n;++i) {
                if(!v[i]) {
                    v[i] = c;
                    d++;
                    if (~d & 1) c++;
                }
            }
            pe(v);
        }
    }
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}