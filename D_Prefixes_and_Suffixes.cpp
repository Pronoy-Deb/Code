#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const int64_t M = 1e9 + 7, N = 2e5 + 5;

auto prefix(auto &s) {
    int n = s.size(); vector<int> pi(n);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        j += (s[i] == s[j]); pi[i] = j;
    }
    return pi;
}
auto pref_occur(auto &pi) {
    int n = pi.size(); vector<int> cnt(n + 1);
    for (int i = 0; i < n; ++i) ++cnt[pi[i]];
    for (int l = n; l > 0; --l) {
        cnt[pi[l - 1]] += cnt[l]; ++cnt[l];
    }
    return cnt;
}

void test(int32_t tc) {
    // int64_t n; cin >> n;
    // vector<int64_t> aa(n);
    // for (int i = 0; i < n; ++i) { cin >> aa[i]; }
    string s; cin >> s;
    auto pi = prefix(s), pre = pref_occur(pi);
    vector<int> res;
    for (int i = s.size(); i > 0; i = pi[i - 1]) res.push_back(i);
    reverse(res.begin(), res.end());
    cout << res.size() << '\n';
    for (auto x : res) cout << x << ' ' << pre[x] << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}