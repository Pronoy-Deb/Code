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

namespace trp {
    mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
    using ptr = struct Node*;
    struct Node {
        ptr l, r; int key, sz, pri;
        Node() {
            pri = rnd(); sz = 1; l = r = nullptr;
        }
        Node(int key) : key(key) {
            pri = rnd(); sz = 1; l = r = nullptr;
        }
    };
    int sz(ptr n) { return n ? n->sz : 0; };
    ptr pull(ptr n) {
        if (!n) return nullptr;
        n->sz = sz(n->l) + 1 + sz(n->r);
        return n;
    }
    ptr merge(ptr l, ptr r) {
        if (!l || !r) return l ? l : r;
        if (l->pri > r->pri) return l->r = merge(l->r, r), pull(l);
        else return r->l = merge(l, r->l), pull(r);
    }
    template<typename... Args>
    ptr merge(ptr l, Args... args) {
        return merge(l, merge(args...));
    }
    // [-inf, i) and [i, inf]
    pair<ptr, ptr> split(ptr n, int i) {
        if (!n) return {nullptr, nullptr};
        if (i <= sz(n->l)) {
            auto [l, r] = split(n->l, i);
            n->l = r;
            return {l, pull(n)};
        } else {
            auto [l, r] = split(n->r, i - 1 - sz(n->l));
            n->r = l;
            return {pull(n), r};
        }
    }
    void heapify(ptr n) {
        if (!n) return;
        ptr mx = n;
        if (n->l && n->l->pri > mx->pri) mx = n->l;
        if (n->r && n->r->pri > mx->pri) mx = n->r;
        if (mx != n) swap(n->pri, mx->pri), heapify(mx);
    }
    ptr make(vector<ptr>& ns, int l = 0, int r = -69) {
        if (r == -69) r = (int) ns.size() - 1;
        if (l > r) return nullptr;
        if (l == r) return ns[l];
        int m = (l + r) >> 1;
        ns[m]->l = make(ns, l, m - 1);
        ns[m]->r = make(ns, m + 1, r);
        heapify(ns[m]);
        return pull(ns[m]);
    }
    template <typename Op>
    void tour(ptr n, Op op) {
        stack<ptr> stk;
        while (n || !stk.empty()) {
            for (; n; n = n->l) stk.push(n);
            n = stk.top(); stk.pop(); op(n); n = n->r;
        }
    }
}
using namespace trp;
ptr treap; int n;
void random_shuffle(int a, int b) {
    if (b < a) return;
    int len = min(b - a, n - b);
    int l0 = a;
    int r0 = a + len;
    int l1 = b;
    int r1 = b + len;
    auto [lxmy, r] = split(treap, r1);
    auto [lxm, y] = split(lxmy, l1);
    auto [lx, m] = split(lxm, r0);
    auto [l, x] = split(lx, l0);
    treap = trp::merge(l, y, m, x, r);
}

void test(int32_t tc) {
    int nn = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n; vector<ptr> ns(n);
    for (i = 0; i < n; ++i) ns[i] = new Node(i + 1);
    treap = make(ns);
    for (i = 0; i < n; ++i) {
        cin >> a >> b; random_shuffle(a - 1, b - 1);
    }
    tour(treap, [&] (ptr n) { cout << n->key << ' '; });
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}