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
const ll M = 1e9 + 7, N = 1e5 + 5;

long long tre[N << 1], lz[N], ar[N], n;
inline long long op(long long l, long long r) { return (l + r); }
void make() {
    for (int i = 0; i < n; ++i) { tre[i + n] = ar[i]; lz[i] = -1; }
    for (int i = n - 1; i > 0; --i) tre[i] = op(tre[i << 1], tre[i << 1 | 1]);
}
void apply(int in, long long val, int k) {
    tre[in] = val * k; if (in < n) lz[in] = val;
}
void push(int l, int r) {
    int s = (sizeof(int) << 3) - __builtin_clz(n), k = 1 << (s - 1);
    for (l += n, r += n - 1; s > 0; --s, k >>= 1) {
        for (int i = l >> s; i <= r >> s; ++i) {
            if (~lz[i]) {
                apply(i << 1, lz[i], k); apply(i << 1 | 1, lz[i], k); lz[i] = -1;
            }
        }
    }
}
void rebuild(int l, int r) {
    int k = 2;
    for (l += n, r += n - 1; l > 1; k <<= 1) {
        l >>= 1, r >>= 1;
        for (int i = r; i >= l; --i) tre[i] = (~lz[i] ? lz[i] * k : op(tre[i << 1], tre[i << 1 | 1]));
    }
}
void asn(int l, int r, long long val) {
    if (l < 0 || r >= n) return;
    push(l, l + 1); push(r, ++r); int l0 = l, r0 = r, k = 1;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1) {
        if (l & 1) apply(l++, val, k); if (r & 1) apply(--r, val, k);
    }
    rebuild(l0, l0 + 1); rebuild(r0 - 1, r0);
}
long long get(int l, int r) {
    long long res = 0; if (l < 0 || r >= n) return res;
    push(l, l + 1); push(r, ++r);
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = op(res, tre[l++]); if (r & 1) res = op(res, tre[--r]);
    }
    return res;
}

void test(int tc) {
    ll o = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> q;
    // vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    make();
    while (q--) {
        cin >> d;
        if (d == 1) {
            cin >> a >> b >> c; asn(a, b - 1, c);
        }
        else {
            cin >> a >> b; cout << get(a, b - 1) << '\n';
        }
    }
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}