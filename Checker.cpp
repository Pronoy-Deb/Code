#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;
#define ll long long
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define pe(c) for (auto &e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const ll M = 1e9 + 7, N = 2e6;
ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0, inp[N], ar[N]; string s;

bool check(ifstream &fin) {
    // Read Output from Optimized.cpp
    fin >> m;
    for (i = 0; i < m; ++i) fin >> ar[i];
    for(i=0;i<n-1;++i) {
        if(abs(ar[i] - ar[i-1]) != 2) return false;
    }
    return true;
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    ifstream fin("inp", ifstream::in);
    // ifstream bf("out1", ifstream::in);
    ifstream op("out2", ifstream::in);
    // Read Input from Generator.cpp
    int tc; fin >> tc; // For testcase
    fin >> n;
    for (i = 0; i < n; ++i) fin >> inp[i];
    return (check(op) ? 0 : -1);
    // return (check(bf) == check(op) ? 0 : -1);
}