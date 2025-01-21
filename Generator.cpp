#include <algorithm>
#include <iostream>
#include <assert.h>
#include <random>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <set>
#include <map>
// #include <chrono>
using namespace std;
#define ll long long
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define pe(c) for (auto &e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n';

random_device rd; mt19937_64 gen(rd());
long double ranr(long double l, long double r) {
    assert(l <= r);
    uniform_real_distribution<> dis(l, r);
    return dis(gen);
}
ll ran(ll l, ll r) {
    assert(l <= r);
    uniform_int_distribution<ll> dis(l, r);
    return dis(gen);
    // return l + rand() % (r - l + 1);
}
const ll M = 1e9, N = 1e6;

void test(int tc) {
    ll n = ran(1, 10); cout << n << ' ';
    ll k = ran(1, n); cout << k << '\n';
    ll tot = 0;
    for (int i = 0; i < n; ++i) {
        ll a = ran(1, 10); cout << a << ' ';
        tot += a;
    }
    cout << '\n';
    ll sum = 0;
    for (int i = 0; i < k - 1; ++i) {
        ll a = ran(1, 10); cout << a << ' ';
        sum += a;
    }
    if (sum < tot) cout << tot - sum; else cout << 1;
    cout << '\n';
    // set<ll> st;
    // while (st.size() != n) {
    //     a = ran(1, 30);
    //     if (st.find(a) == st.end()) {
    //         cout << a << ' '; st.insert(a);
    //     }
    // }
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    // srand(chrono::high_resolution_clock::now().time_since_epoch().count());
    int tc = 0, tt = ran(1, 1);
    cout << tt << '\n'; // For testcase input
    while (tc++ < tt) test(tc);
    return 0;
}