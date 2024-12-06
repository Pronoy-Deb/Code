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

vector<int> gp[N]; bitset<N> vis;
long long k1, k2, ans, sz[N], cnt[N]{1}, ct[N], mxDep, subDep, n;
int subSize(int u, int p) {
    sz[u] = 1;
    for (auto i : gp[u]) {
        if (!vis[i] && i != p) sz[u] += subSize(i, u);
    }
    return sz[u];
}
int centroid(int u, int p, int size) {
    for (auto v : gp[u]) {
        if (!vis[v] && v != p && (sz[v] << 1) > size) return centroid(v, u, size);
    }
    return u;
}
void go(int u, int p, long long dep = 1) {
    if (dep > k2) return; subDep = max(subDep, dep); ++ct[dep];
    for (auto &v : gp[u]) {
        if (!vis[v] && v != p) go(v, u, dep + 1);
    }
}
void dcom(int u = 1) {
    int size = subSize(u, u), c = centroid(u, u, size);
    vis[c] = true, mxDep = 0; long long tot = (k1 == 1);
    for (auto i : gp[c]) {
        if (!vis[i]) {
            subDep = 0; go(i, c); long long sum = tot;
            for (int d = 1; d <= subDep; ++d) {
                ans += sum * ct[d]; int d1 = k2 - d, d2 = k1 - d - 1;
                if (d1 >= 0) sum -= cnt[d1];
                if (d2 >= 0) sum += cnt[d2];
            }
            for (int d = k1 - 1, l = min(k2 - 1, subDep); d <= l; ++d) tot += ct[d];
            for (int d = 1; d <= subDep; ++d) cnt[d] += ct[d];
            mxDep = max(mxDep, subDep); fill(ct, ct + subDep + 1, 0);
        }
    }
    fill(cnt + 1, cnt + mxDep + 1, 0);
    for (auto v : gp[c]) if (!vis[v]) dcom(v);
}

void test(int32_t tc) {
    ll nn = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> k1 >> k2;
    for (i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        gp[u].push_back(v); gp[v].push_back(u);
    }
    dcom();
    cout << ans;
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}