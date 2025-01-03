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

struct sgt {
    int n; vector<long long> ar, tre, lzi, lza;
    sgt(auto &ar) : n(ar.size()), ar(ar), tre((n << 2) + 5), lzi((n << 2) + 5), lza((n << 2) + 5) { make(1, 1, n); }
    inline auto op(long long l, long long r) { return (l + r); }
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
    void make(int i, int s, int e) {
        if (s >= e) { if (s == e) tre[i] = ar[s]; return; }
        int m = (s + e) >> 1, lc = i << 1, rc = lc | 1;
        make(lc, s, m); make(rc, m + 1, e); tre[i] = op(tre[lc], tre[rc]);
    }
    void inc(int l, int r, long long v, int i = 1, int s = 1, int e = -1) {
        if (!~e) e = n; if (s > e || l > e || r < s) return;
        if (l <= s && e <= r) { pgi(i, v, s, e); return; }
        push(i, s, e); int m = (s + e) >> 1, lc = i << 1, rc = lc | 1;
        inc(l, r, v, lc, s, m); inc(l, r, v, rc, m + 1, e);
        tre[i] = op(tre[lc], tre[rc]);
    }
    void asn(int l, int r, long long v, int i = 1, int s = 1, int e = -1) {
        if (!~e) e = n; if (s > e || l > e || r < s) return;
        if (l <= s && e <= r) { pga(i, v, s, e); return; }
        push(i, s, e); int m = (s + e) >> 1, lc = i << 1, rc = lc | 1;
        asn(l, r, v, lc, s, m); asn(l, r, v, rc, m + 1, e);
        tre[i] = op(tre[lc], tre[rc]);
    }
    long long get(int l, int r, int i = 1, int s = 1, int e = -1) {
        if (!~e) e = n; if (s > e || l > e || r < s) return 0;
        if (l <= s && e <= r) return tre[i];
        push(i, s, e); int m = (s + e) >> 1, lc = i << 1, rc = lc | 1;
        return op(get(l, r, lc, s, m), get(l, r, rc, m + 1, e));
    }
};

void test(int32_t tc) {
    ll n, q; cin >> n >> q;
    vector<ll> ar(n + 5); for (int i = 1; i <= n; ++i) { cin >> ar[i]; }
    sgt t(ar);
    while (q--) {
        int tp; cin >> tp;
        if (tp == 1) {
            int l, r, v; cin >> l >> r >> v;
            t.inc(l, r, v);
        } else if (tp == 2) {
            int l, r, v; cin >> l >> r >> v;
            t.asn(l, r, v);
        } else {
            int l, r; cin >> l >> r;
            cout << t.get(l, r) << '\n';
        }
    }
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}