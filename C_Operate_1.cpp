#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ll long long
#define pe(c) for (auto e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "Yes" : "No") << '\n'
const ll M = 1e9 + 7, N = 2e5 + 5;

void test(int32_t tc) {
    ll k; cin >> k;
    // vector<ll> ar(n); for (int i = 0; i < n; ++i) { cin >> ar[i]; }
    string s,r ; cin >> s >> r;
    int n = s.size(), m = r.size();
    if (abs(n - m) > k) {
        ps(0);
        return;
    }
    if (n == m) {
        int c = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i]!=r[i]) ++c;
            if (c > k) {
                ps(0);
                return;
            }
        }
        ps(1);
    }
    else if (n < m) {
        int i = 0, j = 0, c = 0;
        while (j < m) {
            if (s[i] != r[j]) ++c, ++j;
            else ++i, ++j;
            if (c > k) {
                ps(0);
                return;
            }
        }
        ps(1);
    }
    else {
        int i = 0, j = 0, c = 0;
        while (i < n) {
            if (s[i] != r[j]) ++c, ++i;
            else ++i, ++j;
            if (c > k) {
                ps(0);
                return;
            }
        }
        ps(1);
    }
    // cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}