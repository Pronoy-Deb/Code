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
    cin >> n >> k;
    map<ll, ll> mp;
    vector<ll> ar(k); for (i = 0; i < k; ++i) { cin >> a >> b; mp[a] += b; }
    vector<ll> v;
    for(auto &e : mp) {
        v.push_back(e.second);
    }
    sort(v.rbegin(), v.rend());
    a = v.size();
    for(i=0;i<min(a, n);++i) c+=v[i];
    cout << c;
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}