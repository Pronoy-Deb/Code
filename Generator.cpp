#include <algorithm>
#include <iostream>
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

long double ranr(long double l, long double r) {
    random_device rd; mt19937_64 gen(rd());
    uniform_real_distribution<> dis(l, r);
    return dis(gen);
}
ll ran(ll l, ll r) {
    random_device rd; mt19937_64 gen(rd());
    uniform_int_distribution<ll> dis(l, r);
    return dis(gen);
    // return l + rand() % (r - l + 1);
}
const ll M = 1e9 + 7, N = 2e5 + 5;

void test() {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0;
    cout << 1 << '\n'; // For testcase input
    n = ran(1, 5); cout << n << '\n';
    // k = ran(1, 5); cout << k << '\n';
    for (i = 0; i < n; ++i) {
        cout << ran(1, 20) << ' ';
    }
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
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    // srand(chrono::high_resolution_clock::now().time_since_epoch().count());
    test();
    return 0;
}