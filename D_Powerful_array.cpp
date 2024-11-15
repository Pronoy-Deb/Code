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
const ll M = 1e9 + 7, N = 1e6 + 5;

long long sum, cnt[N], ar[N], ans[N], n, q;
uint64_t hilbertOrder(uint64_t x, uint64_t y) {
    const uint64_t logn = __lg((max(x, y) << 1) + 1) | 1, maxn = (1ull << logn) - 1;
    uint64_t res = 0;
    for (uint64_t s = 1ull << (logn - 1); s; s >>= 1) {
        bool rx = x & s, ry = y & s;
        res = (res << 2) | (rx ? ry ? 2 : 1 : ry ? 3 : 0);
        if (!rx) {
            if (ry) x ^= maxn, y ^= maxn; swap(x, y);
        }
    }
    return res;
}
struct Query {
    int l, r, in; int64_t ord;
    void order() { ord = hilbertOrder(l, r); }
    bool operator<(const Query &x) const { return ord < x.ord; }
} Q[N];
inline void add_left(int i) {
    sum += ((cnt[ar[i]]++ << 1) + 1) * ar[i];
}
inline void add_right(int i) {
    sum += ((cnt[ar[i]]++ << 1) + 1) * ar[i];
}
inline void rem_left(int i) {
    sum -= ((cnt[ar[i]]-- << 1) - 1) * ar[i];
}
inline void rem_right(int i) {
    sum -= ((cnt[ar[i]]-- << 1) - 1) * ar[i];
}
void mo() {
    sort(Q + 1, Q + q + 1); int l = 1, r = 0;
    for (int i = 1; i <= q; ++i) {
        int L = Q[i].l, R = Q[i].r;
        while (r < R) add_right(++r);
        while (r > R) rem_right(r--);
        while (l > L) add_left(--l);
        while (l < L) rem_left(l++);
        ans[Q[i].in] = sum;
    }
}

void test(int tc) {
    ll o = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, p = 0;
    cin >> n >> q;
    for (i = 1; i <= n; ++i) cin >> ar[i];
    for (i = 1; i <= q; ++i) {
        cin >> Q[i].l >> Q[i].r; Q[i].in = i;
        Q[i].order();
    }
    mo();
    for (i = 1; i <= q; ++i) cout << ans[i] << '\n';
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}