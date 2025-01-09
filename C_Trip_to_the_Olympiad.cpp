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

void test(int32_t tc) {
	ll l, r; cin >> l >> r;
    ll a = r & (1ll << (int)log2(r)), d = log2(a);
    ll b = 0;
    for (int i = 0; i < d; ++i) b |= (1LL << i);
    ll c = 0;
    for (int i = 0; c < l or !c; ++i) c |= (1LL << i);
    if (a >= l and a <= r and b >=l and b <=r and c >=l and c <=r ) {
        cout << a << ' ' << b << ' ' << c;
        cout << '\n';
        return;
    }
    a = r; ll tot = 0;
    vector<int> v;
    for (int i = 0; i < d; ++i) {
        if ((r & (1LL << i))) {
            tot |= (1LL << i);
            if (tot > r - l) break;
            a ^= (1LL << i);
            v.push_back(i);
            // if (a >= r) {
            //     a &= (~(1LL << i));
            //     break;
            // }
        }
    }
    ck(a, v);
    if (!v.empty()) {
        for (int i = v[0] + 1; i < v.back(); ++i) {
            if ((r & (1LL << i)) == 0) {
                a |= (1LL << i);
            }
        }
    }
    ll e = a; d = log2(a);
    for (int i = 0; i < d; ++i) {
        if ((a & (1LL << i))) {
            e ^= (1LL << i);
            break;
        }
    }
    cout << r << ' ' << a << ' ' << e;
    cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}