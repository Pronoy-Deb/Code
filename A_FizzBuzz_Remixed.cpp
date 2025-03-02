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
    int64_t n; cin >> n;
    // vector<int64_t> aa(n);
    // for (int i = 0; i < n; ++i) { cin >> aa[i]; }
    int64_t ans = n / 15, a = min(3, (int)n % 15 + 1);
    ans = 3 * ans + a;
    cout << ans;
    // if (n <= 0) ++ans;
    // else if (n <= 1) ans += 2;
    // else if (n <= 2) ans += 3;
    // cout << ans;
    // for (int i = 0; i <= n; ++i) {
    //     if (i % 3 == i % 5) cout << i << ' ';
    // }
    cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}