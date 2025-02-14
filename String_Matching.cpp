#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const int64_t N = 1e6 + 5;

const int64_t M = 9223372036854775783ll;
__int128_t bex(__int128_t base, __int128_t pow = M - 2) {
    base %= M; __int128_t ans = 1;
    while (pow) {
        if (pow & 1) ans = (ans * base) % M;
        base = (base * base) % M; pow >>= 1;
    }
    return ans;
}
__int128_t hs[N], pw[N], inv[N], n; string s;
void pre(int p = 31) {
    pw[0] = inv[0] = 1; __int128_t pinv = bex(p);
    for (int i = 0; i < n; ++i) {
        pw[i + 1] = (pw[i] * p) % M;
        hs[i + 1] = (hs[i] + ((pw[i] * (s[i] - 96)) % M)) % M;
        inv[i + 1] = (inv[i] * pinv) % M;
    }
}
inline int64_t get(int l, int r) {
    return ((hs[r] - hs[l] + M) % M * inv[l]) % M;
}
__int128_t cfh(auto &s, int base = 31) {
    __int128_t sz = s.size(), tmp = 0, pow = 1;
    for (int i = 0; i < sz; ++i) {
        tmp = (tmp + ((s[i] - 96) * pow) % M) % M;
        pow = (pow * base) % M;
    }
    return tmp;
}
void test(int32_t tc) {
    cin >> s; n = s.size();
    pre();
    string r; cin >> r; int64_t hh = cfh(r);
    int c = 0;
    for (int i = r.size(), sz = i; i <= n; ++i) {
        int64_t h = get(i - sz, i);
        c += (h == hh);
    }
    cout << c;
    cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}