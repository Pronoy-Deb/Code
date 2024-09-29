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
long long bit[N][N]; set<pair<int, int>> ind;
void add(int x, int y, long long val) {
    for (; x < N; x += -x & x) {
        for (int j = y; j < N; j += -j & j) {
            // ind.insert({x, j});
            bit[x][j] += val;
        }
    }
}
long long get(int x, int y) {
    long long ans = 0;
    for (; x; x -= x & -x) {
        for (int j = y; j; j -= j & -j) ans += bit[x][j];
    }
    return ans;
}
long long get(int x1, int y1, int x2, int y2) {
    return get(x2, y2) - get(x1 - 1, y2) - get(x2, y1 - 1) + get(x1 - 1, y1 - 1);
}
void reset() { for (auto &[i, j] : ind) bit[i][j] = 0; ind.clear(); }

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> q;
    vector<string> v(n);
    for (i = 0; i < n; ++i) {
        cin >> v[i];
        for (j = 0; j < n; ++j) {
            if(v[i][j]=='*')
                add(i + 1, j + 1, 1);
        }
    }
    while(q--) {
        cin >> m; if(m&1) {
            cin >> a >> b;
            c = get(a, b, a, b);
            if(c) add(a, b, -1);
            else add(a, b, 1);
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