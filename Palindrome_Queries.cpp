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

int bex(long long n, long long k, const int m) {
    n %= m; long long ans = 1;
    if (n < 0) n += m;
    while (k) {
        if (k & 1) ans = ans * n % m;
        n = n * n % m; k >>= 1;
    }
    return ans;
}
using T = array<int, 2>;
const T MOD = {127657753, 987654319};
const T p = {137, 277};
T operator+(T a, int x) { return {(a[0] + x) % MOD[0], (a[1] + x) % MOD[1]}; }
T operator-(T a, int x) { return {(a[0] - x + MOD[0]) % MOD[0], (a[1] - x + MOD[1]) % MOD[1]}; }
T operator*(T a, int x) { return {(int)((long long)a[0] * x % MOD[0]), (int)((long long)a[1] * x % MOD[1])}; }
T operator+(T a, T x) { return {(a[0] + x[0]) % MOD[0], (a[1] + x[1]) % MOD[1]}; }
T operator-(T a, T x) { return {(a[0] - x[0] + MOD[0]) % MOD[0], (a[1] - x[1] + MOD[1]) % MOD[1]}; }
T operator*(T a, T x) { return {(int)((long long)a[0] * x[0] % MOD[0]), (int)((long long)a[1] * x[1] % MOD[1])}; }
ostream &operator<<(ostream &os, T hash) { return os << "(" << hash[0] << ", " << hash[1] << ")"; }

T pw[N], ipw[N];
void pre() {
    pw[0] = {1, 1};
    for (int i = 1; i < N; ++i) pw[i] = pw[i - 1] * p;
    ipw[0] = {1, 1};
    T ip = {bex(p[0], MOD[0] - 2, MOD[0]), bex(p[1], MOD[1] - 2, MOD[1])};
    for (int i = 1; i < N; ++i) ipw[i] = ipw[i - 1] * ip;
}
struct hs {
    int n; string s; // 1 - indexed
    vector<array<T, 2>> t; // (normal, rev) hash
    array<T, 2> com(array<T, 2> l, array<T, 2> r) {
        l[0] = l[0] + r[0]; l[1] = l[1] + r[1]; return l;
    }
    void make(int nd, int b, int e) {
        if (b == e) {
            t[nd][0] = pw[b] * s[b];
            t[nd][1] = pw[n - b + 1] * s[b]; return;
        }
        int mid = (b + e) >> 1, l = nd << 1, r = l | 1;
        make(l, b, mid); make(r, mid + 1, e);
        t[nd] = com(t[l], t[r]);
    }
    void up(int nd, int b, int e, int i, char x) {
        if (b > i || e < i) return;
        if (b == e && b == i) {
            t[nd][0] = pw[b] * x;
            t[nd][1] = pw[n - b + 1] * x; return;
        }
        int mid = (b + e) >> 1, l = nd << 1, r = l | 1;
        up(l, b, mid, i, x); up(r, mid + 1, e, i, x);
        t[nd] = com(t[l], t[r]);
    }
    array<T, 2> get(int nd, int b, int e, int i, int j) {
        if (b > j || e < i) return {T({0, 0}), T({0, 0})};
        if (b >= i && e <= j) return t[nd];
        int mid = (b + e) >> 1, l = nd << 1, r = l | 1;
        return com(get(l, b, mid, i, j), get(r, mid + 1, e, i, j));
    }
    hs() {}
    hs(string _s) {
        n = _s.size(); s = "." + _s;
        t.resize((n << 2) + 1); make(1, 1, n);
    }
    void up(int i, char c) {
        up(1, 1, n, i, c); s[i] = c;
    }
    T get_hash(int l, int r) { // 1 - indexed
        return get(1, 1, n, l, r)[0] * ipw[l - 1];
    }
    T rev_hash(int l, int r) { // 1 - indexed
        return get(1, 1, n, l, r)[1] * ipw[n - r];
    }
    T get_hash() {
        return get_hash(1, n);
    }
    bool pal(int l, int r) {
        return get_hash(l, r) == rev_hash(l, r);
    }
};

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    pre();
    cin >> n >> q;
    string s; cin >> s;
    hs h(s);
    while (q--) {
        int ty; cin >> ty;
        if (ty == 1) {
            int k; char c;
            cin >> k >> c;
            h.up(k, c);
        }
        else {
            int l, r; cin >> l >> r;
            cout << (h.pal(l, r) ? "YES" : "NO") << '\n';
        }
    }
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}
