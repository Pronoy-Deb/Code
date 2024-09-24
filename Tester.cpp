#include <bits/stdc++.h>
using namespace std;
#include "def.h"
#define ll long long
#define pe(c) for (auto &e : c) cerr << e << ' '; cerr << '\n'
auto ps(auto b) { return (b ? "YES" : "NO"); }
const ll M = 1e9 + 7, N = 2e5 + 5;
ll m, n, q, ar[N], ar1[N]; string s;

long long ran(long long a, long long b) {
    random_device rd; mt19937_64 gen(rd());
    uniform_int_distribution<long long> distrib(a, b);
    return distrib(gen);
    // return a + rand() % (b - a + 1);
}

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
    cerr << "All tests passed successfully!\n";
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    // auto now = chrono::high_resolution_clock::now();
    // auto ns = chrono::duration_cast<chrono::nanoseconds>(now.time_since_epoch()).count();
    // srand(ns);
    test();
    return 0;
}