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
const ll M = 1e9 + 7, N = 1e5;
string str(ll n, int sz) {
    string s;
    while (n) {
        s += ((n % 10) + 48); n /= 10;
    }
    while (s.size() < sz) s += '0';
    reverse(s.begin(), s.end()); return s;
}
void test(int tc) {
    ll a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, m = 0, n = 0, q = 0;
    // cin >> n;
    // vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    string s;
    cin >> s; n = s.size();
    for(i=0;i<N;++i) {
        string r = str(i, n);
        if(r.size() > n) break;
        bool ck = 1;
        for(j=0;j<n;++j) {
            if(s[j] != '?' && s[j] != r[j]) {
                ck = 0; break;
            }
        }
        a = __builtin_popcountll(i);
        if(ck and a>=c) {
            c = a;
            d = max(d, i);
        }
    }
    cout << d;
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}