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

bool cmp(const pair<long long, long long> &a, const pair<long long, long long> &b) {
    if (a.first == b.first) return a.second < b.second;
    return a.first > b.first;
}

void test(int32_t tc) {
    ll n, k; cin >> n >> k;
    vector<pair<int, int>> ar(n); for (int i = 0; i < n; ++i) {
        int a; cin >> a; ar[i] = {a > k ? a % k : a, i + 1};
    }
    sort(ar.begin(), ar.end(), cmp);
    for (auto [f, s] : ar) cout << s << ' ';
    cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}