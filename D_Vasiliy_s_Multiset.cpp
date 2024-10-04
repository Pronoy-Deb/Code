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
const int L = 31;

int trie[N * L][2], cnt[N * L], tot = 1;
void ins(int x) {
    int u = 1;
    for (int i = L - 1; i >= 0; --i) {
        int f = x >> i & 1;
        if (!trie[u][f]) trie[u][f] = ++tot;
        u = trie[u][f]; ++cnt[u];
    }
}
void rem(int x) {
    int u = 1;
    for (int i = L - 1; i >= 0; --i) {
        int f = x >> i & 1; u = trie[u][f]; --cnt[u];
    }
}
int mx_xr(int x) {
    int u = 1, res = 0;
    for (int i = L - 1; i >= 0; --i) {
        int f = x >> i & 1;
        if (cnt[trie[u][!f]]) res |= 1 << i, u = trie[u][!f];
        else u = trie[u][f];
    }
    return res;
}
int mn_xr(int x) {
    int u = 1, res = 0;
    for (int i = L - 1; i >= 0; --i) {
        int f = x >> i & 1;
        if (cnt[trie[u][f]]) u = trie[u][f];
        else res |= 1 << i, u = trie[u][!f];
    }
    return res;
}
int get(int x, int k) {
    int u = 1, ans = 0;
    for (int i = L - 1; u and i >= 0; --i) {
        int f1 = x >> i & 1, f2 = k >> i & 1;
        if (f2 == 1) {
            if (trie[u][f1]) ans += cnt[trie[u][f1]];
            u = trie[u][!f1];
        }
        else u = trie[u][f1];
    }
    return ans;
}

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n;
    // vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    ins(0);
    while (n--) {
        char ch;
        cin >> ch >> a;
        if(ch == '+') ins(a);
        else if(ch == '-') rem(a);
        else cout << mx_xr(a) << ' ' << mn_xr(a) << '\n';
    }
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}