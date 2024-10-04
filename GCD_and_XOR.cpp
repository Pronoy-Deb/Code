#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pe(c) for (auto &e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
const ll M = 1e9 + 7, N = 2e5 + 5;

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> k;
    vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    if(k == 1) {
        cout << 1 << '\n'; return;
    }
    if(n==1) {
        cout << (ar[0] != k) << '\n'; return;
    }
    i=0; d = k;
    while(i<n) {
        a = i;
        while (i < n and ar[i] != k and ar[i] % k == 0) {
            d = gcd(d, ar[i++]);
        }
        if (d == k) {
            while(a<i) ar[a++] = -1;
        }
        else {
            d = k;
        }
        ++i;
    }
    ck(ar);
    i=0; while(i<n and ar[i]==k) ++i; a = i; ++i;
    b = n - 1; while(b>=i and ar[b]==k) --b;
    while(i<=b) {
        while(i<=b and (ar[i] == k or ar[i] == ar[i-1])) ++i;
        ++c; ++i;
    }
    if((b>a and ar[b] != ar[b-1]) or (a==b and ar[a]!=k)) c++;
    cout << c << '\n';
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}