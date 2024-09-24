#include <bits/stdc++.h>
using namespace std;
template <typename a> void f(char *x, a &&r) { cout << x << " = " << r << '\n'; }template <typename a, typename...A> void f(char *x, a &&r, A &&...g) { char *c = strchr(x + 1, ','); cout.write(x, c - x) << " = " << r << ','; f(c + 1, g...); }
#define pr(c) for (auto& r:c) { for (auto& e:r) cout << e << ' '; cout << '\n'; }
#define pn(c, n) for (k = 0; k < n; ++k) cout << c[k] << " \n"[k == n - 1]
#define pp(c) for (auto& [f, s] : c) cout << f << " : " << s << '\n'
#define pe(c) for (auto& e : c) cout << e << ' '; cout << '\n'
#define pc(t, n) cout << "Case " << t << ": " << n << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
#define ck(...) f(#__VA_ARGS__, __VA_ARGS__)
#define ll long long int
const int M = 1e9 + 7, N = 2e5 + 5;

void Test(int tc) {
    ll a = 0, b = 0, c = 0, d = 0, i = -1, j = -1, k = -1, m = 0, n = 0;
    cin >> n>>m;
    ll ar[n]; while (++i < n) { cin >> ar[i]; }
    for (i = 0; i < m;++i){
        cin >> a;
        c = max(c, a);
    }
    sort(ar + n-c, ar + n);
    pe(ar);
    // cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (++tc <= t) Test(tc);
    return 0;
}