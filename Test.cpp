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

auto nge(auto &v) {
    int n = v.size();
    vector<ll> ng(n);

    stack<ll> sk;
    for (int i=0;i<n;++i) {
        while(!sk.empty() and v[i]>v[sk.top()]) {
            ng[sk.top()] = i; sk.pop();
        }
        sk.push(i);
    }
    while(!sk.empty()) {
        ng[sk.top()] = -1;
        sk.pop();
    }
   return ng;
}
auto nse(auto &v){
    int n = v.size();
    vector<ll> ng(n);
    stack<ll> sk;
    for (int i=0;i<n;++i) {
        while(!sk.empty() and v[i]<v[sk.top()]) {
            ng[sk.top()] = i; sk.pop();
        }
        sk.push(i);
    }
    while(!sk.empty()) {
        ng[sk.top()] = -1;
        sk.pop();
    }
   return ng;
}
//  ll dpg[N], dps[N], in = -1;
// ll rec(int i) {
//     if(ng[i] == -1) {
//         in = i; return 0;
//     }
//     if(dpg[i] != -1) return dpg[i];
//    ll c =
//    i = ng[i];

//     ll c = rec(ng[i]) + (ng[i] - i - 1);
//     return dpg[i] =c;
// }

// ll rec2(int i) {
//     if(ns[i] == -1) return 0;
//     if(dps[i] != -1) return dps[i];
//     ll c = ns[i] - i - 1 + rec2(ns[i]);
// //    i = ng[i];
//     return dps[i] = c;
// }

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = M, i = 0, j = 0, k = 0, q = 0;
    cin >> n;
    vector<ll> v(n);
    for(i=0;i<n;++i) cin >> v[i];
    auto ng = nge(v); auto ns = nse(v);
    ck(ng, ns);
    // for(i=0;i<=n;++i) {
    //     dpg[i] = dps[i] = -1;
    // }
    // in = -1;
//    memset(dpg, -1, sizeof dpg);
//    memset(dps, -1, sizeof dps);
    for(i=0;i<n;++i) {
       a = i;
       c = n - 1;
        while(ng[a] != -1) {
            c--;
            a = ng[a];
        }
        b = c - 1;
        ck(i, b, a);
        for (j = a + 1;j<n;++j) {
            b = c - 1;
            a = j;
            while (ns[a] != -1) {
                b--;
                a = ns[a];
            }
            ck(i, b);
            d = min(d, b);
        }
    }
    cout << d;
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 0, tc = 1;
    cin >> tc;
    while(++t <= tc) {
        test(t);
    }
    return 0;
}