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

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cout << "Case " << tc << ": ";
    cin >> a >> b >> c;
    // vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    if (a==0) {
        if ((b == 3 and c == 6) or (b == 6 and c == 3) or (b == 4 and c == 4)) cout << "perfectus";
        else cout << "invalidum";
    }
    else if(a == 1) {
        if ((b == 3 and c == 4) or (b == 4 and c == 3) or (b == 2 and c == 4) or (b == 4 and c == 2) or (b==1 and c==6) or (b==6 and c==1)) cout << "perfectus";
        else cout << "invalidum";
    }
    else if (a == 3) {
        if ((b == 3 and c == 3) or (b == 0 and c == 6) or (b == 6 and c == 0) or (b == 1 and c == 4) or (b == 4 and c == 1)) cout << "perfectus";
        else cout << "invalidum";
    }
    else if (a == 2) {
        if ((b == 2 and c == 2) or (b == 1 and c == 4) or (b == 4 and c == 1)) cout << "perfectus";
        else cout << "invalidum";
    }
    else if(a == 4) {
        if ((b == 0 and c == 4) or (b == 4 and c == 0) or (b == 1 and c == 3) or (b == 3 and c == 1) or (b==2 and c==1) or (b == 1 and c==2)) cout << "perfectus";
        else cout << "invalidum";
    }
    else if (a==6) {
        if((b == 0 and c == 3) or (b == 3 and c == 0) or (b == 1 and c == 1)) cout << "perfectus";
        else cout << "invalidum";
    }
    else cout << "invalidum";
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}