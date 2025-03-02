#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const int64_t M = 1e9 + 7, N = 2e5 + 5;

void test(int32_t tc) {
    int64_t n, k; cin >> n >> k;
    string s; cin >> s;
    vector<int64_t> pen(n);
    set<pair<int64_t, int>, greater<>> b, r; int c = 0;
    for (int i = 0; i < n; ++i) { cin >> pen[i];
        if (s[i] == 'B') b.insert({pen[i], i});
        else r.insert({pen[i], i}), ++c;
    }
    if (k == n or c == n) {
        cout << 0 << '\n'; return;
    }
    while (k-- and !b.empty()) {
        b.erase(b.begin());
    }
    if (b.empty()) {
        cout << 0 << '\n'; return;
    }
    int64_t wt = b.begin()->first, in = b.begin()->second, mx = LLONG_MIN;
    bool flag = false;
    for (int i = in + 1; i < n; ++i) {
        if (s[i] == 'R') {
            if (pen[i] > wt) break;
            mx = max(mx, pen[i]);
        }
        else {
            // wt = min(wt, pen[i]);
            flag = true;
        }
    }
    bool flag1 = false; int64_t mx1 = LLONG_MIN;
    for (int i = in - 1; i >= 0; --i) {
        if (s[i] == 'R') {
            if (pen[i] > wt) break;
            mx1 = max(mx1, pen[i]);
        }
        else{
            flag1 = true;
        }
    }
    if (flag) wt = min(wt, mx);
    if (flag1) wt = min(wt, mx1);
    cout << wt;
    cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}