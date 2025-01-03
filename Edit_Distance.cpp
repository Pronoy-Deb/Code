#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ll long long
#define pe(c) for (auto e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "Yes" : "No") << '\n'
const ll M = 1e9 + 7, N = 5e3 + 5;

// int lcs(auto &s, auto &r) {
//     int l1 = s.size(), l2 = r.size(); set<int> in[30]{};
//     for (int i = l2 - 1; i >= 0; --i) in[r[i] - 'a'].insert(i + 1);
//     vector<int> pos(l1); int last = 1;
//     for (int i = 0; i < l1; ++i) {
//         int j = s[i] - 'a';
//         if (!in[j].empty()) {
//             auto it = in[j].lower_bound(last);
//             // pos[i] = in[j].back(); in[j].pop_back();
//             if (it == in[j].end()) {
//                 pos[i] = *in[j].begin(); in[j].erase(in[j].begin());
//             }
//             else {
//                 pos[i] = *it; in[j].erase(it);
//             }
//             last = pos[i];
//         }
//     }
//     ck(pos);
//     vector<int> ans; int i = 0; while (i < l1 && !pos[i]) ++i;
//     if (i == l1) return 0; ans.push_back(pos[i]);
//     while (i < l1) {
//         if (!pos[i]) { ++i; continue; }
//         if (pos[i] > ans.back()) ans.push_back(pos[i]);
//         else {
//             int low = lower_bound(ans.begin(), ans.end(), pos[i]) - ans.begin();
//             ans[low] = pos[i];
//         }
//         ++i;
//     }
//     return ans.size();
// }

int lcs(const string &s, const string &r) {
    // Map each character in `r` to its 1-based indices
    unordered_map<char, vector<int>> posMap;
    for (int i = 0; i < (int)r.size(); ++i) {
        posMap[r[i]].push_back(i + 1);
    }

    // Collect indices of `r` for characters in `s`
    vector<int> indices;
    for (char c : s) {
        if (posMap.count(c)) {
            indices.insert(indices.end(), posMap[c].begin(), posMap[c].end());
        }
    }

    // Debugging: print collected indices
    cout << "Collected indices: ";
    for (int x : indices) cout << x << " ";
    cout << endl;

    // Compute LIS on the collected indices
    vector<int> lis;
    for (int x : indices) {
        auto it = lower_bound(lis.begin(), lis.end(), x); // Find position to replace or extend
        if (it == lis.end()) {
            lis.push_back(x); // Extend LIS
        } else {
            *it = x; // Replace to maintain smallest possible valuelcs
        }

        // Debugging: print LIS after each step
        cout << "LIS after processing " << x << ": ";
        for (int y : lis) cout << y << " ";
        cout << endl;
    }

    return (int)lis.size();
}

void test(int32_t tc) {
    string s, r; cin >> s >> r;
    cout << lcs(s, r) << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}