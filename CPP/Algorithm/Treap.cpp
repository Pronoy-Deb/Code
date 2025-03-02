// Treap: 0-based indexing
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
    for (int i = 1; i <= n; ++i) {
        cin >> a; t[a].insert(i);
    }
    int q; cin >> q;
    while (q--) {
        int l, r, x, y; cin >> l >> r >> x >> y;
        auto *p = t[x].erase(l, r); t[y].combine(p);
    }
    for (int i = 1; i < N; ++i) {
        auto p = t[i].get();
        for (auto x : p) ans[x] = i;
    }
    for (int i = 1; i <= n; ++i) cout << ans[i] << " \n"[i == n];

// Implicit Treap: 0-based indexing
// Operations: RANGE cyclic_shift, summation, minimum, maximum, replacement, addition, erasing, reversal

mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
struct treap {
    struct NODE {
        int64_t val, sz, prior, lazy, sum, mx, mn, repl;
        bool repl_flag, rev; NODE *l, *r, *par;
        NODE() {
            lazy = rev = sum = val = sz = mx = mn = repl = repl_flag = prior = 0; l = r = par = NULL;
        }
        NODE(int64_t _val) {
            val = sum = mx = mn = _val;
            repl = repl_flag = rev = lazy = 0;
            sz = 1; prior = rnd(); l = r = par = NULL;
        }
    };
    typedef NODE *node; node root;
    unordered_map<int64_t, node> position; // positions of all the values
    inline void clear() { // clearing the treap
        root = NULL; position.clear();
    }
    treap() { clear(); }
    inline int64_t size(node t) { return t ? t->sz : 0; }
    void update_size(node &t) {
        if (t) t->sz = size(t->l) + size(t->r) + 1;
    }
    inline void update_parent(node &t) {
        if (!t) return;
        if (t->l) t->l->par = t;
        if (t->r) t->r->par = t;
    }
    void lazy_sum_upd(node &t) { // add operation
        if (!t or !t->lazy) return;
        t->sum += t->lazy * size(t); t->val += t->lazy;
        t->mx += t->lazy; t->mn += t->lazy;
        if (t->l) t->l->lazy += t->lazy;
        if (t->r) t->r->lazy += t->lazy;
        t->lazy = 0;
    }
    void lazy_repl_upd(node &t) { // replace update
        if (!t or !t->repl_flag) return;
        t->val = t->mx = t->mn = t->repl;
        t->sum = t->val * size(t);
        if (t->l) {
            t->l->repl = t->repl;
            t->l->repl_flag = true;
        }
        if (t->r) {
            t->r->repl = t->repl;
            t->r->repl_flag = true;
        }
        t->repl_flag = false; t->repl = 0;
    }
    inline void lazy_rev_upd(node &t) { // reverse update
        if (!t or !t->rev) return;
        t->rev = false; swap(t->l, t->r);
        if (t->l) t->l->rev ^= true;
        if (t->r) t->r->rev ^= true;
    }
    // reset the value of current node assuming it now
    // represents a single element of the array
    inline void reset(node &t) {
        if (!t) return;
        t->sum = t->val; t->mx = t->val; t->mn = t->val;
    }
    // combine node l and r to form t by updating corresponding queries
    inline void combine(node &t, node l, node r) {
        if (!l) { t = r; return; }
        if (!r) { t = l; return; }
        // Beware!!! Here t can be equal to l or r anytime
        // i.e. t and (l or r) is representing same node
        // so operation is needed to be done carefully
        // e.g. if t and r are same then after t->sum=l->sum+r->sum operation,
        // r->sum will be the same as t->sum
        t->sum = l->sum + r->sum; t->mx = max(l->mx, r->mx); t->mn = min(l->mn, r->mn);
    }
    void operation(node &t) {
        if (!t) return; reset(t);
        lazy_rev_upd(t->l); lazy_rev_upd(t->r);
        lazy_repl_upd(t->l); lazy_repl_upd(t->r);
        lazy_sum_upd(t->l); lazy_sum_upd(t->r);
        combine(t, t->l, t); combine(t, t, t->r);
    }
    // split node t in l and r by key k
    // so first k+1 elements(0,1,2,...k) of the array from node t
    // will be split in left node and rest will be in right node
    void split(node t, node &l, node &r, int k, int add = 0) {
        if (t == NULL) { l = r = NULL; return; }
        lazy_rev_upd(t); lazy_repl_upd(t); lazy_sum_upd(t);
        int idx = add + size(t->l);
        if (t->l) t->l->par = NULL; if (t->r) t->r->par = NULL;
        if (idx <= k) split(t->r, t->r, r, k, idx + 1), l = t;
        else split(t->l, l, t->l, k, add), r = t;
        update_parent(t); update_size(t); operation(t);
    }
    void merge(node &t, node l, node r) { // merge node l with r in t
        lazy_rev_upd(l); lazy_rev_upd(r);
        lazy_repl_upd(l); lazy_repl_upd(r);
        lazy_sum_upd(l); lazy_sum_upd(r);
        if (!l) { t = r; return; } if (!r) { t = l; return; }
        if (l->prior > r->prior) merge(l->r, l->r, r), t = l;
        else merge(r->l, l, r->l), t = r;
        update_parent(t); update_size(t); operation(t);
    }
    // insert val in position a[pos]
    // so all previous values from pos to last will be right shifted
    void insert(int pos, int64_t val) {
        if (root == NULL) {
            node to_add = new NODE(val); root = to_add;
            position[val] = root; return;
        }
        node l, r, mid; mid = new NODE(val);
        position[val] = mid; split(root, l, r, pos - 1);
        merge(l, l, mid); merge(root, l, r);
    }
    // erase from L to R indexes, so all previous indexes from R+1 to last will be left shifted R - L + 1 times
    void erase(int L, int R) {
        node l, r, mid; split(root, l, r, L - 1);
        split(r, mid, r, R - L); merge(root, l, r);
    }
    // returns answer for corresponding types of query
    int64_t get_sum(int L, int R) {
        node l, r, mid; split(root, l, r, L - 1);
        split(r, mid, r, R - L); int64_t ans = mid->sum;
        merge(r, mid, r); merge(root, l, r); return ans;
    }
    int64_t get_min(int L, int R) {
        node l, r, mid;
        split(root, l, r, L - 1); split(r, mid, r, R - L);
        int64_t ans = mid->mn;
        merge(r, mid, r); merge(root, l, r);
        return ans;
    }
    int64_t get_max(int L, int R) {
        node l, r, mid;
        split(root, l, r, L - 1); split(r, mid, r, R - L);
        int64_t ans = mid->mx;
        merge(r, mid, r); merge(root, l, r);
        return ans;
    }
    // add val in all the values from a[L] to a[R] positions
    void add(int L, int R, int64_t val) {
        node l, r, mid; split(root, l, r, L - 1);
        split(r, mid, r, R - L); lazy_repl_upd(mid);
        mid->lazy += val; merge(r, mid, r); merge(root, l, r);
    }
    // reverse all the values from L to R
    void reverse(int L, int R) {
        node l, r, mid; split(root, l, r, L - 1);
        split(r, mid, r, R - L); mid->rev ^= 1;
        merge(r, mid, r); merge(root, l, r);
    }
    // replace all the values from a[L] to a[R] by v
    void replace(int L, int R, int64_t v) {
        node l, r, mid; split(root, l, r, L - 1);
        split(r, mid, r, R - L); lazy_sum_upd(mid);
        mid->repl_flag = 1; mid->repl = v;
        merge(r, mid, r); merge(root, l, r);
    }
    // it will cyclic right shift the array k times
    // so for k=1, a[L]=a[R] and all positions from L+1 to R will have values from previous a[L] to a[R-1]
    // if you make left_shift=1 then it will to the opposite
    void cyclic_shift(int L, int R, int k, bool left_shift = 0) {
        if (L == R) return; k %= (R - L + 1);
        node l, r, mid, fh, sh; split(root, l, r, L - 1);
        split(r, mid, r, R - L);
        if (!left_shift) split(mid, fh, sh, (R - L + 1) - k - 1);
        else split(mid, fh, sh, k - 1);
        merge(mid, sh, fh); merge(r, mid, r); merge(root, l, r);
    }
    bool exist;
    // returns index of node curr
    int get_pos(node curr, node son = nullptr) {
        if (exist == 0) return 0;
        if (curr == NULL) { return exist = 0; }
        if (!son) {
            if (curr == root) return size(curr->l);
            else return size(curr->l) + get_pos(curr->par, curr);
        }
        if (curr == root) {
            if (son == curr->l) return 0;
            else return size(curr->l) + 1;
        }
        if (curr->l == son) return get_pos(curr->par, curr);
        else return get_pos(curr->par, curr) + size(curr->l) + 1;
    }
    // returns index of the value
    // if the value has multiple positions then it will return the last index where it was added last time
    // returns -1 if it doesn't exist in the array
    int get_pos(int value) {
        if (position.find(value) == position.end()) return -1;
        exist = 1;
        int x = get_pos(position[value]);
        if (exist == 0) return -1;
        else return x;
    }
    int get_val(int pos) { // returns value of index pos
        return get_sum(pos, pos);
    }
    int size() { return size(root); }
    // inorder traversal to get indexes chronologically
    void inorder(node cur) {
        if (cur == NULL) return;
        operation(cur); inorder(cur->l);
        cout << (char)cur->val; inorder(cur->r);
    }
    void print() { // print current array values serially
        // for (int i = 0; i < size(); ++i) cout << get_val(i) << ' ';
        inorder(root); cout << '\n';
    }
    bool find(int val) {
        if (get_pos(val) == -1) return false;
        else return true;
    }
    void toEnd(int L, int R) {
        node l, m, r;
        split(root, l, r, L - 1); split(r, m, r, R - L);
        merge(root, l, r); merge(root, root, m);
    }
} t;

