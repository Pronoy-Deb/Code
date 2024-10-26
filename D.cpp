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
string mul(auto &s, auto &s1) {
    if (s == "0" || s1 == "0") return "0";
    int sz = s.size() - 1, sz1 = s1.size() - 1, car = 0; string pro;
    for (int i = 0; i <= sz + sz1 || car; ++i) {
        int tmp = min(i, sz);
        for (int j = max(0, i - sz1); j <= tmp; ++j)
            car += (s[sz - j] - 48) * (s1[sz1 - i + j] - 48);
        pro += (car % 10 + 48);
        car /= 10;
    }
    reverse(pro.begin(), pro.end()); return pro;
}
string str(auto n) {
    if (!n) return "0"; string s;
    while (n) {
        s += ((n % 10) + 48); n /= 10;
    }
    reverse(s.begin(), s.end()); return s;
}
void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    // cin >> n;
    // vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    for (i = 1; i < 100;++i) {
        string s = str(i), ans = "1";
        for (j = 1;j<100;++j) {
            // string r = to_string(j);
            // for(k=0;k<j;++k)
            ans = mul(ans, s);
            // ck(ans);
            a = 0;
            for(auto &e : ans) {
                a += (e - '0');
            }
            c = max(c, a);
        }
    }
    cout << c;
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}