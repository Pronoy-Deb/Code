/*
Given an array a that contains n elements and the
operation op that satisfies associative property:
(x op y) op z=x op (y op z) is true for any x, y, z.

The following implementation of Sqrt Tree can perform the following operations:
build in O(nloglogn),
answer queries in O(1) and update an element in O(sqrt(n)).
*/
https://www.codechef.com/problems/SEGPROD

int p;
inline int op(const int &a, const int &b) { return (a * 1ll * b) % p; }
int log2Up(long long n) { int b = 0; while ((1ll << b) < n) ++b; return b; }
struct srt {
    int n, lg, SZ; vector<int> v, clz, layers, onL;
    vector< vector<int> > pref, suf, b2in;
    void makeblk(int layer, int l, int r) {
        pref[layer][l] = v[l];
        for (int i = l + 1; i < r; ++i) pref[layer][i] = op(pref[layer][i - 1], v[i]);
        suf[layer][r - 1] = v[r - 1];
        for (int i = r - 2; i >= l; --i) suf[layer][i] = op(v[i], suf[layer][i + 1]);
    }
    void makeb2in(int layer, int L, int R, int b2inof) {
        int bsl = (layers[layer] + 1) >> 1;
        int bcl = layers[layer] >> 1, bSz = 1 << bsl;
        int bc = (R - L + bSz - 1) >> bsl;
        for (int i = 0; i < bc; ++i) {
            for (int j = i, ans = 0; j < bc; ++j) {
                int add = suf[layer][L + (j << bsl)];
                ans = (i == j) ? add : op(ans, add);
                b2in[layer-1][b2inof + L + (i << bcl) + j] = ans;
            }
        }
    }
    void makeb2in0() {
        int bsl = (lg + 1) >> 1;
        for (int i = 0; i < SZ; ++i) v[n+i] = suf[0][i << bsl];
        make(1, n, n + SZ, (1 << lg) - n);
    }
    inline void upb2in0(int bid) {
        int bsl = (lg + 1) >> 1; v[n + bid] = suf[0][bid << bsl];
        up(1, n, n + SZ, (1 << lg) - n, n + bid);
    }
    void make(int layer, int L, int R, int b2inof) {
        if (layer >= (int)layers.size()) return;
        int bSz = 1 << ((layers[layer]+1) >> 1);
        for (int l = L; l < R; l += bSz) {
            int r = min(l + bSz, R); makeblk(layer, l, r);
            make(layer+1, l, r, b2inof);
        }
        if (!layer) makeb2in0();
        else makeb2in(layer, L, R, b2inof);
    }
    void up(int layer, int L, int R, int b2inof, int x) {
        if (layer >= (int)layers.size()) return;
        int bsl = (layers[layer]+1) >> 1;
        int bSz = 1 << bsl, bin = (x - L) >> bsl;
        int l = L + (bin << bsl), r = min(l + bSz, R);
        makeblk(layer, l, r); if (!layer) upb2in0(bin);
        else makeb2in(layer, L, R, b2inof);
        up(layer+1, l, r, b2inof, x);
    }
    int get(int l, int r, int b2inof = 0, int base = 0) {
        if (l == r) return v[l];
        if (l + 1 == r) return op(v[l], v[r]);
        int layer = onL[clz[(l - base) ^ (r - base)]];
        int bsl = (layers[layer]+1) >> 1, bcl = layers[layer] >> 1;
        int L = (((l - base) >> layers[layer]) << layers[layer]) + base;
        int lb = ((l - L) >> bsl) + 1, rb = ((r - L) >> bsl) - 1;
        int ans = suf[layer][l];
        if (lb <= rb) {
            int add = (!layer) ? (get(n + lb, n + rb, (1 << lg) - n, n)) : (b2in[layer-1][b2inof + L + (lb << bcl) + rb]);
            ans = op(ans, add);
        }
        ans = op(ans, pref[layer][r]); return ans;
    }
    inline void up(int x, const int &item) {
        v[x] = item; up(0, 0, n, 0, x);
    }
    srt(const auto &a) : n(a.size()), lg(log2Up(n)), v(a), clz(1 << lg), onL(lg + 1) {
        clz[0] = 0; for (int i = 1, sz = clz.size(); i < sz; ++i) clz[i] = clz[i >> 1] + 1;
        int tlg = lg;
        while (tlg > 1) {
            onL[tlg] = (int)layers.size();
            layers.push_back(tlg); tlg = (tlg + 1) >> 1;
        }
        for (int i = lg - 1; i >= 0; --i) onL[i] = max(onL[i], onL[i + 1]);
        int b2inL = max(0, (int)layers.size() - 1);
        int bsl = (lg + 1) >> 1, bSz = 1 << bsl;
        SZ = (n + bSz - 1) >> bsl; v.resize(n + SZ);
        pref.assign(layers.size(), vector<int>(n + SZ));
        suf.assign(layers.size(), vector<int>(n + SZ));
        b2in.assign(b2inL, vector<int>((1 << lg) + bSz));
        make(0, 0, n, 0);
    }
};

// Operation:
    int n, q; cin >> n >> p >> q;
    vector<int> ar(n); for (int i = 0; i < n; ++i) { cin >> ar[i]; }
    srt t(ar); int sz = (q >> 6) + 2, x = 0, l = 0, r = 0;
    int b[sz]; for (int i = 0; i < sz; ++i) cin >> b[i];
    for (int i = 0; i < q; ++i) {
        if (i % 64) l = (l + x) % n, r = (r + x) % n;
        else l = (b[i >> 6] + x) % n, r = (b[(i >> 6) + 1] + x) % n;
        if (l > r) swap(l, r);
        x = (t.get(l, r) % p + 1) % p;
    }
    cout << x << '\n';

