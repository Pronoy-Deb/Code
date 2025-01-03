#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ll long long
#define pe(c) for (auto e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "Yes" : "No") << '\n'
const ll M = 1e9 + 7, N = 2e5 + 5;

void test(int32_t tc) {
    ll n, m; cin >> n >> m;
    // vector<ll> ar(n); for (int i = 0; i < n; ++i) { cin >> ar[i]; }
    // vector<int> b[2], w[2];
    map<int, set<int, greater<>>> br, bc, wr, wc;
    while (m--) {
        int r, c; char ch; cin >> r >> c >> ch;
        if (ch == 'B') {
            br[r].insert(c);
            bc[c].insert(r);
        }
        else {
            wr[r].insert(c);
            wc[c].insert(r);
        }
    }
    // for (auto &[f, s] : wr) {
    //     sort(s.begin(), s.end());
    // }
    // for (auto &[f, s] : wc) {
    //     sort(s.begin(), s.end());
    // }
    for (auto &[f, s] : br) {
        for (auto e : s) {
            auto it = wc.find(e);
            if (it != wc.end() and *it->second.begin() > f) {
                ps(0); return;
            }
        }
    }
    for (auto &[f, s] : bc) {
        for (auto e : s) {
            auto it = wr.find(e);
            if (it != wr.end() and *it->second.begin() > f) {
                ps(0); return;
            }
        }
    }
    ps(1);
    // cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}