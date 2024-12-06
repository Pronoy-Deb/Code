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
#include <ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<class T> using ost = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
void test(int32_t tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n;
    // vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    ost<int> st;
    while (n--) {
        char ch; cin >> ch >> a;
        if (ch == 'I') st.insert(a);
        else if (ch == 'C') cout << st.order_of_key(a) << '\n';
        else if (ch == 'K') {
            if (a > st.size()) cout << "invalid\n";
            else cout << *st.find_by_order(a-1) << '\n';
        }
        else {
            auto it = st.find(a); if (it != st.end()) st.erase(it);
        }
        ck(st);
    }
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}