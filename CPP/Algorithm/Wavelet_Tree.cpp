/*  -Wavelet Tree-
 *  INF : maximum value in the array
 *  valaues can be negetive as well
 *  Use appropirate maximum & minimum value (INF, -INF)
 *  The array changes after applying init
 */

const long long N = 3e5 + 9, INF = 1e9 + 9;

struct wltre {
    long long lo, hi;
    wltre *l, *r;
    long long *b, *c, bsz, csz;  // c holds the prefix sum of elements
    wltre() { lo = 1, hi = 0, bsz = 0, csz = 0, l = NULL, r = NULL; }
    void init(long long *from, long long *to, long long x, long long y) {
        lo = x, hi = y;
        if (from >= to) return;
        long long mid = (lo + hi) >> 1;
        auto f = [mid](long long x) { return x <= mid; };
        b = (long long *)malloc((to - from + 2) * sizeof(long long));
        bsz = 0, b[bsz++] = 0;
        c = (long long *)malloc((to - from + 2) * sizeof(long long));
        csz = 0, c[csz++] = 0;
        for (auto it = from; it != to; ++it) {
            b[bsz] = (b[bsz - 1] + f(*it));
            c[csz] = (c[csz - 1] + (*it));
            bsz++, csz++;
        }
        if (hi == lo) return;
        auto pivot = stable_partition(from, to, f);
        l = new wltre();
        l->init(from, pivot, lo, mid);
        r = new wltre();
        r->init(pivot, to, mid + 1, hi);
    }
    // k-th smallest element in [l, r]
    // for array [1,2,1,3,5] 2nd smallest is 1 and 3rd smallest is 2
    long long kth(long long l, long long r, long long k) {
        if (l > r) return 0;
        if (lo == hi) return lo;
        long long inLeft = b[r] - b[l - 1], lb = b[l - 1], rb = b[r];
        if (k <= inLeft) return this->l->kth(lb + 1, rb, k);
        return this->r->kth(l - lb, r - rb, k - inLeft);
    }
    // count of numbers in [l, r] Less than or equal to k
    long long LTE(long long l, long long r, long long k) {
        if (l > r || k < lo) return 0;
        if (hi <= k) return r - l + 1;
        long long lb = b[l - 1], rb = b[r];
        return this->l->LTE(lb + 1, rb, k) + this->r->LTE(l - lb, r - rb, k);
    }
    // count of numbers in [l, r] equal to k
    long long count(long long l, long long r, long long k) {
        if (l > r || k < lo || k > hi) return 0;
        if (lo == hi) return r - l + 1;
        long long lb = b[l - 1], rb = b[r];
        long long mid = (lo + hi) >> 1;
        if (k <= mid) return this->l->count(lb + 1, rb, k);
        return this->r->count(l - lb, r - rb, k);
    }
    // sum of numbers in [l ,r] less than or equal to k
    long long sum(long long l, long long r, long long k) {
        if (l > r or k < lo) return 0;
        if (hi <= k) return c[r] - c[l - 1];
        long long lb = b[l - 1], rb = b[r];
        return this->l->sum(lb + 1, rb, k) + this->r->sum(l - lb, r - rb, k);
    }
    ~wltre() { delete l, delete r; }
};

long long a[N];
wltre Tree;

// Operation:
    cin >> n >> q;
    for (i = 1; i <= n; ++i) cin >> a[i];
    Tree.init(a + 1, a + n + 1, -INF, INF);
    while (q--) {
        int l, r, k; cin >> l >> r >> k;
        cout << Tree.kth(l + 1 , r , k + 1) << "\n";
    }