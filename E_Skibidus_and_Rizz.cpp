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
    int64_t n, m, k; cin >> n >> m >> k;
    int sz = n + m;
    // vector<int64_t> ar(n);
    // for (int i = 0; i < n; ++i) { cin >> ar[i]; }
    string s; bool ok = (m > n);
    if (m > n) {
        for (int i = 0; m and i < k; ++i) {
            s += to_string(1); m--;
            if (m == n) break;
        }
    } else {
        for (int i = 0; n and i < k; ++i) {
            s += to_string(0); n--;
            if (m == n) break;
        }
    }
    ok = !ok;
    while (m or n) {
        if (m == n) {
            while (m or n) {
                for (int i = 0; (ok ? m : n) and i < k; ++i) {
                    s += to_string(ok); ok ? m-- : n--;
                }
                ok = !ok;
            }
            break;
        }
        if (ok) {
            for (int i = 0; m and i < k; ++i) {
                s += to_string(1); m--;
                if (m == n) break;
            }
            ok =!ok;
        } else {
            for (int i = 0; n and i < k; ++i) {
                s += to_string(0); n--;
                if (m == n) break;
            }
            ok =!ok;
        }
    }
    int c = 0, d = 0, i = sz - 1;
    while (i >= 0 and s[i] == s[sz - 1]) ++c, --i;
    int j = i;
    while (j >= 0 and s[j] == s[i]) ++d, --j;
    i = j;
    while (i >= 0 and s[i] == s[sz - 1]) ++c, --i;
    if (c - d > k) cout << -1;
    else cout << s;
    cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}