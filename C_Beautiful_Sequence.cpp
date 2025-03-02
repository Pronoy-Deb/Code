#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const int64_t M = 998244353, N = 2e5 + 5;

void test(int32_t tc) {
    int64_t n; cin >> n;
    vector<int64_t> aa(n);
    vector<int> v;
    for (int i = 0; i < n; ++i) { cin >> aa[i]; if (aa[i] == 2) v.push_back(i); }
    vector<int64_t> prefix1(n, 0), prefix2(n, 0);
    vector<int64_t> suffix2(n, 0), suffix3(n, 0);
    for (int i = 1; i < n; i++) {
        prefix1[i] = prefix1[i - 1] + (aa[i - 1] == 1);
        prefix2[i] = prefix2[i - 1] + (aa[i - 1] == 2);
    }
    for (int i = n - 2; i >= 0; i--) {
        suffix2[i] = suffix2[i + 1] + (aa[i + 1] == 2);
        suffix3[i] = suffix3[i + 1] + (aa[i + 1] == 3);
    }
    int64_t ans = 0, sz = v.size();
    for (int l = 1; l < sz; ++l) {
        for (int i = 0; i + l < sz; ++i) {
            ans = (ans + prefix1[v[i]] * suffix3[v[i + l - 1]] % M) % M;
        }
    }
    cout << ans << '\n';
    // cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}