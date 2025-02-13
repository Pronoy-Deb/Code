#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ll long long
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const int M = 1e9 + 7, N = 4e5 + 5;

void test(int32_t tc) {
    ll n; cin >> n;
    set<pair<int, int>> st;
    int wt[n + 5];
    vector<int> gp[n + 5];
    for (int i = 1; i <= n; ++i) { int a; cin >> a; st.insert({a, i}); wt[i] = a; }
    for (int i = 0; i < n - 1; ++i) {
        int u, v; cin >> u >> v;
        gp[u].push_back(v);
        gp[v].push_back(u);
    }
    auto it = st.begin();
    int beg = it->second;
    if (beg == 1) {
        if (n > 1) {
            ++it; beg = it->second;
        } else {
            cout << 0 << '\n'; return;
        }
    }
    ck(beg);
    bool win = 1, vis[n + 5]{}; int last = 0;
    while (!st.empty()) {
        set<int> sst = {1};
        while (it != st.end() and (it->second == 1 or it->first <= last)) {
            sst.insert(it->second); ++it;
        }
        if (it == st.end()) {
            if (win) cout << beg; else cout << 0; cout << '\n'; return;
        }
        int u = it->second; last = it->first;
        vis[u] = true;
        st.erase(it);
        for (int v : gp[u]) {
            if (vis[v] or sst.find(v) != sst.end()) continue;
            st.erase({wt[v], v});
        }
        ck(st);
        it = st.begin();
        win ^= 1;
    }
    if (win) cout << 0; else cout << beg;
    cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}