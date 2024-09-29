#include <bits/stdc++.h>
using namespace std;
#include "def.h"
#define ll long long
#define pe(c) for (auto &e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const ll M = 1e9 + 7, N = 2e5 + 5;
ll a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, m = 0, n = 0, q = 0, ar[N], ar1[N]; string s;

bool check(ifstream &fin) {
    // Read Output
    fin >> a;
    for (i = 0; i < a; ++i) fin >> ar1[i];
    for (i = 0; i < a - 1; ++i) {
        if((ar1[i] | ar1[i+1]) != n or ar1[i+1] <= ar1[i])
            return false;
    }
    return true;
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    ifstream fin("inp", ifstream::in), bf("out1", ifstream::in), op("out2", ifstream::in);
    ll tc; fin >> tc; // For testcase (Read Input from Generator)
    fin >> n;
    // for (i = 0; i < n; ++i) fin >> ar[i];
    return (check(op) ? -1 : 0);
}