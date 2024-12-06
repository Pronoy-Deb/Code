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

mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
struct node {
    node *l, *r; int key, prior;
    node(int id) {
        l = r = nullptr; key = id; prior = rnd();
    }
};
struct treap {
    node *root; treap() { root = nullptr; }
    void split(node *t, int pos, node *&l, node *&r) {
        if (t == nullptr) { l = r = nullptr; return; }
        if (t->key <= pos) {
            split(t->r, pos, l, r); t->r = l; l = t;
        }
        else {
            split(t->l, pos, l, r); t->l = r; r = t;
        }
    }
    node *merge(node *l, node *r) {
        if (!l || !r) return l ? l : r;
        if (l->prior < r->prior) {
            l->r = merge(l->r, r); return l;
        }
        r->l = merge(l, r->l); return r;
    }
    node *merge_treap(node *l, node *r) {
        if (!l) return r; if (!r) return l;
        if (l->prior < r->prior) swap(l, r);
        node *L, *R; split(r, l->key, L, R);
        l->r = merge_treap(l->r, R);
        l->l = merge_treap(L, l->l);
        return l;
    }
    void insert(int id) {
        node *l, *r; split(root, id, l, r);
        root = merge(merge(l, new node(id)), r);
    }
    node *erase(int L, int R) {
        node *l, *r, *mid, *mr; split(root, L - 1, l, r);
        split(r, R, mid, mr); root = merge(l, mr); return mid;
    }
    void combine(node *x) { // combine with another treap
        root = merge_treap(root, x);
    }
    vector<int> res;
    void dfs(node *cur) {
        if (!cur) return; res.push_back(cur->key);
        dfs(cur->l); dfs(cur->r);
    }
    vector<int> get() {
        res.clear(); dfs(root); return res;
    }
} t[N];
int ans[N];

void test(int32_t tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n;
    for (i = 1; i <= n; ++i) {
        cin >> a; t[a].insert(i);
    }
    cin >> q;
    while (q--) {
        int l, r, x, y; cin >> l >> r >> x >> y;
        auto *p = t[x].erase(l, r); t[y].combine(p);
    }
    for (i = 1; i < N; ++i) {
        auto p = t[i].get();
        for (auto x : p) ans[x] = i;
    }
    for (i = 1; i <= n; ++i) cout << ans[i] << " \n"[i == n];
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}