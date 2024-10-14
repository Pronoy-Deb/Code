#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <set>
#include <map>
using namespace std;
#define ll long long
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define pe(c) for (auto &e : c) cerr << e << ' '; cerr << '\n'
#define ps(b) cerr << (b ? "YES" : "NO") << '\n';
ll m, n, q, ar[N], ar1[N]; string s;

auto ranr(auto l, auto r) {
    random_device rd; mt19937_64 gen(rd());
    uniform_real_distribution<> dis(l, r);
    return dis(gen);
}
auto ran(auto l, auto r) {
    random_device rd; mt19937_64 gen(rd());
    uniform_int_distribution<ll> dis(l, r);
    return dis(gen);
    // return l + rand() % (r - l + 1);
}
const ll M = 1e9 + 7, N = 2e5 + 5;

auto bruteForce() {
    ll a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0;

    return ;
}

auto optimized() {
    ll a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0;

    return ;
}

void test() {
    int tc = 0, t = 10000;
    while (++tc <= t) {
        n = ran(1, 10);
        // for (i = 0; i < n; ++i) { ar[i] = ran(1, 100); }
        auto bf = bruteForce(), op = optimized();
        if (bf != op) {
            cerr << "Wrong answer on test " << tc << "\nInput:\n";
            cerr << n;
            cerr << "\nExpected:\n";
            ck(bf);
            cerr << "\nFound:\n";
            ck(op);
            return;
        }
        cerr << "Passed test " << tc << " / " << t << '\n';
    }
    cerr << "Pretests passed successfully!\n";
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    test();
    return 0;
}