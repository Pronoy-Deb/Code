#include <bits/stdc++.h>
using namespace std;
#include "def.h"
#define ll long long
#define pe(c) for (auto &e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n';
const ll M = 1e9 + 7, N = 2e5 + 5;

auto ran(auto l, auto r) {
    random_device rd; mt19937_64 gen(rd());
    uniform_int_distribution<ll> dis(l, r);
    // uniform_real_distribution<> dis(l, r);
    return dis(gen);
    // return l + rand() % (r - l + 1);
}

void test() {
    ll a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, m = 0, n = 0, q = 0;
    cout << 1 << '\n'; // For testcase input
    n = ran(1, 10);
    cout << n << ' ';
    // k = ran(1, 5);
    // cout << k << '\n';
    // for (i = 0; i < n; ++i) {
    //     cout << ran(1, 5) << ' ';
    // }
    cout << '\n';
    // while(k--) {
    //     a = ran(1, n); cout << a << ' ';
    //     a = ran(a, n); cout << a << '\n';
    // }
    // set<ll> st;
    // while (st.size() != n) {
    //     ll a = ran(1, 30);
    //     if (st.find(a) == st.end()) {
    //         cout << a << ' '; st.insert(a);
    //     }
    // }
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    test();
    // auto now = chrono::high_resolution_clock::now();
    // auto ns = chrono::duration_cast<chrono::nanoseconds>(now.time_since_epoch()).count();
    // srand(ns);
    return 0;
}