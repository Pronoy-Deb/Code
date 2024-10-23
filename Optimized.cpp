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
struct cmp {
    bool operator() (const pair<ll, ll> &a, const pair<ll, ll> &b) const {
        return a.second < b.second;
    }
};
void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n;
    multiset<pair<ll,ll>> st;
    multiset<pair<ll,ll>, cmp> st1;
    for (i = 0; i < n; ++i) {
        cin >> a >> b;
        st.insert({a, b});
        st1.insert({a, b});
    }
    for(auto &[f, s] : st1) cerr << f << ' ' << s << ' ';
    cerr << endl;
    while (!st.empty() and !st1.empty()) {
        if(!st1.empty()) {
            cout << st1.begin()->first << ' ' << st1.begin()->second << ' ';
            st.erase(st.find(*st1.begin()));
            st1.erase(st1.begin());
        }
        if(!st.empty()) {
            cout << st.begin()->first << ' ' << st.begin()->second << ' ';
            st1.erase(st1.find(*st.begin()));
            st.erase(st.begin());
        }
    }
    cout << '\n';
    // ck(st.size());
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}