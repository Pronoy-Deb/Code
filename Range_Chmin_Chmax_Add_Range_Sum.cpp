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

long long ar[N], n;
struct Node {
    long long sum, mx1, mx2, mxc, mn1, mn2, mnc, lz;
} tre[N << 2];
void merge(int nd) {
    int lc = nd << 1, rc = lc | 1;
    tre[nd].sum = tre[lc].sum + tre[rc].sum;
    if (tre[lc].mx1 == tre[rc].mx1) {
    	tre[nd].mx1 = tre[lc].mx1;
    	tre[nd].mx2 = max(tre[lc].mx2, tre[rc].mx2);
    	tre[nd].mxc = tre[lc].mxc + tre[rc].mxc;
    }
    else {
    	if (tre[lc].mx1 > tre[rc].mx1) {
    		tre[nd].mx1 = tre[lc].mx1;
    		tre[nd].mx2 = max(tre[lc].mx2, tre[rc].mx1);
    		tre[nd].mxc = tre[lc].mxc;
    	}
        else {
    		tre[nd].mx1 = tre[rc].mx1;
    		tre[nd].mx2 = max(tre[lc].mx1, tre[rc].mx2);
    		tre[nd].mxc = tre[rc].mxc;
    	}
    }
    if (tre[lc].mn1 == tre[rc].mn1) {
    	tre[nd].mn1 = tre[lc].mn1;
    	tre[nd].mn2 = min(tre[lc].mn2, tre[rc].mn2);
    	tre[nd].mnc = tre[lc].mnc + tre[rc].mnc;
    }
    else {
    	if (tre[lc].mn1 < tre[rc].mn1) {
    		tre[nd].mn1 = tre[lc].mn1;
    		tre[nd].mn2 = min(tre[lc].mn2, tre[rc].mn1);
    		tre[nd].mnc = tre[lc].mnc;
    	}
        else {
    		tre[nd].mn1 = tre[rc].mn1;
    		tre[nd].mn2 = min(tre[lc].mn1, tre[rc].mn2);
    		tre[nd].mnc = tre[rc].mnc;
    	}
    }
}
void make(int nd = 1, int s = 0, int e = n - 1) {
    tre[nd].lz = 0;
    if (s == e) {
    	tre[nd].sum = tre[nd].mx1 = tre[nd].mn1 = ar[s];
    	tre[nd].mxc = tre[nd].mnc = 1;
    	tre[nd].mx2 = LLONG_MIN; tre[nd].mn2 = LLONG_MAX; return;
    }
    int m = (s + e) >> 1, lc = nd << 1, rc = lc | 1;
    make(lc, s, m); make(rc, m + 1, e); merge(nd);
}
void push_add(int nd, int s, int e, long long v) {
    if (v == 0) return;
    tre[nd].sum += (e - s + 1) * v; tre[nd].mx1 += v;
    if (tre[nd].mx2 != LLONG_MIN) tre[nd].mx2 += v; tre[nd].mn1 += v;
    if (tre[nd].mn2 != LLONG_MAX) tre[nd].mn2 += v; tre[nd].lz += v;
}
void push_max(int nd, long long v, bool l) {
    if (v >= tre[nd].mx1) return;
    tre[nd].sum -= tre[nd].mx1 * tre[nd].mxc; tre[nd].mx1 = v;
    tre[nd].sum += tre[nd].mx1 * tre[nd].mxc;
    if (l) tre[nd].mn1 = tre[nd].mx1;
    else {
    	if (v <= tre[nd].mn1) tre[nd].mn1 = v;
        else if (v < tre[nd].mn2) tre[nd].mn2 = v;
    }
}
void push_min(int nd, long long v, bool l) {
    if (v <= tre[nd].mn1) return;
    tre[nd].sum -= tre[nd].mn1 * tre[nd].mnc; tre[nd].mn1 = v;
    tre[nd].sum += tre[nd].mn1 * tre[nd].mnc;
    if (l) tre[nd].mx1 = tre[nd].mn1;
    else {
    	if (v >= tre[nd].mx1) tre[nd].mx1 = v;
        else if (v > tre[nd].mx2) tre[nd].mx2 = v;
    }
}
void pushdown(int nd, int s, int e) {
    if (s == e) return; int m = (s + e) >> 1, lc = nd << 1, rc = lc | 1;
    push_add(lc, s, m, tre[nd].lz); push_add(rc, m + 1, e, tre[nd].lz); tre[nd].lz = 0;
    push_max(lc, tre[nd].mx1, s == m); push_max(rc, tre[nd].mx1, m + 1 == e);
    push_min(lc, tre[nd].mn1, s == m); push_min(rc, tre[nd].mn1, m + 1 == e);
}
void stmn(int l, int r, long long v, int nd = 1, int s = 0, int e = n - 1) {
    if (r < s || e < l || v >= tre[nd].mx1) return;
    if (l <= s && e <= r && v > tre[nd].mx2) { push_max(nd, v, s == e); return; }
    pushdown(nd, s, e); int m = (s + e) >> 1, lc = nd << 1, rc = lc | 1;
    stmn(l, r, v, lc, s, m); stmn(l, r, v, rc, m + 1, e); merge(nd);
}
void stmx(int l, int r, long long v, int nd = 1, int s = 0, int e = n - 1) {
    if (r < s || e < l || v <= tre[nd].mn1) return;
    if (l <= s && e <= r && v < tre[nd].mn2) { push_min(nd, v, s == e); return; }
    pushdown(nd, s, e); int m = (s + e) >> 1, lc = nd << 1, rc = lc | 1;
    stmx(l, r, v, lc, s, m); stmx(l, r, v, rc, m + 1, e); merge(nd);
}
void add(int l, int r, long long v, int nd = 1, int s = 0, int e = n - 1) {
    if (r < s || e < l) return;
    if (l <= s && e <= r) { push_add(nd, s, e, v); return; }
    pushdown(nd, s, e); int m = (s + e) >> 1, lc = nd << 1, rc = lc | 1;
    add(l, r, v, lc, s, m); add(l, r, v, rc, m + 1, e); merge(nd);
}
long long get(int l, int r, int nd = 1, int s = 0, int e = n - 1) {
    if (r < s || e < l) return 0; if (l <= s && e <= r) return tre[nd].sum;
    pushdown(nd, s, e); int m = (s + e) >> 1, lc = nd << 1, rc = lc | 1;
    return get(l, r, lc, s, m) + get(l, r, rc, m + 1, e);
}

void test(int tc) {
    ll a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, m = 0, q = 0;
    cin >> n >> q;
    for (i = 0; i < n; ++i) { cin >> ar[i]; }
    make();
    while(q--) {
        cin >> m;
        if(m == 3) {
            cin >> a >> b; cout << get(a, --b) << '\n';
        }
        else if(m == 2) {
            cin >> a >> b >> c; add(a, --b, c);
        }
        else if(m == 0) {
            cin >> a >> b >> c; stmn(a, --b, c);
        }
        else {
            cin >> a >> b >> c; stmx(a, --b, c);
        }
    }
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}