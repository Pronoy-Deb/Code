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
struct Trie {
    static const int B = 31;
    struct node {
        node* nxt[2];
        int sz;
        node() {
            nxt[0] = nxt[1] = NULL;
            sz = 0;
        }
    }* root;
    Trie() {
        root = new node();
    }
    void insert(int val) {
        node* cur = root;
        cur->sz++;
        for (int i = B - 1; i >= 0; i--) {
            int b = val >> i & 1;
            if (cur->nxt[b] == NULL) cur->nxt[b] = new node();
            cur = cur->nxt[b];
            cur->sz++;
        }
    }
    int get(int x, int k) {  // number of values val ^ x < k
        node* cur = root;
        int ans = 0;
        for (int i = B - 1; i >= 0; i--) {
            if (cur == NULL) break;
            int b1 = x >> i & 1, b2 = k >> i & 1;
            if (b2 == 1) {
                if (cur->nxt[b1]) ans += cur->nxt[b1]->sz;
                cur = cur->nxt[!b1];
            } else
                cur = cur->nxt[b1];
        }
        return ans;
    }
    int get_max(int x) {  // returns maximum of val ^ x
        node* cur = root;
        int ans = 0;
        for (int i = B - 1; i >= 0; i--) {
            int k = x >> i & 1;
            if (cur->nxt[!k])
                cur = cur->nxt[!k], ans <<= 1, ans++;
            else
                cur = cur->nxt[k], ans <<= 1;
        }
        return ans;
    }
    int get_min(int x) {  // returns minimum of val ^ x
        node* cur = root;
        int ans = 0;
        for (int i = B - 1; i >= 0; i--) {
            int k = x >> i & 1;
            if (cur->nxt[k])
                cur = cur->nxt[k], ans <<= 1;
            else
                cur = cur->nxt[!k], ans <<= 1, ans++;
        }
        return ans;
    }
    void del(node* cur) {
        for (int i = 0; i < 2; i++)
            if (cur->nxt[i]) del(cur->nxt[i]);
        delete (cur);
    }
} t;

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> k;
    long long ans = n * (n + 1) >> 1;
    int cur = 0; t.insert(cur);
    for (i = 0; i < n; ++i) {
        int x; cin >> x; cur ^= x;
        ans -= t.get(cur, k);
        t.insert(cur);
    }
    cout << ans << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}