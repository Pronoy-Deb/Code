#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ll long long
#define pe(c) for (auto e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const ll M = 1e9 + 7, N = 2e5 + 5;

void test(int32_t tc) {
    ll n; cin >> n;
    pair<int, int> in[n + 5];
    bool vis[n + 5]{};
    vector<ll> ar(n); for (int i = 0; i < n; ++i) {
        cin >> ar[i];
        if (vis[ar[i]]) in[ar[i]].second = i;
        else in[ar[i]].first = in[ar[i]].second = i;
        vis[ar[i]] = true;
    }
    // for (auto [f, s] : in) cerr << f << ' ' << s << endl;
    memset(vis, 0, sizeof(vis));
    set<ll> st; int last = 0; ll ans = 0;
    for (int i = 0; i < n; ++i) {
        last = max(last, i);
        if (vis[ar[i]]) {
            auto it = st.find(ar[i]);
            if (it != st.end()) st.erase(it);
            continue;
        }
        auto [f, l] = in[ar[i]];
        if (f == l) {
            continue;
        }
        while (last <= l) {
            st.insert(ar[last]);
            if (in[ar[last]].second <= l) vis[ar[last]] = true;
            ++last;
        }
        ans += st.size();
        auto it = st.find(ar[i]);
        if (it != st.end()) st.erase(it);
        vis[ar[i]] = true;
        ck(tc, st);
    }
    cout << ans << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}