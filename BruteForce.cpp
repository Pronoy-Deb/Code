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
const ll M = 1e9, N = 2e5 + 5;

bitset<N> ip;
void pre() {
	ip[2] = true; for (int i = 3; i < N; i += 2) ip[i] = true;
    for (long long i = 3, j; (j = i * i) < N; i += 2) {
        for (; ip[i] && j < N; j += (i << 1)) ip[j] = false;
    }
}
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
int cc(int n) {
    int cc = 0;
    for (int i = 1; i <= n; ++i) {
        if (ip[i] and get(i) == i) ++cc;
    }
    return cc;
}

void test(int32_t tc) {
    // for (int i = 0; i < 20; ++i) if (!ip[i]) cout << i << ' ';
    ll n, m; cin >> n >> m;
    vector<array<ll, 3>> gp;
    while (m--) {
        ll a, b, c; cin >> a >> b >> c;
        if (ip[a] and ip[b]) gp.push_back({c, a, b});
    }
    sort(gp.begin(), gp.end());
    make(n);
    ll ans = 0;
    for (auto &[c, a, b] : gp) {
        if (!same(a, b)) {
            uni(a, b); ans += c;
        }
    }
    ll c = cc(n);
    cout << ans + (c - 1) * M << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    pre();
    while (tc++ < tt) test(tc);
    return 0;
}