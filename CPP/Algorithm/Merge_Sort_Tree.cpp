// Complexity: make: O(n * logn), Finding number of elements in a range <= val: O(log^2(n)), Finding the k-th value in a range: O(log ^ 3n)
// Number of elements in the range that is <= val:

long long ar[N], n; vector<long long> tre[N << 2];
auto merge(auto &a, auto &b) {
    int i, j, k = a.size(), l = b.size(); vector<long long> res;
    for (i = 0, j = 0; i < k && j < l;) {
        if (a[i] < b[j]) res.push_back(a[i++]);
        else res.push_back(b[j++]);
    }
    while (i < k) res.push_back(a[i++]);
    while (j < l) res.push_back(b[j++]);
    return res;
}
void make(int nd = 0, int s = 0, int e = n - 1) {
    if (s == e) { tre[nd].push_back(ar[e]); return; }
    int m = (s + e) >> 1, lc = (nd << 1) + 1, rc = lc + 1;
    make(lc, s, m); make(rc, m + 1, e);
    tre[nd] = merge(tre[lc], tre[rc]);
}
void up(int in, long long val, int nd = 0, int s = 0, int e = n - 1) {
    if (s == e) { tre[nd][0] = val; return; }
    int m = (s + e) >> 1, lc = (nd << 1) + 1, rc = lc + 1;
    if (in <= m) up(in, val, lc, s, m);
    else up(in, val, rc, m + 1, e);
    tre[nd] = merge(tre[lc], tre[rc]);
}
int get(int l, int r, long long val, int nd = 0, int s = 0, int e = n - 1) {
    if (l > e || r < s) return 0;
    if (l <= s && e <= r)
        return lower_bound(tre[nd].begin(), tre[nd].end(), val + 1) - tre[nd].begin();
    int m = (e + s) >> 1, lc = (nd << 1) + 1, rc = lc + 1;
    return get(l, r, val, lc, s, m) + get(l, r, val, rc, m + 1, e);
}

// Operation:
    cin >> n >> q;
    for (i = 0; i < n; ++i) cin >> ar[i];
    make();
    while (q--) {
        int l, r, k, lo = -M, hi = M, ans = 0;
        cin >> l >> r >> k; --l, --r;
        // k-th element in the range [l, r]
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            if (get(l, r, mid) < k) lo = mid + 1;
            else ans = mid, hi = mid - 1;
        }
        cout << ans << '\n';
    }

// OR,

long long n, ar[N]; vector<long long> tre[N << 2];
void make(int nd = 0, int s = 0, int e = n - 1) {
    if (s == e) {
        tre[nd].push_back(ar[s]); return;
    }
    int m = (s + e) >> 1, lc = (nd << 1) + 1, rc = lc + 1;
    make(lc, s, m); make(rc, m + 1, e);
    int i = 0, j = 0, ls = tre[lc].size(), rs = tre[rc].size();
    while (i < ls && j < rs) {
        if (tre[lc][i] < tre[rc][j]) tre[nd].push_back(tre[lc][i++]);
        else tre[nd].push_back(tre[rc][j++]);
    }
    while (i < ls) tre[nd].push_back(tre[lc][i++]);
    while (j < rs) tre[nd].push_back(tre[rc][j++]);
}
int get(int l, int r, int x, int nd = 0, int s = 0, int e = n - 1) {
    if (s > r || e < l) return 0;
    if (s >= l && e <= r)
        return lower_bound(tre[nd].begin(), tre[nd].end(), x + 1) - tre[nd].begin();
    int m = (s + e) >> 1, lc = (nd << 1) + 1, rc = lc + 1;
    return get(l, r, x, lc, s, m) + get(l, r, x, rc, m + 1, e);
}

// OR,

#include <ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T> using oset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

int n, ar[N]; oset<int> tre[N << 2];
void make(int nd = 0, int l = 0, int r = n - 1) {
    if (l == r) { tre[nd].insert(ar[l]); return; }
    int m = (l + r) >> 1, lc = (nd << 1) + 1, rc = lc + 1;
    make(lc, l, m); make(rc, m + 1, r);
    for (int i = l; i <= r; ++i) tre[nd].insert(ar[i]);
}
void up(int in, int val, int nd = 0, int l = 0, int r = n - 1) {
    if (l == r) {
        tre[nd].erase(tre[nd].upper_bound(ar[in])); tre[nd].insert(val); return;
    }
    int m = (l + r) >> 1, lc = (nd << 1) + 1, rc = lc + 1;
    if (in <= m) up(in, val, lc, l, m);
    else up(in, val, rc, m + 1, r);
    tre[nd].erase(tre[nd].upper_bound(ar[in])); tre[nd].insert(val);
}
int get(int lx, int rx, int x, int nd = 0, int l = 0, int r = n - 1) {
    if (l > rx || r < lx) return 0;
    if (l >= lx && r <= rx) return tre[nd].order_of_key(x + 1);
    int m = (l + r) >> 1, lc = (nd << 1) + 1, rc = lc + 1;
    return get(lx, rx, x, lc, l, m) + get(lx, rx, x, rc, m + 1, r);
}

// Dynamic Lower Bound Problem:

long long n, ar[N]; multiset<long long> tre[N << 2];
void make(int nd = 0, int l = 0, int r = n - 1) {
    if (l == r) { tre[nd].insert(ar[l]); return; }
    int m = (l + r) >> 1, lc = (nd << 1) + 1, rc = lc + 1;
    make(lc, l, m); make(rc, m + 1, r);
    for (int i = l; i <= r; ++i) tre[nd].insert(ar[i]);
}
void up(int in, long long val, int nd = 0, int l = 0, int r = n - 1) {
    if (l == r) {
        tre[nd].erase(ar[in]); tre[nd].insert(val); return;
    }
    int m = (l + r) >> 1, lc = (nd << 1) + 1, rc = lc + 1;
    if (in <= m) up(in, val, lc, l, m);
    else up(in, val, rc, m + 1, r);
    tre[nd].erase(ar[in]); tre[nd].insert(val);
}
long long get(int lx, int rx, long long x, int nd = 0, int l = 0, int r = n - 1) {
    if (l > rx || r < lx) return LLONG_MAX;
    if (l >= lx && r <= rx) {
        auto it = tre[nd].lower_bound(x);
        return (it == tre[nd].end() ? LLONG_MAX : *it);
    }
    int m = (l + r) >> 1, lc = (nd << 1) + 1, rc = lc + 1;
    return min(get(lx, rx, x, lc, l, m), get(lx, rx, x, rc, m + 1, r));
}

// Operation:
    cin >> n >> q;
    for (i = 0; i < n; ++i) cin >> ar[i];
    make();
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            long long in, val; cin >> in >> val;
            up(--in, val); ar[in] = val;
        }
        else {
            long long l, r, x; cin >> l >> r >> x;
            long long res = get(--l, --r, x);
            cout << (res == LLONG_MAX ? -1 : res) << '\n';
        }
    }
