#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ll long long
#define pe(c) for (auto &e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const ll M = 1e9 + 7, N = 2e5 + 5;

bool ok(ll n, auto v) {
    while(n) {
        int a = n % 10;
        if(v.find(a) == v.end()) return false;
        v.erase(v.find(a));
        n /= 10;
    }
    return true;
}

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    // cin >> n;
    // vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    for (i = 1;i<N;++i) {
        int a = i;
        multiset<int> v;
        while(a) {
            v.insert(a%10);
            a /= 10;
        }
        if(ok(2*i, v) and ok(3*i, v) and ok(4*i, v) and ok(5*i, v) and ok(6*i, v)){
            cout << i << '\n';
            return;
        }
    }
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}