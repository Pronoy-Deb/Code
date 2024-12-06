// Treap:
https://codeforces.com/problemset/problem/911/G

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

// Operation:
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

// Persistent Treap:
https://vjudge.net/problem/UVA-12538

const int N = 5e4 + 9;

// Implicit Persistent Treap
// 0-indexed
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
struct node
{
    node *l, *r;
    int val, prior, sz;
    node() {}
    node(int id)
    {
        l = r = nullptr;
        val = id;
        prior = rnd();
        sz = 1;
    }
};
namespace PersistentTreap
{
    inline void copy(node *&a, node *b)
    {
        if (!b)
            a = nullptr;
        else
        {
            a = new node();
            *a = *b;
        }
    }
    int size(node *t)
    {
        return t ? t->sz : 0;
    }
    void update_size(node *&t)
    {
        if (t)
            t->sz = size(t->l) + size(t->r) + 1;
    }
    void split(node *cur, int pos, node *&l, node *&r, int add = 0)
    {
        node *t;
        copy(t, cur);
        if (t == nullptr)
        {
            l = r = nullptr;
            return;
        }
        int id = add + size(t->l);
        if (id <= pos)
        {
            split(t->r, pos, l, r, id + 1);
            t->r = l;
            l = t;
        }
        else
        {
            split(t->l, pos, l, r, add);
            t->l = r;
            r = t;
        }
        update_size(t);
    }
    node *merge(node *l, node *r)
    {
        node *t;
        if (!l || !r)
            copy(t, l ? l : r);
        else if (l->prior < r->prior)
        {
            copy(t, l);
            t->r = merge(t->r, r);
        }
        else
        {
            copy(t, r);
            t->l = merge(l, t->l);
        }
        update_size(t);
        return t;
    }
    node *insert(node *t, int pos, int val)
    {
        node *l, *r;
        split(t, pos - 1, l, r);
        return merge(merge(l, new node(val)), r);
    }
    node *insert(node *t, int pos, node *x)
    {
        node *l, *r;
        split(t, pos - 1, l, r);
        return merge(merge(l, x), r);
    }
    node *erase(node *t, int L, int R)
    {
        node *l, *r, *mid, *mr;
        split(t, L - 1, l, r);
        split(r, R - L, mid, mr);
        return merge(l, mr);
    }
    // creating a treap for string s in O(n)
    node *build(int l, int r, string &s)
    {
        int mid = l + r >> 1;
        node *cur = new node(s[mid]);
        if (l < mid)
            cur->l = build(l, mid - 1, s);
        if (mid < r)
            cur->r = build(mid + 1, r, s);
        update_size(cur);
        return cur;
    }
    int c = 0;
    void print_nodes(node *t)
    {
        if (!t)
            return;
        print_nodes(t->l);
        char ch = t->val;
        c += ch == 'c';
        cout << ch;
        print_nodes(t->r);
    }
    void print(node *t, int L, int R)
    {
        node *l, *r, *mid, *mr;
        split(t, L - 1, l, r);
        split(r, R - L, mid, mr);
        print_nodes(mid);
    }
}
using namespace PersistentTreap;
node *root[N];
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int version = 0;
    int q;
    cin >> q;
    while (q--)
    {
        int ty;
        cin >> ty;
        if (ty == 1)
        {
            int k;
            string s;
            cin >> k >> s;
            k -= c;
            node *t = build(0, (int)s.size() - 1, s);
            root[version + 1] = insert(root[version], k, t);
            version++;
        }
        else if (ty == 2)
        {
            int l, len;
            cin >> l >> len;
            l -= c, len -= c;
            --l;
            root[version + 1] = erase(root[version], l, l + len - 1);
            version++;
        }
        else
        {
            int v, l, len;
            cin >> v >> l >> len;
            v -= c, l -= c, len -= c;
            --l;
            print(root[v], l, l + len - 1);
            cout << '\n';
        }
    }
    return 0;
}


// generated at caterpillow.github.io/byot

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

namespace Treap {

    struct Lazy {

        void operator+=(const Lazy& oth) {
        }
    };
    const Lazy lid = {};
    // You can implement your own monoid here for custom operations.
    struct Value {
        ll sum;
        ll mx;
        ll mn;
        T ksum;

        void upd(Lazy lazy, int sz) {
        }

        Value operator+(const Value& oth) const {
            Value res {};
            res.sum = sum + oth.sum;
            res.mx = max(mx, oth.mx);
            res.mn = min(mn, oth.mn);
            res.ksum = ksum + oth.ksum;
            return res;
        }
    };

    const Value vid = {0, -1'000'000'000'000'000'000, 1'000'000'000'000'000'000, 0};

    mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
    using ptr = struct Node*;
    using T = long long;

    struct Node {
        Value val;
        Value agg;
        Lazy lazy;

        T key;
        int sz;
        int pri;
        ptr l, r;
        ptr par;

        Node() {
            pri = mt();
            val = vid;
            agg = vid;
            lazy = lid;
            sz = 1;
            l = r = nullptr;
            par = nullptr;
        }

