#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;
const int SZ = MAXN * 30; // for segment tree nodes

int s[SZ], ch[SZ][2]; // s: size of node, ch: children of node
int n, q, X;
int P[MAXN]; // permutation
int root[MAXN], rb[MAXN], ty[MAXN];
set<int> cur; // set of current segment tree boundaries
int node_count = 0;

int new_node() {
    ++node_count;
    s[node_count] = 0;
    ch[node_count][0] = ch[node_count][1] = 0;
    return node_count;
}

// Build a tree with only node p, returns in the first argument
void build(int& x, int l, int r, int p) {
    x = new_node();
    s[x] = 1;
    if (l == r) return;
    int m = (l + r) / 2;
    if (p <= m) build(ch[x][0], l, m, p);
    else build(ch[x][1], m + 1, r, p);
}

// Split tree t1 into t1 and t2 such that t1 keeps k smallest elements
void split(int t1, int& t2, int k) {
    if (!t1 || k == 0) return;
    t2 = new_node();
    int ls = s[ch[t1][0]]; // size of t1's left child
    if (k > ls) {
        split(ch[t1][1], ch[t2][1], k - ls); // split right child
    } else {
        swap(ch[t1][1], ch[t2][1]); // move right child to t2
    }
    if (k <= ls) {
        split(ch[t1][0], ch[t2][0], k); // split left child
    }
    s[t2] = s[t1] - k; // adjust size
    s[t1] = k;
}

// Merge two segment trees
int merge(int t1, int t2) {
    if (!t1 || !t2) return t1 ^ t2;
    ch[t1][0] = merge(ch[t1][0], ch[t2][0]);
    ch[t1][1] = merge(ch[t1][1], ch[t2][1]);
    s[t1] += s[t2]; // update size
    return t1;
}

// Query for the k-th element in the sorted segment tree x[l, r]
int ask(int x, int l, int r, int k) {
    if (l == r) return l;
    int ls = s[ch[x][0]]; // number of elements in the left child
    int m = (l + r) / 2;
    if (k > ls) return ask(ch[x][1], m + 1, r, k - ls);
    return ask(ch[x][0], l, m, k);
}

// Split the range at l and r
void split_range(int l, int r) {
    if (r >= rb[l] || r < l) return;
    if (!ty[l]) split(root[l], root[r + 1], r - l + 1); // ascending
    else { // descending
        root[r + 1] = root[l];
        split(root[r + 1], root[l], rb[l] - r);
    }
    rb[r + 1] = rb[l];
    rb[l] = r;
    cur.insert(r + 1);
    ty[r + 1] = ty[l];
}

// Merge adjacent ranges a and b
void merge_range(int a, int b) {
    if (a == b) return;
    cur.erase(b);
    root[a] = merge(root[a], root[b]);
    rb[a] = rb[b];
}

// Query the k-th element in the range starting from l
int get_element(int l, int k) {
    k -= l - 1;
    if (!ty[l]) return ask(root[l], 1, n, k);
    return ask(root[l], 1, n, rb[l] - l + 1 - k + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> q >> X;
    for (int i = 1; i <= n; ++i) {
        cin >> P[i];
        build(root[i], 1, n, P[i]); // build a segment tree for each element
        cur.insert(i);
        rb[i] = i;
    }

    while (q--) {
        int C, L, R;
        cin >> C >> L >> R;
        set<int>::iterator it = cur.upper_bound(L);
        split_range(*(--it), L - 1); // split left side
        it = cur.upper_bound(R);
        split_range(*(--it), R); // split right side

        set<int>::iterator L_it = cur.lower_bound(L), R_it = cur.upper_bound(R);
        --R_it;
        int nw = *L_it;
        vector<int> ranges_to_merge;
        while (L_it != R_it) {
            ++L_it;
            int next = *L_it;
            ranges_to_merge.push_back(next);
            if (L_it == R_it) break;
        }
        for (int i = 0; i < ranges_to_merge.size(); ++i) {
            merge_range(nw, ranges_to_merge[i]); // merge the ranges
        }
        ty[nw] = C - 1; // set the type (ascending or descending)
    }

    set<int>::iterator it = cur.upper_bound(X);
    int l = *(--it);
    cout << get_element(l, X) << '\n'; // output the position of X

    return 0;
}
