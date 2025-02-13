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
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ps(b) cout << (b ? "YES" : "NO") << '\n'

random_device rd; mt19937_64 gen(rd());
long double ranr(long double l, long double r) {
    assert(l <= r);
    uniform_real_distribution<> dis(l, r);
    return dis(gen);
}
int64_t ran(int64_t l, int64_t r) {
    assert(l <= r);
    uniform_int_distribution<int64_t> dis(l, r);
    return dis(gen);
    // return l + rand() % (r - l + 1);
}
const int64_t M = 1e9, N = 1e6;

void test(int32_t tc) {
    int64_t n = ran(1, 10); cout << n << ' ';
    int64_t k = ran(1, 11); cout << k << '\n';
    for (int i = 0; i < n; ++i) {
        int64_t a = ran(1, 10); cout << a << ' ';
    }
    cout << '\n';
    cout << ran(1, 10) << '\n';
    // int64_t sum = 0;
    // for (int i = 0; i < k - 1; ++i) {
    //     int64_t a = ran(1, 10); cout << a << ' ';
    //     sum += a;
    // }
    // if (sum < tot) cout << tot - sum; else cout << 1;
    // cout << '\n';
    // set<int64_t> st;
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
    int32_t tc = 0, tt = ran(1, 1);
    cout << tt << '\n'; // For testcase input
    while (tc++ < tt) test(tc);
    return 0;
}