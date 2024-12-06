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

long long lzi[N << 2], lza[N << 2], tre[N << 2], ar[N], n;
inline long long op(long long l, long long r) { return (l + r); }
inline void pgi(int i, long long v, int s, int e) {
    lzi[i] += v; tre[i] += (e - s + 1) * v;
}
inline void pga(int i, long long v, int s, int e) {
    lza[i] = v; lzi[i] = 0; tre[i] = (e - s + 1) * v;
}
void push(int i, int s, int e) {
    int m = (s + e) >> 1, lc = i << 1, rc = lc | 1;
    if (lza[i]) {
        pga(lc, lza[i], s, m); pga(rc, lza[i], m + 1, e); lza[i] = 0;
    }
    if (lzi[i]) {
        pgi(lc, lzi[i], s, m); pgi(rc, lzi[i], m + 1, e); lzi[i] = 0;
    }
}
void make(int i = 1, int s = 1, int e = n) {
    if (s >= e) { if (s == e) tre[i] = ar[s]; return; }
    int m = (s + e) >> 1, lc = i << 1, rc = lc | 1;
    make(lc, s, m); make(rc, m + 1, e); tre[i] = op(tre[lc], tre[rc]);
}
void inc(int l, int r, long long v, int i = 1, int s = 1, int e = n) {
    if (s > e || l > e || r < s) return;
    if (l <= s && e <= r) { pgi(i, v, s, e); return; }
    push(i, s, e); int m = (s + e) >> 1, lc = i << 1, rc = lc | 1;
    inc(l, r, v, lc, s, m); inc(l, r, v, rc, m + 1, e);
    tre[i] = op(tre[lc], tre[rc]);
}
void asn(int l, int r, long long v, int i = 1, int s = 1, int e = n) {
    if (s > e || l > e || r < s) return;
    if (l <= s && e <= r) { pga(i, v, s, e); return; }
    push(i, s, e); int m = (s + e) >> 1, lc = i << 1, rc = lc | 1;
    asn(l, r, v, lc, s, m); asn(l, r, v, rc, m + 1, e);
    tre[i] = op(tre[lc], tre[rc]);
}
long long get(int l, int r, int i = 1, int s = 1, int e = n) {
    if (s > e || l > e || r < s) return 0;
    if (l <= s && e <= r) return tre[i];
    push(i, s, e); int m = (s + e) >> 1, lc = i << 1, rc = lc | 1;
    return op(get(l, r, lc, s, m), get(l, r, rc, m + 1, e));
}

void test(int32_t tc) {
    ll nn = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> q;
    for (i = 1; i <= n; ++i) { cin >> ar[i]; }
    make();
    while (q--) {
        cin >> d;
        if (d == 1) {
            cin >> a >> b >> c; inc(a, b, c);
        }
        else if (d == 2) {
            cin >> a >> b >> c; asn(a, b, c);
        }
        else {
            cin >> a >> b; cout << get(a, b) << '\n';
        }
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