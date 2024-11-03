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
    cin >> n;
    // vector<ll> ar(n);
    multiset<ll> st;
    multiset<ll> st1;
    for (i = 0; i < n; ++i) { cin >> a; st.insert(a); st1.insert(a); }
    a = *st.lower_bound((*prev(st.end()) / 2) + 1);
    while(*st.begin() + *next(st.begin()) <= *prev(st.end())) {
        c++;
        st.erase(st.begin());
        st.insert(a);
    }
    // a = *st1.lower_bound((*st1.begin() + *next(st1.begin())) - 1);
    while(*st1.begin() + *next(st1.begin()) <= *prev(st1.end())) {
        d++;
        st1.erase(--st1.end());
        st1.insert(*next(st1.begin()));
    }
    ck(c, d);
    cout << min(c, d);
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}