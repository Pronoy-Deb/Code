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
    // int64_t n; cin >> n;
    // vector<int64_t> ar(n);
    // for (int i = 0; i < n; ++i) { cin >> ar[i]; }
    string s; cin >> s;
    int n = s.size();
    for (int i = n - 1; i > 0; --i) {
        if(s[i] == s[i-1]) {
            cout << 1 << '\n'; return;
        }
    }
    cout << n;
    cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}