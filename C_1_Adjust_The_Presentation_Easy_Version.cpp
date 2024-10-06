#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pe(c) for (auto &e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "YA" : "TIDAK") << '\n'
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
const ll M = 1e9 + 7, N = 2e5 + 5;

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> m >> k;
    vector<ll> in(n + 5), ar1(n), pre(n + 5);
    for (i = 0; i < n; ++i) {
        cin >> b; in[b] = i; ar1[i] = b;
        if(!i) {
            a = b, pre[b] = -1;
        }
        else pre[b] = ar1[i - 1];
    }
    ck(in, a);
    bool vis[n + 5]{}, ck = 1;
    vector<ll> ar(m);
    for (i = 0; i < m; ++i) {
        cin >> ar[i];
        if(ar[i] != a) {
            if (pre[ar[i]] == a) {
                pre[a] = ar[i];
                a = ar[i];
            }
            else if(vis[ar[i]]) {
                pre[a] = ar[i];
                if(in[ar[i]] < n - 1) {
                    pre[ar1[in[ar[i]] + 1]] = ar[i];
                }
                a = ar[i];
            }
            else ck = 0;
            ck(tc, i, ck);
        }
        pre[a] = -1;
        vis[ar[i]] = 1;
    }
    ps(ck);
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}