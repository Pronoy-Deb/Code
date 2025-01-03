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
const ll M = 1e9 + 7, N = 5e5 + 5;

long long ar[N], n;
int lis() {
    vector<long long> ans; ans.push_back(ar[0]);
    for (int i = 1; i < n; ++i) {
        if (ar[i] > ans.back()) ans.push_back(ar[i]);
        else {
            int low = lower_bound(ans.begin(), ans.end(), ar[i]) - ans.begin();
            ans[low] = ar[i];
        }
    }
    return (int)ans.size();
}

void test(int32_t tc) {
    ll k; cin >> k;
    // vector<ll> ar(n); for (int i = 0; i < n; ++i) { cin >> ar[i]; }
    string s, r; cin >> s >> r;
    int a = s.size(), b = r.size();
    n = a;
    int in[30]{};
    for (int i = 0; i < b; ++i) {
        if (in[r[i] - 'a'] == 0) in[r[i] - 'a'] = i + 1;
    }
    for (int i = 0; i < a; ++i) {
        ar[i] = in[s[i] - 'a'];
    }
    // pn(ar, a);
    ps(max(a, b) - lis() <= k);
    // cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}