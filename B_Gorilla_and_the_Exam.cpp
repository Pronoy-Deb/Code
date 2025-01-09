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

struct chash {
	const uint64_t C = uint64_t(2e18) + 71, R = chrono::high_resolution_clock::now().time_since_epoch().count();
	size_t operator()(uint64_t x) const {
		return __builtin_bswap64((x ^ R) * C);
	}
};

void test(int32_t tc) {
    ll n, k; cin >> n >> k; unordered_map<ll, ll, chash> mp;
    for (int i = 0; i < n; ++i) { int a; cin >> a; ++mp[a]; }
    multimap<ll, ll> mm;
    for (auto [a, b] : mp) mm.insert({b, a});
    auto it = mm.begin();
    while (k > 0 and it != mm.end() and mm.size() > 1) {
        auto [f, s] = *prev(mm.end());
        if (it->first <= k) {
            mm.erase(prev(mm.end()));
            mm.insert({it->first + f, s}), k -= it->first;
            it = mm.erase(it);
        }
        else break;
    }
    cout << max(1, (int)mm.size()) << '\n';
    // cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}