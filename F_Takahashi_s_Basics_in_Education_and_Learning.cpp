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
array<int, 3> apgp(int r, int n)
{
    if (n == 1)
        return {r, 1, 0};

    if (n & 1) {
        auto [x, L0, L] = apgp(r, n - 1);
        return {r * x, 1 + r * L0, r * L0 + r * L};
    }
    auto [x, L0, L] = apgp(r, n / 2);
    int R0 = x * L0;
    int R = x * (n / 2 * L0 + L);
    return {x * x, L0 + R0, L + R};
}
void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> a >> d >> m;
    // vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    auto [f, s, t] = apgp(a, n);
    ck(f, s, t);
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}