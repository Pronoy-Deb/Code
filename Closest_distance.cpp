#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ll long long
#define pe(c) for (auto e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const ll M = 1e9 + 7, N = 2e5 + 5;

const int k = 2; // Dimension
struct point {
    long long p[k];
    bool operator!=(const point &a) const {
        bool ok = 1;
        for (int i = 0; i < k; ++i) ok &= (p[i] == a.p[i]);
        return !ok;
    }
};
struct kd_node {
    int axis, value; point p; kd_node *left, *right;
};
struct cmp {
    int axis;
    cmp(int x) : axis(x) {}
    bool operator()(const point &a, const point &b) const {
        return a.p[axis] < b.p[axis];
    }
};
typedef kd_node *node_ptr;
node_ptr root; point ar[N]; int n;
long long manhattan(point a, point b) {
    long long res = 0;
    for (int i = 0; i < k; ++i) res += abs(a.p[i] - b.p[i]);
        // res += (a.p[i] - b.p[i]) * (a.p[i] - b.p[i]);
    return res;
}
void make(node_ptr &node = root, int from = 0, int to = n - 1, int axis = 0) {
    if (from > to) { node = NULL; return; }
    node = new kd_node();
    if (from == to) {
        node->p = ar[from]; node->left = NULL;
        node->right = NULL; return;
    }
    int mid = (from + to) >> 1;
    nth_element(ar + from, ar + mid, ar + to + 1, cmp(axis));
    node->value = ar[mid].p[axis]; node->axis = axis;
    make(node->left, from, mid, (axis + 1) % k);
    make(node->right, mid + 1, to, (axis + 1) % k);
}
long long get(node_ptr node, point q) {
	long long ans = M * M; if (node == NULL) return ans;
    if (node->left == NULL && node->right == NULL) {
        if (q != node->p) ans = min(ans, manhattan(node->p, q)); // Change accordingly
        return ans;
    }
    if (q.p[node->axis] <= node->value) {
        ans = min(ans, get(node->left, q));
        if (q.p[node->axis] + ans >= node->value) ans = min(ans, get(node->right, q));
    }
    else {
        ans = min(ans, get(node->right, q));
        if (q.p[node->axis] - ans <= node->value) ans = min(ans, get(node->left, q));
    }
	return ans;
}

void test(int32_t tc) {
    cin >> n; point pts[n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) cin >> ar[i].p[j];
        pts[i] = ar[i];
    }
    make();
    for (int i = 0; i < n; ++i) cout << get(root, pts[i]) << '\n';
}

int32_t main() {
	cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
	int32_t tc = 0, tt = 1;
	// cin >> tt;
	while (tc++ < tt) test(tc);
	return 0;
}