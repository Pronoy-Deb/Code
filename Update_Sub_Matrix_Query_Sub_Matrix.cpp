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

long long pro[N][N][2], sum[N][N][2]; set<pair<int, int>> ind;
void up2(long long t[N][N][2], int x, int y, long long mul, long long add) {
    for(int i = x; i < N; i += i & -i) {
        for(int j = y; j < N; j += j & -j) {
            t[i][j][0] += mul; t[i][j][1] += add;
            // ind.insert({i, j});
        }
    }
}
void up1(int x, int y1, int y2, long long mul, long long add) {
    up2(pro, x, y1, mul, -mul * (y1 - 1)); up2(pro, x, y2, -mul, mul * y2);
    up2(sum, x, y1, add, -add * (y1 - 1)); up2(sum, x, y2, -add, add * y2);
}
void add(int x1, int y1, int x2, int y2, long long val) {
    up1(x1, y1, y2, val, -val * (x1 - 1)); up1(x2, y1, y2, -val, val * x2);
}
long long get2(long long t[N][N][2], int x, int y) {
    long long mul = 0, add = 0;
    for(int i = y; i > 0; i -= i & -i) { mul += t[x][i][0]; add += t[x][i][1]; }
    return mul * y + add;
}
long long get1(int x, int y) {
    long long mul = 0, add = 0;
    for(int i = x; i > 0; i -= i & -i) { mul += get2(pro, i, y); add += get2(sum, i, y); }
    return mul * x + add;
}
long long get(int x1, int y1, int x2, int y2) {
    return get1(x2, y2) - get1(x1 - 1, y2) - get1(x2, y1 - 1) + get1(x1 - 1, y1 - 1);
}
void reset() { for (auto &[i, j] : ind) pro[i][j][0] = pro[i][j][1] = sum[i][j][0] = sum[i][j][1] = 0; ind.clear(); }

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    // cin >> n;
    // vector<ll> v(n); for (i = 0; i < n; ++i) { cin >> v[i]; }
    cin >> n >> q;
    // for(i = 1; i <= n; i++) {
    //     for(j = 1; j <= m; j++) {
    //         cin >> k; add(i, j, i, j, k);
    //     }
    // }
    // cin >> q;
    while (q--) {
        int ty, x1, y1, x2, y2; cin >> ty;
        if(ty == 2) {
            long long val; cin >> x1 >> y1 >> x2 >> y2 >> val;
            add(x1, y1, x2, y2, val);
        }
        else {
            cin >> x1 >> y1 >> x2 >> y2;
            cout << get(x1, y1, x2, y2) << '\n';
        }
    }
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}