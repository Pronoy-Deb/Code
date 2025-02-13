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
    vector<int64_t> aa(n);
    for (int i = 0; i < n; ++i) { cin >> aa[i]; }
    vector<int64_t> bb(m);
    for (int i = 0; i < m; ++i) { cin >> bb[i]; }
    sort(bb.begin(), bb.end());
    ck(bb);
    for (int i = 0; i < n; ++i) {
        if (!i) {
            if (bb[0] - aa[i] < aa[i]) aa[i] = bb[0] - aa[i];
        }
        else {
            int a = lower_bound(bb.begin(), bb.end(), aa[i] + aa[i - 1]) - bb.begin();
            ck(tc, aa, a);
            if (a < m) {
                // aa[i] = bb[a] - aa[i];
                if (bb[a] - aa[i] < aa[i]) {
                    if (bb[a] - aa[i] >= aa[i - 1]) aa[i] = bb[a] - aa[i];
                }
                else {
                    if (aa[i] < aa[i - 1]) aa[i] = bb[a] - aa[i];
                }
            }
            // else {
            //     ps(0); return;
            // }
        }
    }
    // ck(aa);
    ps(is_sorted(aa.begin(), aa.end()));
    // cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}