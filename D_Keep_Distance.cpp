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

void test(int32_t tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> m;
    vector<int> ar(n);
    int in = n-1; a = 1;
    for (i=0;i<n;++i) ar[i] = a, a+=10;
    vector<vector<int>> v;
    if (ar[n-1] <= m) v.emplace_back(ar);
    while(in >= 0) {
        ar[in]++;
        if(ar[in] > m) {
            in--; if(in<0) break;
            ar[in]++;
        }
        a = ar[in]+10;
        for (i = in+1; i<n; ++i) ar[i] = a, a+=10;
        if (ar[n-1] > m) continue;
        v.emplace_back(ar);
        in = n - 1;
    }
    cout << v.size() << '\n';
    for(auto &r : v) {
        for(auto e : r) cout << e << ' ';
        cout << '\n';
    }
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}