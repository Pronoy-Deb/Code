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
int mex(auto &v) {
    set<int> st(v.begin(), v.end());
    int i = 0;
    while (st.find(i) != st.end())
        ++i;
    return i;
}
void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> d >> a;
    vector<ll> ar; for(i=0;i<n;++i) {
        ar.push_back(a);
        a += d;
    }
    c = 0;
    while (1) {
        if(k>n) {
            cout << -1 << '\n';
            return;
        }
        bool ok = 1;
        for (i = 0; i < n; ++i) {
            sort(ar.begin(), ar.end());
            if(ar[i]!=i) {
                ok = 0;
                break;
            }
        }
        if(ok) {
            cout << c << '\n';
            return;
        }
        ar[n-1] = mex(ar);
        c++;
        k++;
    }
    cout << c << '\n';
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}