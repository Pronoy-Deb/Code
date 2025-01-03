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
inline int log2Up(int n) {
    int res = 0; while ((1 << res) < n) ++res; return res;
}
struct sqt {
    int n, lg, SZ; vector<int> v, clz, layers, onL;
    vector< vector<int> > pref, suf, b2in;
    inline void makeblk(int layer, int l, int r) {
        pref[layer][l] = v[l];
        for (int i = l + 1; i < r; ++i) pref[layer][i] = op(pref[layer][i - 1], v[i]);
        suf[layer][r - 1] = v[r - 1];
        for (int i = r - 2; i >= l; --i) suf[layer][i] = op(v[i], suf[layer][i + 1]);
    }
    inline void makeb2in(int layer, int L, int R, int b2inof) {
        int bsl = (layers[layer] + 1) >> 1;
        int bcl = layers[layer] >> 1, bSz = 1 << bsl;
        int bc = (R - L + bSz - 1) >> bsl;
        for (int i = 0; i < bc; ++i) {
            for (int j = i, ans; j < bc; ++j) {
                int add = suf[layer][L + (j << bsl)];
                ans = (i == j) ? add : op(ans, add);
                b2in[layer-1][b2inof + L + (i << bcl) + j] = ans;
            }
        }
    }
    inline void makeb2in0() {
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
    inline int get(int l, int r, int b2inof = 0, int base = 0) {
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
    sqt(const auto &a) : n(a.size()), lg(log2Up(n)), v(a), clz(1 << lg), onL(lg + 1) {
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
    sqt t(ar); int sz = (q >> 6) + 2, x = 0, l = 0, r = 0;
    int b[sz]; for (int i = 0; i < sz; ++i) cin >> b[i];
    for (int i = 0; i < q; ++i) {
        if (i % 64) l = (l + x) % n, r = (r + x) % n;
        else l = (b[i >> 6] + x) % n, r = (b[(i >> 6) + 1] + x) % n;
        if (l > r) swap(l, r);
        x = (t.get(l, r) % p + 1) % p;
    }
    cout << x << '\n';