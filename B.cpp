#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pe(c) for (auto &e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
const ll M = 1e9 + 7, N = 2e5 + 5;
long long ar[N], n; vector<long long> tre[N << 2];
auto merge(auto &a, auto &b) {
    int i, j, k = a.size(), l = b.size(); vector<long long> res;
    for (i = 0, j = 0; i < k && j < l;) {
        if (a[i] < b[j]) res.push_back(a[i++]);
        else res.push_back(b[j++]);
    }
    while (i < k) res.push_back(a[i++]);
    while (j < l) res.push_back(b[j++]);
    return res;
}
void make(int nd = 0, int s = 0, int e = n - 1) {
    if (s == e) { tre[nd].push_back(ar[e]); return; }
    int m = (s + e) >> 1, lc = (nd << 1) + 1, rc = lc + 1;
    make(lc, s, m); make(rc, m + 1, e);
    tre[nd] = merge(tre[lc], tre[rc]);
}
void up(int in, long long val, int nd = 0, int s = 0, int e = n - 1) {
    if (s == e) { tre[nd][0] = val; return; }
    int m = (s + e) >> 1, lc = (nd << 1) + 1, rc = lc + 1;
    if (in <= m) up(in, val, lc, s, m);
    else up(in, val, rc, m + 1, e);
    tre[nd] = merge(tre[lc], tre[rc]);
}
int get(int l, int r, long long val, int nd = 0, int s = 0, int e = n - 1) {
    if (l > e || r < s || l > r) return 0;
    if (l <= s && e <= r)
        return lower_bound(tre[nd].begin(), tre[nd].end(), val) - tre[nd].begin();
    int m = (e + s) >> 1, lc = (nd << 1) + 1, rc = lc + 1;
    return get(l, r, val, lc, s, m) + get(l, r, val, rc, m + 1, e);
}
int get1(int l, int r, long long val, int nd = 0, int s = 0, int e = n - 1) {
    if (l > e || r < s || l > r) return 0;
    if (l <= s && e <= r)
        return lower_bound(tre[nd].begin(), tre[nd].end(), val + 1) - tre[nd].begin();
    int m = (e + s) >> 1, lc = (nd << 1) + 1, rc = lc + 1;
    return get1(l, r, val, lc, s, m) + get1(l, r, val, rc, m + 1, e);
}
void reset() {
    for (int i = 0; i < (n << 2); ++i) tre[i].clear();
}
void test(int tc) {
    ll o = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n;
    // vector<ll> ar(n);
    for (i = 0; i < n; ++i) { cin >> ar[i]; }
    make();
    cin >> q;
    while(q--) {
        d = 0;
        cin >> a >> b >> c ; --a; --b; --c;
        k = get(a, b - 1, ar[b]);
        m = (c - b) - get1(b + 1, c, ar[b]);
        d += (k * m);
        k = (b - a) - get1(a, b - 1, ar[b]);
        m = get(b + 1, c, ar[b]);
        d += (k * m);
        cout << d << '\n';
    }
    // cout << '\n';
    reset();
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}