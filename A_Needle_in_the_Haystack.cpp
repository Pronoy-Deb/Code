#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const int64_t M = 1e9 + 7, N = 2e5 + 5;

auto kmp(auto &str, auto &pat) {
    int pl = pat.size(), sl = str.size(), sz = max(pl, sl) + 5, pi[sz], now = pi[0] = -1, match = 0;
    for (int i = 1; i < pl; ++i) {
        while (now != -1 && pat[now + 1] != pat[i]) now = pi[now];
        if (pat[now + 1] == pat[i]) ++now; pi[i] = now;
    }
    now = -1; vector<int> ind;
    for (int i = 0; i < sl; ++i) {
        while (now != -1 && pat[now + 1] != str[i]) now = pi[now];
        if (pat[now + 1] == str[i]) ++now;
        // match += (now == pl - 1);
        if(now == pl - 1) ind.emplace_back(i - pl + 1);  // To determine the indices
    }
    return ind;
}

void test(int32_t tc) {
    // int64_t n; cin >> n;
    // vector<int64_t> aa(n);
    // for (int i = 0; i < n; ++i) { cin >> aa[i]; }
    string s, p; cin >> s >> p;
    auto ans = kmp(s, p);
    int n = ans.size();
    if (!n) cout << "Not Found";
    else cout << n << '\n';
    for (auto x : ans) cout << x + 1 << ' ';
    cout << "\n\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}