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

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> a >> b;
    // vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    string s; cin >> s;
    while(c < 150) {
        if (s[k] == 'N') j++;
        else if(s[k] == 'S') j--;
        else if(s[k] == 'E') i++;
        else i--;
        // ck(tc, i, j);
        if(i == a and j == b) {
            ps(1);
            return;
        }
        k++;
        if (k == n) k = 0;
        c++;
    }
    ps(0);
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}