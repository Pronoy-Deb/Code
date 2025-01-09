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

inline unsigned long long onmsb(unsigned long long n) {
    return n ? (1ull << (bit_width(n) - 1)) : 0;
}
void test(int32_t tc) {
	ll l, r; cin >> l >> r;
    ll a = onmsb(r), d = log2(a);
    ll b = 0;
    for (int i = 0; i < d; ++i) b |= (1LL << i);
    ll c = 0;
    for (int i = 0; c < l or !c; ++i) c |= (1LL << i);
    cout << a << ' ' << b << ' ' << c;
    cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}