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

void test(int32_t tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    string s; cin >> s;
    int cnt[10]{};
    n = s.size();
    for (i = 0; i < n; ++i) { cnt[s[i] - '0']++; c += s[i] - '0'; }
    a = c % 9;
    if (a) {
        a = 9 - a;
        if (a == 1) {
            ps((cnt[2] >= 5) or (cnt[3] and cnt[2] >= 2));
        }
         else if (a==2) {
            ps(cnt[2]);
        }
        else if(a==3) {
            ps(cnt[3] >= 2 or (cnt[3] and cnt[2] >= 3) or cnt[2] >= 6);
        }
        else if(a == 4) {
            ps(cnt[2] >= 2);
        }
        else if (a == 5){
            ps((cnt[2] >= 7) or (cnt[3] and cnt[2] >= 4) or (cnt[3] >= 2 and cnt[2]));
        }
        else if(a==6) {
            ps(cnt[2] >= 3 or cnt[3]);
        }
        else if(a==7) {
            ps((cnt[2] >= 2 and cnt[3] >= 2) or (cnt[2] >= 5 and cnt[3]) or (cnt[2] >= 8));
        }
        else if(a==8) {
            ps((cnt[2] and cnt[3]) or (cnt[2] >= 4));
        }
        else ps(0);
    }
    else ps(1);
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}