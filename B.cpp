#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
#define pc cout << "Case " << tc << ": "
#ifdef LOCAL
#include "def.h"
#else
#define ck(...) 
#endif
const ll M = 1e9 + 7, N = 2e5 + 5;

void test(int tc) {
    ll a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, m = 0, n = 0, q = 0;
    cin >> n >> k;
    map<ll, ll> mp;
    for (i = 0; i < n; ++i) { 
        cin >> a;
        mp[a]++;
    }
    multiset<ll, greater<>> st;
    for(auto [f,s] : mp)
        st.insert(s);
    ck(st);
    a = *st.begin();
    st.erase(st.begin());
    for (i = 0; i < k; ++i){
        // if((!st.empty() and a >= *st.begin()) or (st.empty() and a)) {
        for (j = i; j < n and a > 0; j += k){
            c++;
            a--;
        }
        // }
        ck(i, c, a);
        // if (!st.empty() and a < *st.begin()) {
        b = 0;
        for (j = i + 1; j < n; j+=k)
            b++;
        if (!st.empty() and (b ))
            {
                a = *st.begin();
                st.erase(st.begin());
            }
        // else if(st.empty() and !a)
        //     break;
    }
    cout << n - c;
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit|cin.badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}