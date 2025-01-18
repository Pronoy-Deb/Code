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

void test(int32_t tc) {
    ll n; cin >> n; ll mx = -M*M;
    vector<ll> pos, neg;
    for (int i = 0; i < n; ++i) {
        ll a; cin >> a; mx = max(mx, a);
        if (a >= 0) pos.push_back(a);
        else neg.push_back(a);
    }
    if (mx <= 0) {
        cout << 0 << '\n'; return;
    }
    int sz = pos.size(), sz1 = neg.size();
    ll pre[sz + 1]; pre[sz] = 0;
    for (int i = sz - 1; i >= 0; --i) pre[i] = pre[i + 1] + pos[i];
    // for (auto e : pre) cerr << e << ' '; cerr << '\n';
    ll lo = mx, hi = 1e15, ans = mx;
    while (lo < hi) {
        ll mid = lo + hi >> 1, sum = 0, i = 0, j = 0;
        while (i < sz and j < sz1) {
            if (sum + pos[i] > mid) {
                ll tot = 0;
                while (j < sz1 and tot < sum) tot += abs(neg[j]), ++j;
                sum = pos[i];
                i += (j < sz1);
            }
            else {
                sum += pos[i], ++i;
            }
        }
        if (pre[i] <= mid) {
            // cout << mx << '\n'; return;
            hi = mid - 1; ans = mid;
        }
        else {
            lo = mid + 1;
            // mx = pre[i];
        }
    }
    cout << ans;
    cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}