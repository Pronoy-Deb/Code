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
const ll M = 1e9 + 7, N = 5e4 + 5;
int par[N], sz[N];
void make(int n) {
    for (int i = 1; i <= n; ++i) {
        par[i] = i; sz[i] = 1;
    }
}
int get(int i) {
    return (par[i] == i ? i : par[i] = get(par[i]));
}
void uni(int a, int b) {
    a = get(a); b = get(b);
    if (a != b) {
        if (sz[a] < sz[b]) swap(a, b);
        par[b] = a; sz[a] += sz[b];
    }
}
bool same(int a, int b) { return get(a) == get(b); }
int len(int a) { return sz[get(a)]; }
void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> m >> q;
    // vector<ll> ar(n);
    for (i = 0; i < m; ++i) { cin >> a >> b; }
    tuple<bool, int, int> tp[q];
    for(i = 0; i < q; ++i) {
        string s; cin >> s >> a >> b;
        if (s == "ask") tp[i] = {0, a, b};
        else tp[i] = {1, a, b};
    }
    make(n);
    vector<bool> ans;
    for (i = q-1; i >= 0; --i) {
        auto [f, s, t] = tp[i];
        if (f) uni(s, t);
        else ans.push_back(same(s, t));
    }
    for (i = ans.size() - 1; i >= 0; --i) ps(ans[i]);
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}