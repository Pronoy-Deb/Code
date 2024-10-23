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

// bitset<N> vis; vector<vector<int>> per; vector<int> p; int n;
// void gen() {
//     if ((int)p.size() == n) { per.push_back(p); return; }
//     for (int i = 1; i <= n; ++i) {
//         if (!vis[i]) {
//             vis[i] = 1; p.push_back(i); gen();
//             vis[i] = 0; p.pop_back();
//         }
//     }
// }
void test(int tc) {
    ll n = 0, m = M*M, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n;
    pair<int,int> ar[n + 5];
    for (i = 1; i <= n; ++i) {
        cin >> ar[i].first >> ar[i].second;
    }
    // gen();
    vector<vector<int>> per;
    vector<int> v(n);
    iota(v.begin(), v.end(), 1);
    // sort(v.begin(), v.end());
    do {
        per.push_back(v);
    } while (next_permutation(v.begin(), v.end()));
    vector<pair<int, int>> pr;
    for (auto &v : per) {
        vector<pair<int,int>> st;
        for (i = 0; i < n; ++i) {
            st.push_back(ar[v[i]]);
        }
        c = 0;
        for (i = 0; i < 2*n; ++i) {
            for(j=i+1;j<2*n;++j) {
                c += (st[i] > st[j]);
            }
        }
        if(c < m) {
            m = c;
            // pr.clear();
            // for (i = 0; i < n; ++i) {
            //     pr.push_back({ar[v[i]].first, ar[v[i]].second});
            // }
            pr = st;
        }
        // cout << '\n';
    }
    for(auto &[f, s] : pr) cout << f << ' ' << s << ' ';
    cout << '\n';
    // ck(st.size());
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}