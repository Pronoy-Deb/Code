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
const int B = 440;

struct query {
int l, r, id;
bool operator < (const query &x) const {
    if (l / B == x.l / B) return ((l / B) & 1) ? r > x.r : r < x.r;
    return l / B < x.l / B;
}
} Q[N];
long long sum, cnt[N], ar[N];
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
long long ans[N];
void mo(int q) {
    sort(Q + 1, Q + q + 1); int l = 1, r = 0;
    for (int i = 1; i <= q; ++i) {
        int L = Q[i].l, R = Q[i].r;
        if (R < l) {
            while (l > L) add_left(--l);
            while (l < L) rem_left(l++);
            while (r < R) add_right(++r);
            while (r > R) rem_right(r--);
        }
        else {
            while (r < R) add_right(++r);
            while (r > R) rem_right(r--);
            while (l > L) add_left(--l);
            while (l < L) rem_left(l++);
        }
        ans[Q[i].id] = sum;
    }
}

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n;
    for (i = 1; i <= n; ++i) cin >> ar[i];
    cin >> q;
    for (i = 1; i <= q; ++i) {
        cin >> Q[i].l >> Q[i].r; Q[i].id = i;
    }
    mo(q);
    for (i = 1; i <= q; ++i) cout << ans[i] << '\n';

    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}