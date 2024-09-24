#include <bits/stdc++.h>
using namespace std;
#define ll long long
auto f(auto *x, auto &&r) { cerr << x << " = " << r << '\n'; } auto f(auto *x, auto &&r, auto &&...g) { auto *c = strchr(x + 1, ','); cerr.write(x, c - x) << " = " << r << ','; f(++c, g...); }
#define pr(c) for (auto& r:c) { for (auto& e:r) cerr << e << ' '; cerr << '\n'; }
#define pn(c, n) for (k = 0; k < n; ++k) cerr << c[k] << " \n"[k == n - 1]
#define pp(c) for (auto& [f, s] : c) cerr << f << " : " << s << '\n'
#define pe(c) for (auto& e : c) cerr << e << ' '; cerr << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
#define ck(...) f(#__VA_ARGS__, __VA_ARGS__)
#define pc cout << "Case " << tc << ": "
const ll M = 1e9 + 7, N = 2e5 + 5;

void test(int tc) {
    ll a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, m = 0, n = 0, q = 0;
    cin >> n;
    ll ar[n]; for (i = 0; i < n; ++i) { cin >> ar[i]; }

    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int t = 0, tc = 1;
    cin >> tc;
    while (t < tc) test(++t);
    return 0;
}

