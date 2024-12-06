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

long long tre[N << 1], lz[N], n;
inline long long op(long long x, long long y) { return (x + y); }
inline void apply(int in, long long val, int k) {
    tre[in] += val * k; if (in < n) lz[in] += val;
}
void push(int l, int r) {
    int s = (sizeof(int) << 3) - __builtin_clz(n), k = 1 << (s - 1);
    for (l += n, r += n - 1; s > 0; --s, k >>= 1) {
        for (int i = l >> s; i <= r >> s; ++i) {
            if (lz[i]) {
                apply(i << 1, lz[i], k); apply(i << 1 | 1, lz[i], k); lz[i] = 0;
            }
        }
    }
}
void rebuild(int l, int r) {
    int k = 2;
    for (l += n, r += n - 1; l > 1; k <<= 1) {
        l >>= 1, r >>= 1;
        for (int i = r; i >= l; --i) tre[i] = op(tre[i << 1], tre[i << 1 | 1]) + lz[i] * k;
    }
}
void inc(int l, int r, long long val) {
    if (l < 0 || r >= n) return;
    push(l, l + 1); push(r, ++r); int l0 = l, r0 = r, k = 1;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1) {
        if (l & 1) apply(l++, val, k); if (r & 1) apply(--r, val, k);
    }
    rebuild(l0, l0 + 1); rebuild(r0 - 1, r0);
}
long long get(int l, int r) {
    long long res = 0; if (l < 0 || r >= n) return res;
    push(l, l + 1); push(r, ++r);
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = op(res, tre[l++]); if (r & 1) res = op(res, tre[--r]);
    }
    return res;
}
void reset() {
    for (int i = 0; i <= n; ++i) tre[i] = tre[i + n] = lz[i] = 0;
}

void test(int32_t tc) {
    ll nn = 0, m = M, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    // cin >> n;
    string s, r; cin >> s; r = s;
    vector<int> ar[10];
    n = s.size(); bool vis[n]{};
    for (i = n - 1; i >= 0; --i) { ar[s[i] - '0'].push_back(i); }
    vector<int> ind;
    for (j = 0; j < n; ++j) {
        c = -1; m = M; int val = -1, en = -1, digit = -1, in = -1;
        for (i = 9; i > 0; --i) {
            if (!ar[i].empty()) {
                d = ar[i].back();
                if (d == 0) continue;
                b = get(d, d);
                a = i - (d + b - j);
                if (a >= 0 and (a > c or (a == c and d + b < m))) {
                    c = a;
                    // s[j] = a + '0';
                    // inc(j, d - 1, 1);
                    val = a;
                    en = d + b - 1;
                    m = d + b;
                    digit = i;
                    in = d;
                    // ar[i].pop_back();
                }
            }
        }
        if (val != -1) {
            s[j] = val + '0';
            vis[in] = 1;
            ck(tc, j);
            inc(j, en, 1);
            ar[digit].pop_back();
        }
        else ind.push_back(j);
    }
    // for (i=0;i<n;++i) if(!vis[i]) ind.push_back(i);
    ck(ind);
    int sz = ind.size();
    i = 0, j = 0;
    while(i < sz and j < n) {
        if(!vis[j]) {
            s[j] = r[ind[i]];
            i++, j++;
        }
        else j++;
    }
    cout << s;
    cout << '\n';
    reset();
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}