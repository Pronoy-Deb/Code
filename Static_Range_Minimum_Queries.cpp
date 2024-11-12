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
long long bs, ans[N], ar[N], n, m; tuple<int, int, int> qr[N];
bool cmp(const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
    int L1 = get<0>(a), R1 = get<1>(a);
    int L2 = get<0>(b), R2 = get<1>(b);
    if (L1 / bs != L2 / bs) return L1 / bs < L2 / bs;
    return R1 < R2;
}
void mo() {
    bs = sqrt(n); sort(qr, qr + m, cmp);
    long long l = 0, r = 0, res = M;
    multiset<ll> st; st.insert(M);

    // auto add = [&](int x) {
    //     if (mp[ar[x]] == ar[x]) res--;
    //     mp[ar[x]]++; if (mp[ar[x]] == ar[x]) res++;
    // };
    // auto rem = [&](int x) {
    //     if (mp[ar[x]] == ar[x]) res--;
    //     mp[ar[x]]--; if (mp[ar[x]] == ar[x]) res++;
    // };

    auto add = [&](int x) {
        if (ar[x] == *st.begin()) res = (st.size() > 1 ? *next(st.begin()) : M);
        st.insert(ar[x]);
        if (*st.begin() == ar[x]) res = *st.begin();
        else
            res = M;
        // ck(st);
    };
    auto rem = [&](int x) {
        if (ar[x] == *st.begin()) res = (st.size() > 1 ? *next(st.begin()) : M);
        // st.erase(st.find(ar[x]));
        auto it = st.find(ar[x]);
        if (it != st.end()) st.erase(it);
        if (!st.empty() and *st.begin() == ar[x]) res = *st.begin();
        else
            res = M;
        // ck(st);
    };
    for (int i = 0; i < m; ++i) {
        auto &[L, R, in] = qr[i];
        while (l < L) rem(l++);
        while (l > L) add(--l);
        while (r <= R) add(r++);
        while (r > R + 1) rem(--r);
        ans[in] = *st.begin();
    }
}
void test(int tc) {
    ll p = 0, o = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> m;
    for (i = 0; i < n; ++i) { cin >> ar[i]; }
    for (i = 0; i < m; ++i) {
        cin >> a >> b;
        qr[i] = {a - 1, b - 1, i};
    }
    mo();
    for (i = 0; i < m; ++i) cout << ans[i] << '\n';
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}