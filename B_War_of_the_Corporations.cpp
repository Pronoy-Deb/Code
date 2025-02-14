#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const int64_t M = 2147483647, N = 1e5 + 5;

int64_t bex(int64_t base, int64_t pow = M - 2) {
    base %= M; int64_t ans = 1;
    while (pow) {
        if (pow & 1) ans = (ans * base) % M;
        base = (base * base) % M; pow >>= 1;
    }
    return ans;
}
int64_t hs[N], pw[N], inv[N], n; string s;
void pre(int p = 31) {
    pw[0] = inv[0] = 1; int64_t pinv = bex(p);
    for (int i = 0; i < n; ++i) {
        pw[i + 1] = (pw[i] * p) % M;
        hs[i + 1] = (hs[i] + ((pw[i] * s[i]) % M)) % M;
        inv[i + 1] = (inv[i] * pinv) % M;
    }
}
inline int64_t get(int l, int r) { // 1-based range
    return ((hs[r] - hs[l - 1] + M) % M * inv[l - 1]) % M;
}
int64_t cfh(auto &s, int base = 31) {
    int64_t sz = s.size(), tmp = 0, pow = 1;
    for (int i = 0; i < sz; ++i) {
        tmp = (tmp + (s[i] * pow) % M) % M;
        pow = (pow * base) % M;
    }
    return tmp;
}

void test(int32_t tc) {
    string p; cin >> s >> p;
    n = s.size(); pre();
    int h = cfh(p), i = 1, c = 0, pl = p.size();
    while (i <= n) {
        int hh = get(i, i + pl - 1);
        if (hh == h) ++c, i += pl;
        else ++i;
    }
    cout << c << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}