// Operation:

    for (int i = 0; i < 10; ++i) t.insert(i, i * 10);
    t.cyclic_shift(4, 5, 1);
    t.add(2, 5, 1);
    t.replace(2, 5, 100);
    t.reverse(2, 9);
    t.replace(2, 5, 200);
    cout << t.get_sum(0, 7) << '\n';
    t.cyclic_shift(2, 3, 2, 1);
    cout << t.get_pos(20) << '\n';
    t.erase(2, 2);
    cout << t.find(30) << '\n';
    t.print();

// Persistent Treap:
https://vjudge.net/problem/UVA-12538

const int N = 5e4 + 9;

// Implicit Persistent Treap
// 0-indexed
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
struct node {
    node *l, *r; int val, prior, sz;
    node() {}
    node(int id) {
        l = r = nullptr; val = id; prior = rnd(); sz = 1;
    }
};
namespace PersistentTreap {
    inline void copy(node *&a, node *b) {
        if (!b) a = nullptr;
        else { a = new node(); *a = *b; }
    }
    int size(node *t) { return t ? t->sz : 0; }
    void update_size(node *&t) {
        if (t) t->sz = size(t->l) + size(t->r) + 1;
    }
    void split(node *cur, int pos, node *&l, node *&r, int add = 0) {
        node *t; copy(t, cur);
        if (t == nullptr) { l = r = nullptr; return; }
        int id = add + size(t->l);
        if (id <= pos) {
            split(t->r, pos, l, r, id + 1);
            t->r = l; l = t;
        }
        else {
            split(t->l, pos, l, r, add);
            t->l = r; r = t;
        }
        update_size(t);
    }
    node *merge(node *l, node *r) {
        node *t; if (!l || !r) copy(t, l ? l : r);
        else if (l->prior < r->prior) {
            copy(t, l); t->r = merge(t->r, r);
        }
        else {
            copy(t, r); t->l = merge(l, t->l);
        }
        update_size(t); return t;
    }
    node *insert(node *t, int pos, int val) {
        node *l, *r; split(t, pos - 1, l, r);
        return merge(merge(l, new node(val)), r);
    }
    node *insert(node *t, int pos, node *x) {
        node *l, *r; split(t, pos - 1, l, r);
        return merge(merge(l, x), r);
    }
    node *erase(node *t, int L, int R) {
        node *l, *r, *mid, *mr; split(t, L - 1, l, r);
        split(r, R - L, mid, mr); return merge(l, mr);
    }
    // creating a treap for string s in O(n)
    node *build(int l, int r, string &s) {
        int mid = l + r >> 1; node *cur = new node(s[mid]);
        if (l < mid) cur->l = build(l, mid - 1, s);
        if (mid < r) cur->r = build(mid + 1, r, s);
        update_size(cur); return cur;
    }
    int c = 0;
    void print_nodes(node *t) {
        if (!t) return; print_nodes(t->l);
        char ch = t->val; c += ch == 'c';
        cout << ch; print_nodes(t->r);
    }
    void print(node *t, int L, int R) {
        node *l, *r, *mid, *mr; split(t, L - 1, l, r);
        split(r, R - L, mid, mr); print_nodes(mid);
    }
}
using namespace PersistentTreap;
node *root[N];
int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int version = 0, q; cin >> q;
    while (q--) {
        int ty; cin >> ty;
        if (ty == 1) {
            int k; string s; cin >> k >> s;
            k -= c; node *t = build(0, (int)s.size() - 1, s);
            root[version + 1] = insert(root[version], k, t);
            ++version;
        }
        else if (ty == 2) {
            int l, len; cin >> l >> len;
            l -= c, len -= c; --l;
            root[version + 1] = erase(root[version], l, l + len - 1);
            ++version;
        }
        else {
            int v, l, len; cin >> v >> l >> len;
            v -= c, l -= c, len -= c; --l;
            print(root[v], l, l + len - 1); cout << '\n';
        }
    }
    return 0;
}

// generated at caterpillow.github.io/byot

#include <bits/stdc++.h>

using namespace std;
using ll = int64_t;

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
    using T = int64_t;

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
        if (!n) return; ptr mx = n;
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
