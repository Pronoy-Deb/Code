#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ll long long
#define pe(c) for (auto &e : c) cout << e << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const ll M = 1e9 + 7, N = 2e5 + 5;

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
long long cnt[N], ar[N], ans[N], n, q;
void mo() {
    sort(Q + 1, Q + q + 1); int l = 1, r = 0, res = 0;
    auto add = [&](int i){
        res += (++cnt[ar[i]] == 1);
    };
    auto rem = [&](int i) {
        res -= (--cnt[ar[i]] == 0);
    };
    for (int i = 1; i <= q; ++i) {
        int L = Q[i].l, R = Q[i].r;
        if (R < l) {
            while (l > L) add(--l);
            while (l < L) rem(l++);
            while (r < R) add(++r);
            while (r > R) rem(r--);
        }
        else {
            while (r < R) add(++r);
            while (r > R) rem(r--);
            while (l > L) add(--l);
            while (l < L) rem(l++);
        }
        ans[Q[i].in] = res;
    }
}

void test(int tc) {
    ll o = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, p = 0;
    cin >> n >> q;
    unordered_map<int, int> mp;
    for (i = 1; i <= n; ++i) {
        cin >> ar[i];
        auto it = mp.find(ar[i]);
        if (it == mp.end()) {
            mp[ar[i]] = ++c; ar[i] = c;
        }
        else ar[i] = it -> second;
    }
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