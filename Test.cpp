#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ll long long
#define pe(c) for (auto e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const ll M = 1e9 + 7, N = 2e5 + 5;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<class T> using ost = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
bool contains(ost<int>& tree, int val) {
    int order = tree.order_of_key(val);
    return 0 <= order && order < tree.size() && *tree.find_by_order(order) == val;
}
void test(int32_t tc) {
    // ll n; cin >> n;
    // vector<ll> ar(n); for (int i = 0; i < n; ++i) { cin >> ar[i]; }
    ost<long long> st;
    st.insert(5);
    st.insert(215);
    st.insert(25);
    auto it = st.order_of_key(6);
    cout << it << '\n';
    for (auto e : st) cout << e << ' ';
    cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}