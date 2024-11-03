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
vector<pair<int, long long>> gp[N];
bitset<N> vis; long long path[N], dis[N];
void dij(int src) {
    fill(dis, dis + N, LLONG_MAX);
    dis[src] = 0; set<pair<long long, int>> st;
    st.emplace(0, src);
    while (!st.empty()) {
        int nd = (*st.begin()).second; st.erase(st.begin());
        if(vis[nd]) continue; vis[nd] = true;
        for (auto &[cld, wt] : gp[nd]) {
            if (dis[nd] + wt < dis[cld]) {
                dis[cld] = dis[nd] + wt; st.emplace(dis[cld], cld);
                path[cld] = nd;
            }
        }
    }
}

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    // cin >> n;
    // vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    int vr; cin >> vr;
    for (i = 1; i < vr; ++i) {
        cin >> a >> b >> c;
        gp[i].emplace_back(i + 1, a);
        gp[i].emplace_back(c, b);
    }
    dij(1);
    cout << dis[vr] << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}