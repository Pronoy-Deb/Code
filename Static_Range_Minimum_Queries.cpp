#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const int64_t M = 1e9 + 7, N = 2e5 + 5;

int64_t L[N], R[N], ar[N], ans[N]; pair<int, int> qr[N];

inline int64_t op(int64_t l, int64_t r) { return min(l, r); }
void dnq(int l, int r, auto &queries) {
    if (queries.empty()) return;
    if (l == r) {
        for (int i : queries) ans[i] = ar[l]; return;
    }
    int m = (l + r) >> 1; L[m] = ar[m];
    for (int i = m - 1; i >= l; --i) L[i] = op(ar[i], L[i + 1]);
    R[m + 1] = ar[m + 1];
    for (int i = m + 2; i <= r; ++i) R[i] = op(R[i - 1], ar[i]);
    vector<int> lq, rq;
    for (int i : queries) {
        int s = qr[i].first, e = qr[i].second;
        if (s <= m && m < e) {
            ans[i] = op(op(L[s], ar[m]), R[e]); continue;
        }
        if (e <= m) lq.push_back(i);
        else rq.push_back(i);
    }
    dnq(l, m, lq); dnq(m + 1, r, rq);
}

void test(int32_t tc) {
    int n, q; cin >> n >> q;
    for (int i = 0; i < n; ++i) cin >> ar[i];
    for (int i = 0; i < q; ++i) {
        cin >> qr[i].first >> qr[i].second;
        --qr[i].first, --qr[i].second;
    }
    vector<int> ind(q); iota(ind.begin(), ind.end(), 0);
    dnq(0, n - 1, ind);
    for (int i = 0; i < q; ++i) cout << ans[i] << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}