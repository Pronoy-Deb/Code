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
long long bs, ans[N], ar[N], n, q; tuple<int, int, int> qr[N];
bool cmp(const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
    int L1 = get<0>(a), R1 = get<1>(a);
    int L2 = get<0>(b), R2 = get<1>(b);
    if (L1 / bs != L2 / bs) return L1 / bs < L2 / bs;
    return R1 < R2;
}
int cnt[N];
void mo() {
    bs = sqrt(n); sort(qr, qr + q, cmp);
    long long l = -1, r = -1, res = 0;
    auto add = [&](int x) {
        if (++cnt[ar[x]] == 1) res++;
    };
    auto rem = [&](int x) {
        if (--cnt[ar[x]] == 0) res--;
    };
    for (int i = 0; i < q; ++i) {
        auto &[L, R, in] = qr[i];
        while (l < L) rem(l++);
        while (l > L) add(--l);
        while (r < R) add(++r);
        while (r > R) rem(r--);
        ans[in] = res;
    }
}

void test(int tc) {
    ll o = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, p = 0;
    cin >> n;
    for (i = 0; i < n; ++i) { cin >> ar[i]; }
    cin >> q;
    for (i = 0; i < q; ++i) {
        cin >> a >> b;
        qr[i] = {a - 1, b - 1, i};
    }
    mo();
    for (i = 0; i < q; ++i) cout << ans[i] << '\n';
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}