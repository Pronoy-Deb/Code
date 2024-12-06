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
    // cin >> n;
    // vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    string s; cin >> s;
    n = s.size();
    for(i=0;i<n-1;++i) {
        if(s[i] == s[i+1]) {
            cout << s[i] << s[i+1] <<'\n'; return;
        }
    }
    // bool ok = 1;
    // for (i=0;i+2<n;i+=2) {
    //     if(s[i]!=s[i+2]){
    //         ok = 0; break;
    //     }
    // }
    // if (ok) {
    //     for (i=1;i+2<n;i+=2) {
    //         if(s[i]!=s[i+2]){
    //             ok = 0; break;
    //         }
    //     }
    // }
    // if(ok) {
    //     cout << -1<<'\n'; return;
    // }
    for(i=0;i<n-2;++i) {
        if(s[i] != s[i+1] and s[i] != s[i+2] and s[i+1]!=s[i+2]) {
            cout << s[i] << s[i+1] <<s[i+2]<<'\n'; return;
        }
    }
    // if(n>=4) cout << s.substr(0, 4);
    cout << -1;
    // else cout << -1;
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}