#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const int64_t M = 1e9 + 7, N = 1e5 + 5;

bitset<N> mask[26], oc;
void pre(string &s) {
    for (int i = 0; s[i]; ++i) mask[s[i] - 'a'][i] = true;
}
inline void up(string &s, int in, char ch) {
    mask[s[in] - 'a'][in] = false; s[in] = ch;
    mask[s[in] - 'a'][in] = true;
}
int match(string &p, int l, int r) {
    int sz = p.size(); if (sz > r - l + 1) return 0; oc.set();
    for (int i = 0; p[i]; ++i) oc &= (mask[p[i] - 'a'] >> i);
    return (oc >> (l - 1)).count() - (oc >> (r - sz + 1)).count();
}
vector<int> posi(string &p, int l, int r) {
    int l1 = p.size(); if (l1 > r - l + 1) return {};
    vector<int> positions(match(p, l, r));
    int pos = oc._Find_next(l - 2), i = 0, l2 = positions.size();
    while (pos < r && i < l2) {
        positions[i++] = pos + 1; pos = oc._Find_next(pos);
    }
    return positions;
}

void test(int32_t tc) {
    string s; cin >> s; pre(s);
    int64_t n = s.size(), q; cin >> q;
    while (q--) {
        int k; string r; cin >> k >> r;
        auto v = posi(r, 1, n);
        int l1 = r.size(), ans = M, l2 = v.size();
        for (int i = 0; i + k - 1 < l2; ++i) {
            ans = min(ans, v[i + k - 1] + l1 - v[i]);
        }
        cout << (ans == M ? -1 : ans);
        cout << '\n';
    }
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}