https://cses.fi/problemset/task/1649

inline long long op(const long long &a, const long long &b) { return min(a, b); }
int log2Up(long long n) { int b = 0; while ((1ll << b) < n) ++b; return b; }
struct srt {
    int n, lg, SZ; vector<long long> v, clz, layers, onL;
    vector<vector<long long>> pref, suf, b2in;
    srt(const auto &ar) : n(ar.size()), lg(log2Up(n)), v(ar), clz(1 << lg), onL(lg + 1) {
        clz[0] = 0; for (int i = 1, sz = clz.size(); i < sz; ++i) clz[i] = clz[i >> 1] + 1;
        int tlg = lg;
        while (tlg > 1) {
            onL[tlg] = (int)layers.size();
            layers.push_back(tlg); tlg = (tlg + 1) >> 1;
        }
        for (int i = lg - 1; i >= 0; --i) onL[i] = max(onL[i], onL[i + 1]);
        int b2inL = max(0, (int)layers.size() - 1);
        int bsl = (lg + 1) >> 1, bSz = 1 << bsl;
        SZ = (n + bSz - 1) >> bsl; v.resize(n + SZ);
        pref.assign(layers.size(), vector<long long>(n + SZ));
        suf.assign(layers.size(), vector<long long>(n + SZ));
        b2in.assign(b2inL, vector<long long>((1 << lg) + bSz));
        make(0, 0, n, 0);
    }
    void makeblk(int layer, int l, int r) {
        pref[layer][l] = v[l];
        for (int i = l + 1; i < r; ++i) pref[layer][i] = op(pref[layer][i - 1], v[i]);
        suf[layer][r - 1] = v[r - 1];
        for (int i = r - 2; i >= l; --i) suf[layer][i] = op(v[i], suf[layer][i + 1]);
    }
    void makeb2in(int layer, int L, int R, int b2inof) {
        int bsl = (layers[layer] + 1) >> 1;
        int bcl = layers[layer] >> 1, bSz = 1 << bsl;
        int bc = (R - L + bSz - 1) >> bsl;
        for (int i = 0; i < bc; ++i) {
            for (long long j = i, ans = LLONG_MAX; j < bc; ++j) {
                long long add = suf[layer][L + (j << bsl)];
                ans = (i == j) ? add : op(ans, add);
                b2in[layer-1][b2inof + L + (i << bcl) + j] = ans;
            }
        }
    }
    void makeb2in0() {
        int bsl = (lg + 1) >> 1;
        for (int i = 0; i < SZ; ++i) v[n + i] = suf[0][i << bsl];
        make(1, n, n + SZ, (1 << lg) - n);
    }
    inline void upb2in0(int bid) {
        int bsl = (lg + 1) >> 1; v[n + bid] = suf[0][bid << bsl];
        up(1, n, n + SZ, (1 << lg) - n, n + bid);
    }
    void make(int layer, int L, int R, int b2inof) {
        if (layer >= (int)layers.size()) return;
        int bSz = 1 << ((layers[layer] + 1) >> 1);
        for (int l = L; l < R; l += bSz) {
            int r = min(l + bSz, R); makeblk(layer, l, r);
            make(layer+1, l, r, b2inof);
        }
        if (!layer) makeb2in0();
        else makeb2in(layer, L, R, b2inof);
    }
    void up(int layer, int L, int R, int b2inof, int in) {
        if (layer >= (int)layers.size()) return;
        int bsl = (layers[layer] + 1) >> 1;
        int bSz = 1 << bsl, bin = (in - L) >> bsl;
        int l = L + (bin << bsl), r = min(l + bSz, R);
        makeblk(layer, l, r); if (!layer) upb2in0(bin);
        else makeb2in(layer, L, R, b2inof);
        up(layer + 1, l, r, b2inof, in);
    }
    inline void up(int in, const long long &val) {
        v[in] = val; up(0, 0, n, 0, in);
    }
    long long get(int l, int r, int b2inof = 0, int base = 0) {
        if (l == r) return v[l];
        if (l + 1 == r) return op(v[l], v[r]);
        int layer = onL[clz[(l - base) ^ (r - base)]];
        int bsl = (layers[layer]+1) >> 1, bcl = layers[layer] >> 1;
        int L = (((l - base) >> layers[layer]) << layers[layer]) + base;
        int lb = ((l - L) >> bsl) + 1, rb = ((r - L) >> bsl) - 1;
        long long ans = suf[layer][l];
        if (lb <= rb) {
            int add = (!layer) ? (get(n + lb, n + rb, (1 << lg) - n, n)) : (b2in[layer-1][b2inof + L + (lb << bcl) + rb]);
            ans = op(ans, add);
        }
        ans = op(ans, pref[layer][r]); return ans;
    }
};

// Operation:
    int n, q; cin >> n >> q;
    vector<ll> ar(n); for (int i = 0; i < n; ++i) { cin >> ar[i]; }
    srt t(ar);
    for (int i = 0; i < q; ++i) {
        int tp, l, r; cin >> tp >> l >> r; --l;
        if (tp == 1) t.up(l, r);
        else cout << t.get(l, --r) << '\n';
    }