        Node(T key, Value val) : key(key), val(val), agg(val) {
            pri = mt();
            lazy = lid;
            sz = 1;
            l = r = nullptr;
            par = nullptr;
            val.ksum = agg.ksum = 0;
        }

        ~Node() {
            delete l;
            delete r;
        }
    };

    int sz(ptr n) { return n ? n->sz : 0; };
    Value agg(ptr n) { return n ? n->agg : vid; }

    void push(ptr n) {
        n->val.upd(n->lazy, 1);
        n->agg.upd(n->lazy, sz(n));
        if (n->l) n->l->lazy += n->lazy;
        if (n->r) n->r->lazy += n->lazy;
        n->lazy = lid;
    }

    ptr pull(ptr n) {
        if (!n) return nullptr;
        if (n->l) push(n->l);
        if (n->r) push(n->r);
        if (n->l) n->l->par = n;
        if (n->r) n->r->par = n;
        n->sz = sz(n->l) + 1 + sz(n->r);
        n->agg = agg(n->l) + n->val + agg(n->r);
        return n;
    }

    ptr merge(ptr l, ptr r) {
        if (!l || !r) return l ? l : r;
        push(l), push(r);
        if (l->pri > r->pri) return l->r = merge(l->r, r), pull(l);
        else return r->l = merge(l, r->l), pull(r);
    }

    // [-inf, k) and [k, inf]
    pair<ptr, ptr> split(ptr n, T k) {
        if (!n) return {nullptr, nullptr};
        n->par = nullptr;
        push(n);
        if (k <= n->key) {
            auto [l, r] = split(n->l, k);
            n->l = r;
            return {l, pull(n)};
        } else {
            auto [l, r] = split(n->r, k);
            n->r = l;
            return {pull(n), r};
        }
    }

    // cuts out [lo, hi)
    tuple<ptr, ptr, ptr> split(ptr n, T lo, T hi) {
        auto [lm, r] = split(n, hi);
        auto [l, m] = split(lm, lo);
        return {l, m, r};
    }

    ptr find(ptr n, int k) {
        if (!n) return 0;
        push(n);
        if (n->key == k) return n;
        if (k <= n->key) return find(n->l, k);
        else return find(n->r, k);
    }

    // only insert single nodes
    void ins(ptr& n, ptr it) {
        if (!n) { n = it; return; }
        if (n->pri < it->pri) {
            auto [l, r] = split(n, it->key);
            it->l = l, it->r = r, n = it;
        } else if (it->key <= n->key) ins(n->l, it);
        else ins(n->r, it);
        pull(n);
    }

    // performs an arbitrary operation on some node
    template <typename Op>
    void modify(ptr n, T k, Op op) {
        if (!n) return;
        push(n);
        if (n->key == k) op(n);
        else if (k <= n->key) modify(n->l, k, op);
        else modify(n->r, k, op);
        pull(n);
    }

    // finds smallest key such that pred returns false
    template<typename Pred>
    T partition_key(ptr n, Pred pred) {
        push(n);
        if (pred(n)) return n->r ? partition_key(n->r, pred) : n->key + 1;
        else return n->l ? partition_key(n->l, pred) : n->key;
    }

    // given a predicate that will return true for some prefix of aggregates,
    // find the key of the first prefix aggregate makes the predicate false (max key + 1 if always true)
    // eg. find the smallest prefix that has sum > x
    template <typename Pred>
    T cumulative_partition_key(ptr n, Pred pred, Value acc = vid) {
        push(n);
        if (!pred(acc + agg(n->l))) return n->l ? cumulative_partition_key(n->l, pred, acc) : n->key;
        if (!pred(acc = acc + agg(n->l) + n->val)) return n->key;
        return n->r ? cumulative_partition_key(n->r, pred, acc) : n->key + 1;
    }

    ptr mn(ptr n) {
        push(n);
        return n->l ? mn(n->l) : n;
    }

    ptr mx(ptr n) {
        push(n);
        return n->r ? mx(n->r) : n;
    }

    void clean(ptr n) {
        if (!n) return;
        clean(n->par);
        push(n);
    }

    ptr root(ptr n) {
        while (n->par) n = n->par;
        return n;
    }

    void heapify(ptr n) {
        if (!n) return;
        ptr mx = n;
        if (n->l && n->l->pri > mx->pri) mx = n->l;
        if (n->r && n->r->pri > mx->pri) mx = n->r;
        if (mx != n) swap(n->pri, mx->pri), heapify(mx);
    }

    ptr build(vector<ptr>& ns, int l = 0, int r = -69) {
        if (r == -69) r = (int) ns.size() - 1;
        if (l > r) return nullptr;
        if (l == r) return ns[l];
        int m = (l + r) >> 1;
        ns[m]->l = build(ns, l, m - 1);
        ns[m]->r = build(ns, m + 1, r);
        heapify(ns[m]);
        return pull(ns[m]);
    }

    template <typename Op>
    void tour(ptr n, Op op) {
        stack<ptr> stk;
        while (n || !stk.empty()) {
            for (; n; n = n->l) push(n), stk.push(n);
            n = stk.top(); stk.pop();
            op(n);
            n = n->r;
        }
    }

}

using namespace Treap;

main() {
    cin.tie(0)->sync_with_stdio(0);

}
