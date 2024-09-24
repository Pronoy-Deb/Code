#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pe(c) for (auto &e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
#define pc cout << "Case " << tc << ": "
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
const ll M = 1e9 + 7, N = 2e5 + 5;
#include <ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T> using oset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

int n, ar[N]; oset<int> tre[N << 2];
void make(int nd = 0, int l = 0, int r = n - 1) {
    if (l == r) { tre[nd].insert(ar[l]); return; }
    int m = (l + r) >> 1, lc = (nd << 1) + 1, rc = lc + 1;
    make(lc, l, m); make(rc, m + 1, r);
    for (int i = l; i <= r; ++i) tre[nd].insert(ar[i]);
}
void up(int in, int val, int nd = 0, int l = 0, int r = n - 1) {
    if (l == r) {
        tre[nd].erase(tre[nd].upper_bound(ar[in])); tre[nd].insert(val); return;
    }
    int m = (l + r) >> 1, lc = (nd << 1) + 1, rc = lc + 1;
    if (in <= m) up(in, val, lc, l, m);
    else up(in, val, rc, m + 1, r);
    tre[nd].erase(tre[nd].upper_bound(ar[in])); tre[nd].insert(val);
}
int get(int lx, int rx, int x, int nd = 0, int l = 0, int r = n - 1) {
    if (l > rx || r < lx) return 0;
    if (l >= lx && r <= rx) return tre[nd].order_of_key(x + 1);
    int m = (l + r) >> 1, lc = (nd << 1) + 1, rc = lc + 1;
    return get(lx, rx, x, lc, l, m) + get(lx, rx, x, rc, m + 1, r);
}

void test(int tc) {
    ll a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, m = 0, q = 0;
    cin >> n >> q;
    for (i = 0; i < n; ++i) { cin >> ar[i]; }
    make();
    while(q--) {
        char ch; cin >> ch >> a >> b;
        if(ch == '!') {
            up(a - 1, b); ar[a - 1] = b;
        }
        else {
            c = get(0, n - 1, b), d = get(0, n - 1, a - 1);
            cout << c - d << '\n';
        }
    }
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}