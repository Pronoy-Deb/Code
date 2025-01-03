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
    int n; vector<long long> ar, tre;
    sgt(auto &ar) : n(ar.size()), ar(ar), tre((n << 2) + 5) { make(1, 0, n - 1); }
    inline auto op(long long l, long long r) { return (l + r); }
    void make(int nd, int s, int e) {
        if (s >= e) { if (s == e) tre[nd] = ar[s]; return; }
        int m = (s + e) >> 1, lc = nd << 1, rc = lc | 1;
        make(lc, s, m); make(rc, m + 1, e); tre[nd] = op(tre[lc], tre[rc]);
    }
    void up(int in, long long val, int nd = 1, int s = 0, int e = -1) {
        if (!~e) e = n - 1; if (s == e) { tre[nd] = val; return; }
        int m = (s + e) >> 1, lc = nd << 1, rc = lc | 1;
        if (in <= m) up(in, val, lc, s, m); else up(in, val, rc, m + 1, e);
        tre[nd] = op(tre[lc], tre[rc]);
    }
    long long get(int l, int r, int nd = 1, int s = 0, int e = -1) {
        if (!~e) e = n - 1; if (s > e || s > r || e < l) return 0;
        if (s >= l && e <= r) return tre[nd];
        int m = (s + e) >> 1, lc = nd << 1, rc = lc | 1;
        return op(get(l, r, lc, s, m), get(l, r, rc, m + 1, e));
    }
};

void test(int32_t tc) {
    ll n; cin >> n;
    int fre[2 * n + 5]{}; pair<int, int> ar[n];
    vector<ll> ar1(2 * n + 5);
    for (int i = 0; i < n; ++i) {
        cin >> ar[i].first >> ar[i].second;
        ar[i].first--, ar[i].second--;
        if (ar[i].first == ar[i].second) {
            ++fre[ar[i].first]; ar1[ar[i].first] = 1;
        }
    }
    sgt t(ar1);
    string s(n, '0');
    for (int i = 0; i < n; ++i) {
        int a = ar[i].first, b = ar[i].second;
        ll cnt = t.get(a, b) - (a == b and fre[a] == 1);
        if (cnt != b - a + 1) s[i] = '1';
    }
    cout << s << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}