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
    for(a=0;a<n;) {
        if(s[a] == '0') {
            if(a-2>=0 and a+1<n) {
                if(s[a-2] == '1' and s[a-1] == '1' and s[a+1] == '0') c++, a+=4;
                else a++;
            }
            else if(a-3>=0 and s[a-3] == '1' and s[a-2] == '1' and s[a-1] == '0') c++, a+=4;
            else a++;
        }
        else {
            if(a-1>=0 and a+2<n) {
                if(s[a-1] == '1' and s[a+1] == '0' and s[a+2] == '0') c++, a+=4;
            }
            else if(a+3<n and s[a+1] == '1' and s[a+2] == '0' and s[a+3] == '0') c++, a+=4;
            else a++;
        }
    }
    ck(tc, c);
    // d = c;
    cin >> q;
    while(q--) {
        cin >> a;
        a--;
        char ch; cin >> ch;
        // if(ch == s[a]) {
        //     ps(c>0);
        //     continue;
        // }
        // c = d;
        if(s[a] == '0') {
            if(a-2>=0 and a+1<n) {
                if(s[a-2] == '1' and s[a-1] == '1' and s[a+1] == '0') c--;
            }
            else if(a-3>=0 and s[a-3] == '1' and s[a-2] == '1' and s[a-1] == '0') c--;
        }
        else {
            if(a-1>=0 and a+2<n) {
                if(s[a-1] == '1' and s[a+1] == '0' and s[a+2] == '0') c--;
            }
            else if(a+3<n and s[a+1] == '1' and s[a+2] == '0' and s[a+3] == '0') c--;
        }
        ck(tc, c);
        s[a] = ch;
        if(s[a] == '0') {
            if(a-2>=0 and a+1<n) {
                if(s[a-2] == '1' and s[a-1] == '1' and s[a+1] == '0') c++;
            }
            else if(a-3>=0 and s[a-3] == '1' and s[a-2] == '1' and s[a-1] == '0') c++;
        }
        else {
            if(a-1>=0 and a+2<n) {
                if(s[a-1] == '1' and s[a+1] == '0' and s[a+2] == '0') c++;
            }
            else if(a+3<n and s[a+1] == '1' and s[a+2] == '0' and s[a+3] == '0') c++;
        }
        ck(tc, c);
        // for (i = min(0ll, a - 3); i+3<n and i <= a; ++i) {
        //     r = s.substr(i, 4);
        //     if(r == "1100") c++;
        // }
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