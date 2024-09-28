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
    vector<ll> ar(n); for (i = 0; i < n; ++i) {
        cin >> ar[i];
        if(ar[i]>c){
            c = ar[i];
        }
    }
    vector<int> v;
    for(i=0;i<n;++i){
        if(ar[i]==c)
            v.push_back(i);
    }
    if(n&1){
        for(auto &e:v){
            if(~e&1){
                cout << c + (n / 2) + 1;
                cout << '\n';
                return;
            }
        }
    }
    cout << c + (n / 2);
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}