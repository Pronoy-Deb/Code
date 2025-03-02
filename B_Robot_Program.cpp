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
    int64_t n, x, k; cin >> n >> x >> k;
    // vector<int64_t> aa(n);
    // for (int i = 0; i < n; ++i) { cin >> aa[i]; }
    string s; cin >> s;
    int64_t i = 0, cor = x, zero = (x == 0), sec = 0;
    while (i < n) {
        if (s[i] == 'L') {
            --cor;
        }
        else {
            ++cor;
        }
        if (cor == 0) {
            if (zero) {
                ++zero; k -= (sec + 1);
                if (k <= 0) {
                    cout << zero << '\n'; return;
                }
                k /= (i + 1);
                zero += k;
                cout << zero << '\n'; return;
            }
            ++zero; i = 0;
        }
        else {
            ++i;
        }
        ++sec;
        if (sec == k) break;
    }
    ck(zero, sec, cor);
    cout << zero;
    cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}