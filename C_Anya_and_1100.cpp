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

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    string s, r; cin >> s;
    n = s.size();
    if(n<4) {
        cin >> q;
        while(q--) {
            cin >> a >> b;
            ps(0);
        }
        return;
    }
    // for(i=0;i<4;++i) r+=s[i];
    // if (r == "1100") c++;
    for(i=0;i<n;) {
        r = "";
        for (j = i, k = 0; j < n and k < 4; ++k, ++j) {
            r += s[j];
        }
        if(r == "1100") {
            c++;
            i+=4;
        }
        else i++;
    }
    // ck(c);
    // d = c;
    cin >> q;
    while(q--) {
        cin >> a;
        a--;
        char ch; cin >> ch;
        if(ch == s[a]) {
            ps(c>0);
            continue;
        }
        // c = d;
        for (i = min(0ll, a - 3); i<n and i <= a; ++i) {
            r = "";
            for (j = i, k = 0; j < n and k < 4; ++k, ++j) {
                r += s[j];
            }
            // ck(r);
            if(r == "1100") c--;
        }
        s[a] = ch;
        for (i = min(0ll, a - 3); i<n and i <= a; ++i) {
            r = "";
            for (j = i, k = 0; j < n and k < 4; ++k, ++j) {
                r += s[j];
            }
            // ck(r);
            if(r == "1100") c++;
        }
        ps(c > 0);
        // s[a] = ch2;
    }
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}