#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const int64_t M = 1e9 + 7, N = 2e5 + 5;

void test(int32_t tc) {
    int64_t n, m; cin >> n >> m;
    int aa[n][m];
    // map<int, set<pair<int, int>>> pos;
    int cnt[n * m + 5]{};
    // fill(cnt, cnt + n * m + 5, 1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> aa[i][j];
            if (!cnt[aa[i][j]]) cnt[aa[i][j]] = 1;
            if (i and aa[i - 1][j] == aa[i][j]) {
                cnt[aa[i][j]]++;
            }
            else if (j and aa[i][j - 1] == aa[i][j]) {
                cnt[aa[i][j]]++;
            }
            // pos[aa[i][j]].insert({i, j});
        }
    }
    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < m; ++j) {
    //         else if (i < n - 1 and aa[i + 1][j] == aa[i][j]) cnt[aa[i][j]]++;
    //         else if (j < m - 1 and aa[i][j + 1] == aa[i][j]) cnt[aa[i][j]]++;
    //     }
    // }
    int mx = -M, ele = -1;
    for (int i = 0; i < n * m + 3; ++i) {
        if (cnt[i] > mx) {
            mx = cnt[i]; ele = i;
        }
    }
    int ans = 0;
    for (int i = 0; i < n * m + 3; ++i) {
        if (i == ele) continue;
        if (cnt[i] > 1) ans += 2;
        else if (cnt[i]) ans++;
    }
    cout << ans;
    // auto it = pos.begin();
    // while (it != pos.end()) {
    //     while (!it->second.empty()) {
    //         auto it1 = it->second.begin();
    //         while (it1 != it->second.end()) {
    //             auto [r, c] = *it1;
    //             if (r and aa[r - 1][c] == it->first or c and aa[r][c - 1] == it->first or r < n - 1 and aa[r + 1][c] == it->first or c < m - 1 and aa[r][c + 1] == it->first) {
    //                 continue;
    //             }
    //         }
    //     }
    // }
    cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}