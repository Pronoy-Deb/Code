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
    int64_t n, m; cin >> n >> m;
    vector<int64_t> ar(n);
    for (int i = 0; i < n; ++i) { cin >> ar[i]; }
    int a; cin >> a;
    for (int i = 0; i < n; ++i) {
        if (!i) {
            if (a - ar[i] < ar[i]) ar[i] = a - ar[i];
        }
        else {
            if (a - ar[i] < ar[i] and a - ar[i] >= ar[i - 1]) ar[i] = a - ar[i];
        }
    }
    ck(ar);
    ps(is_sorted(ar.begin(), ar.end()));
    // cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}