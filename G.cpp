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
const ll M = 1000267129, N = 2e5 + 5;

bool ok(ll i, ll j) {
    set<int> st;
    while(i) {
        st.insert(i%10);
        i /= 10;
    }
    while(j) {
        if(st.find(j%10) != st.end()) return true;
        j /= 10;
    }
    return false;
}

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    // cin >> n;
    // vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    for(i=1;i<69696;++i) {
        for(j=i+1;j<69696;++j) {
            if(ok(i, j)) c++;
            c %= M;
        }
    }
    cout << c;
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}