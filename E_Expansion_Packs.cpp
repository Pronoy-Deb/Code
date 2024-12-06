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
int P[N], n;
auto pre() {
    vector<long double> prob(n + 1); prob[0] = 1.0;
    for (int i = 0; i < n; ++i) {
        long double p = P[i] / 100.0;
        for (int k = n; k >= 1; --k) prob[k] = prob[k] * (1 - p) + prob[k - 1] * p;
        prob[0] *= (1 - p);
    }
    return prob;
}
long double ex(int X) {
    vector<long double> prob = pre(), dp(X + 1, 1.0); dp[0] = 0.0;
    for (int x = 1; x <= X; ++x) {
        for (int k = 1; k <= n && k <= x; ++k) dp[x] += prob[k] * dp[x - k];
        dp[x] /= (1 - prob[0]);
    }
    return dp[X];
}
void test(int32_t tc) {
    ll nn = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> k;
    for (i = 0; i < n; ++i) { cin >> P[i]; }
    cout << fixed << setprecision(16) << ex(k);
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}