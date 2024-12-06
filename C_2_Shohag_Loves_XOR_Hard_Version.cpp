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
auto div(long long n) {
    vector<long long> v;
    for (long long i = 1; i * i <= n; ++i) {
        if (!(n % i)) {
            v.push_back(i); long long tmp = n / i;
            if (i != tmp) v.push_back(tmp);
        }
    }
    return v;
}
void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> m;
    // vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    // auto v = div(n);
    // for (auto e : v) {
    //     a = e ^ n;
    //     c += (a <= m and e != n);
    // }
    for (i=1;i<=n;++i) {
        a = n ^ i;
        if (a <= m and (a % i == 0 or n % i == 0)) {
            // ck(a, i);
            c++;
        }
    }
    cout << c;
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}