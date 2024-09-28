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
#include <ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<class T> using oset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

void test(int tc) {
    ll a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, m = 0, n = 0, q = 0;
    cin >> n >> k;
    j = k;
    vector<ll> ar(n);
    oset<ll> st;
    for (i = 0; i < n; ++i) {
        cin >> a;
        st.insert(a);
        c = max(c, a);
    }
    oset<ll> st1 = st;
    pa(st);
    ll lo=0, hi=n;
    while(lo<=hi){
        m = (lo + hi) >> 1;
        if(st.size()<m) {
            hi = m - 1;
            continue;
        }
        d = c;
        j = k;
        while(!st.empty() and j>=0) {
            a = *st.begin();
            d -= a;
            if(d<=0) break;
            vector<ll> v, v1;
            b = m;
            for(auto &e : st) {
                if(b--) {
                    v1.push_back(e);
                    if(e-a) v.push_back(e - a);
                }
                else
                    break;
            }
            for(auto &e : v1) {
                st.erase(st.upper_bound(e));
            }
            for(auto &e : v) {
                st.insert(e);
            }
            if(!st.empty()) {
                while(st.size()!=m and j>=0) {
                    a = *st.begin();
                    st.insert(a);
                    j -= a;
                }
            }
        }
        pa(st);
        if(d<=0 and j>=0){
            q = m;
            lo = m + 1;
        }
        else hi = m - 1;
        st = st1;
    }
    cout << q;
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}