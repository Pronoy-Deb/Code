#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pe(c) for (auto &e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
const ll M = 1e9 + 7, N = 1e3 + 5;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T> using ost = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ost<pair<int, int>> bit[N];
void on(int x, int y) {
	for(int i = x; i < N; i += i & -i) bit[i].insert({y, x});
}
void off(int x, int y) {
	for(int i = x; i < N; i += i & -i) bit[i].erase({y, x});
}
int get(int x, int y) {
	int ans = 0; ++y;
    for(int i = x; i > 0; i -= i & -i) ans += bit[i].order_of_key({y, 0});
	return ans;
}
long long get(int x1, int y1, int x2, int y2) {
    return get(x2, y2) - get(x1 - 1, y2) - get(x2, y1 - 1) + get(x1 - 1, y1 - 1);
}

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> q;
    vector<string> v(n);
    for (i = 0; i < n; ++i) {
        cin >> v[i];
        for (j = 0; j < n; ++j) {
            if(v[i][j]=='*') on(i + 1, j + 1);
        }
    }
    while(q--) {
        cin >> m; if(m&1) {
            cin >> a >> b;
            if(v[a-1][b-1] == '*'){
                off(a, b);
                v[a - 1][b - 1] = '.';
            }
            else {
                on(a, b);
                v[a-1][b-1]='*';
            }
        }
        else {
            cin >> a >> b >> c >> d;
            cout << get(a, b, c, d) << '\n';
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