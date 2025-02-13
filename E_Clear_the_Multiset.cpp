#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const int64_t M = 1e9 + 7, N = 5e3 + 5;

vector<int> aa(N);
int rec(int l, int r) {
    if (l > r) return 0;
    int mn = *min_element(aa.begin() + l, aa.begin() + r + 1), idx = -1;
    for (int i = l; i <= r; ++i) {
        aa[i] -= mn; if (!aa[i]) idx = i;
    }
    return min(rec(l, idx - 1) + rec(idx + 1, r) + mn, r - l + 1);
}

void test(int32_t tc) {
    int64_t n; cin >> n;
    for (int i = 0; i < n; ++i) { cin >> aa[i]; }
    cout << rec(0, n - 1) << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}