#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pe(c) for (auto &e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "BOB" : "ALICE") << '\n'
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
const ll M = 1e9 + 7, N = 2e5 + 5;

bool rec(int n, bool ck) {
    if(n == 0) return 1;
    if(n<0) return 0;
    if(!ck) {
        bool ck1 = rec(n - 1, 1);
        if(ck1) return rec(n-2, 1);
        else return 0;
    }
    else {
        bool ck1 = rec(n - 1, 0);
        if(ck1) return 1;
        else return rec(n - 2, 0);
    }
}

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n;
    // vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    ps(rec(n, 0));
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}