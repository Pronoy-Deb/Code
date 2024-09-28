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
const ll M = 1e9 + 7, N = 1e5 + 5;

long long tre[N << 2], lz[N << 2], ar[N], n;
long long com(long long x, long long y) { return x + y; }
void make(int nd = 1, int s = 0, int e = n - 1) {
    if (s >= e) { if (s == e) tre[nd] = ar[s]; return; }
    int m = (s + e) >> 1, lc = nd << 1, rc = lc | 1;
    make(lc, s, m); make(rc, m + 1, e); tre[nd] = com(tre[lc], tre[rc]);
}
void propagate(int nd, int s, int e) {
    if (lz[nd]) {
        tre[nd] += (e - s + 1) * lz[nd];
        if (s != e) { lz[nd << 1] += lz[nd]; lz[nd << 1 | 1] += lz[nd]; }
        lz[nd] = 0;
    }
}
void add(int l, int r, long long val, int nd = 1, int s = 0, int e = n - 1) {
    propagate(nd, s, e); if (s > e || s > r || e < l) return;
    int m = (s + e) >> 1, lc = nd << 1, rc = lc | 1;
    if (s >= l && e <= r) { lz[nd] += val; propagate(nd, s, e); return; }
    add(l, r, val, lc, s, m); add(l, r, val, rc, m + 1, e);
    tre[nd] = com(tre[lc], tre[rc]);
}
long long get(int l, int r, int nd = 1, int s = 0, int e = n - 1) {
    propagate(nd, s, e); if (s > e || s > r || e < l) return 0;
    if (s >= l && e <= r) return tre[nd];
    int m = (s + e) >> 1, lc = nd << 1, rc = lc | 1;
    return com(get(l, r, lc, s, m), get(l, r, rc, m + 1, e));
}
void reset() { for (int i = 0; i < (n << 2) + 5; ++i) tre[i] = lz[i] = 0; }

void test(int tc) {
    cout << "Case " << tc << ":\n";
    ll a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, m = 0, q = 0;
    cin >> n >> q;
    for (i = 0; i < n; ++i) {
        cin >> ar[i];
    }
    make();
    while(q--) {
        cin >> c;
        if(c == 1) {
            cin >> a; b = get(a, a);
            cout << b << '\n'; add(a, a, -b);
        }
        else if(c==2){
            cin >> a >> b; add(a, a, b);
        }
        else {
            cin >> a >> b; cout << get(a, b) << '\n';
        }
    }
    reset();
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}