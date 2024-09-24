/*
segment tree class merely handles segment tree operations
and the attempt here is to employ it in such a way that
there would be no need to change that part of the code

vertex class needs to handle everything that a segment tree
needs.
VT, DT, LT are the vertex class, query return type, and update type
respectively

requirements from the vertex class:
a constructor that takes the query return type as an argument
a lazy value that contains update types
member functions:
apply:
    given an update type and range of the node, it will apply the update
    to a node
reset:
    will clear all pending operations in lazy
merge:
    given child nodes, will combine them to form the current node
get:
    given two results of queries from child node and current range
    will give the result for this node
ans:
    in the case of a leaf, will give the result

ostream must be defined to use check
*/

template <typename VT>
class ST {
    using DT = typename VT::DT;
    using LT = typename VT::LT;

   public:
    long long L, R, counter = 1;
    vector<VT> tree;
    ST(long long n) : L(0), R(n - 1), tree(n << 2) {}
    ST(long long s, long long e) : L(s), R(e), tree(e - s + 1 << 2) {}

    void propagate(long long s, long long e, long long node) {
        if (s == e) return;
        tree[node * 2].apply(tree[node].lazy, s, s + e >> 1);
        tree[node * 2 + 1].apply(tree[node].lazy, s + e + 2 >> 1, e);
        tree[node].reset();
    }

    void build(vector<DT> &v) { build(L, R, v); }
    void update(long long S, long long E, LT U) { update(S, E, U, L, R); }
    DT query(long long S, long long E) { return query(S, E, L, R); }

    void build(long long s, long long e, vector<DT> &v, long long node = 1) {
        long long m = s + e >> 1;
        if (s == e) {
            tree[node] = VT(v[s]);
            return;
        }
        build(s, m, v, node * 2);
        build(m + 1, e, v, node * 2 + 1);
        tree[node].merge(tree[node * 2], tree[node * 2 + 1], s, e);
    }
    void update(long long S, long long E, LT uval, long long s, long long e, long long node = 1) {
        if (S > E) return;
        if (S == s and E == e) {
            tree[node].apply(uval, s, e);
            return;
        }
        propagate(s, e, node);
        long long m = s + e >> 1;
        update(S, min(m, E), uval, s, m, node * 2);
        update(max(S, m + 1), E, uval, m + 1, e, node * 2 + 1);
        tree[node].merge(tree[node * 2], tree[node * 2 + 1], s, e);
    }
    DT query(long long S, long long E, long long s, long long e, long long node = 1) {
        if (S > E) return VT::I;
        if (s == S and e == E) return tree[node].ans(s, e);
        propagate(s, e, node);
        long long m = s + e >> 1;
        DT L = query(S, min(m, E), s, m, node * 2);
        DT R = query(max(S, m + 1), E, m + 1, e, node * 2 + 1);
        return tree[node].get(L, R, s, e);
    }
};

class vertex {
   public:
    using DT = long long;
    using LT = long long;
    DT val;
    LT lazy;
    static constexpr DT I = 0;
    static constexpr LT None = 0;

    vertex(DT val = I, LT lazy = None) : val(val), lazy(lazy) {}
    // update functions
    inline void apply(const LT &U, long long s, long long e) {
        if(U == None) return;
        val += (e - s + 1) * U;
        lazy += U;
    }
    inline void reset() { lazy = None; }
    inline void merge(const vertex &a, const vertex &b, long long s, long long e) {
        val = a.val + b.val;
    }
    // query functions
    inline DT get(const DT &a, const DT &b, long long s, long long e) { return a + b; }
    inline DT ans(long long s, long long e) { return val; }
};