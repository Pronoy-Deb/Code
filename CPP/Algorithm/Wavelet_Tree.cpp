/*  -Wavelet tree- 1-based indexing
 *  M : maximum value in the array
 *  valaues can be negetive as well
 *  Use appropirate maximum & minimum value (M, -M)
 *  The array changes after applying init
 */

struct wltre {
    wltre *l, *r; int64_t lo, hi, *b, *c, bsz, csz;  // c holds the prefix sum of elements
    wltre() { lo = 1, hi = bsz = csz = 0, l = r = NULL; }
    void init(int64_t *from, int64_t *to, int64_t x, int64_t y) {
        lo = x, hi = y; if (from >= to) return;
        int64_t mid = (lo + hi) >> 1;
        auto f = [mid](int64_t x) { return x <= mid; };
        b = (int64_t *)malloc((to - from + 2) * sizeof(int64_t));
        bsz = 0, b[bsz++] = 0;
        c = (int64_t *)malloc((to - from + 2) * sizeof(int64_t));
        csz = 0, c[csz++] = 0;
        for (auto it = from; it != to; ++it) {
            b[bsz] = (b[bsz - 1] + f(*it));
            c[csz] = (c[csz - 1] + (*it));
            ++bsz, ++csz;
        }
        if (hi == lo) return;
        auto pivot = stable_partition(from, to, f);
        l = new wltre(); l->init(from, pivot, lo, mid);
        r = new wltre(); r->init(pivot, to, mid + 1, hi);
    }
    // k-th smallest element in [l, r]
    // for array [1,2,1,3,5] 2nd smallest is 1 and 3rd smallest is 2
    int64_t kth(int l, int r, int k) {
        if (l > r) return 0; if (lo == hi) return lo;
        int64_t inLeft = b[r] - b[l - 1], lb = b[l - 1], rb = b[r];
        if (k <= inLeft) return this->l->kth(lb + 1, rb, k);
        return this->r->kth(l - lb, r - rb, k - inLeft);
    }
    // count of numbers in [l, r] Less than or equal to k
    int lte(int l, int r, int64_t k) {
        if (l > r || k < lo) return 0;
        if (hi <= k) return r - l + 1;
        int64_t lb = b[l - 1], rb = b[r];
        return this->l->lte(lb + 1, rb, k) + this->r->lte(l - lb, r - rb, k);
    }
    // count of numbers in [l, r] equal to k
    int count(int l, int r, int64_t k) {
        if (l > r || k < lo || k > hi) return 0;
        if (lo == hi) return r - l + 1;
        int64_t lb = b[l - 1], rb = b[r], mid = (lo + hi) >> 1;
        if (k <= mid) return this->l->count(lb + 1, rb, k);
        return this->r->count(l - lb, r - rb, k);
    }
    // sum of numbers in [l ,r] less than or equal to k
    int64_t sum(int l, int r, int64_t k) {
        if (l > r or k < lo) return 0;
        if (hi <= k) return c[r] - c[l - 1];
        int64_t lb = b[l - 1], rb = b[r];
        return this->l->sum(lb + 1, rb, k) + this->r->sum(l - lb, r - rb, k);
    }
    ~wltre() { delete l, delete r; }
} t;


// Operation:
	cin >> n >> q;
    int64_t ar[N]; for (i = 1; i <= n; ++i) cin >> ar[i];
	t.init(ar + 1, ar + n + 1, -M, M);
	while (q--) {
		int l, r, k; cin >> l >> r >> k;
		cout << t.kth(l + 1, r, k + 1) << '\n';
	}

// OR, Note: Ranges are [l, r), gives TLE

struct node {
    int x, y, s;
    node *p = 0;
    node *l = 0;
    node *r = 0;

    node(int v) {
        x = v;
        y = v;
        s = 1;
    }

    void upd() {
        s = 1;
        y = x;
        if (l) {
            y += l->y;
            s += l->s;
        }

        if (r) {
            y += r->y;
            s += r->s;
        }
    }

    int left_size() {
        return l ? l->s : 0;
    }
};

struct splay_tree {
    node *root = 0;

    void rot(node *c) {
        auto p = c->p;
        auto g = p->p;

        if (g)
            (g->l == p ? g->l : g->r) = c;

        if (p->l == c) {
            p->l = c->r;
            c->r = p;
            if (p->l) p->l->p = p;
        } else {
            p->r = c->l;
            c->l = p;
            if (p->r) p->r->p = p;
        }

        p->p = c;
        c->p = g;

        p->upd();
        c->upd();
    }

    void splay(node *c) {
        while (c->p) {
            auto p = c->p;
            auto g = p->p;

            if (g) rot((g->l == p) == (p->l == c) ? p : c);
            rot(c);
        }
        c->upd();
        root = c;
    }

    node *join(node *l, node *r) {
        if (not l) return r;
        if (not r) return l;

        while (l->r) l = l->r;

        splay(l);
        r->p = l;
        l->r = r;
        l->upd();

        return l;
    }

    pair<node *, node *> split(node *p, int idx) {
        if (not p)
            return make_pair(nullptr, nullptr);

        if (idx < 0)
            return make_pair(nullptr, p);

        if (idx >= p->s)
            return make_pair(p, nullptr);

        for (int lf = p->left_size(); idx != lf; lf = p->left_size()) {
            if (idx < lf)
                p = p->l;
            else
                p = p->r, idx -= lf + 1;
        }

        splay(p);

        node *l = p;
        node *r = p->r;
        if (r) {
            l->r = r->p = 0;
            l->upd();
        }
        return make_pair(l, r);
    }

    node *get(int idx) {
        auto p = root;
        for (int lf = p->left_size(); idx != lf; lf = p->left_size()) {
            if (idx < lf)
                p = p->l;
            else
                p = p->r, idx -= lf + 1;
        }

        splay(p);

        return p;
    }

    int insert(int idx, int x) {
        node *l, *r;
        tie(l, r) = split(root, idx - 1);
        int v = l ? l->y : 0;
        root = join(l, join(new node(x), r));
        return v;
    }

    void erase(int idx) {
        node *l, *r;
        tie(l, r) = split(root, idx);
        root = join(l->l, r);
        delete l;
    }

    void append(int x) {
        root = join(root, new node(x));
    }

    int rank(int idx) {
        node *l, *r;
        tie(l, r) = split(root, idx);
        int x = (l && l->l ? l->l->y : 0);
        root = join(l, r);
        return x;
    }

    int operator[](int idx) {
        return rank(idx);
    }

    ~splay_tree() {
        if (!root)
            return;

        vector<node *> nodes{root};
        while (nodes.size()) {
            auto u = nodes.back();
            nodes.pop_back();
            if (u->l) nodes.emplace_back(u->l);
            if (u->r) nodes.emplace_back(u->r);
            delete u;
        }
    }
};

struct wlt {
    int A, Z;
    wlt *l = 0;
    wlt *r = 0;
    splay_tree b;

    wlt(int L, int R) {
        A = L;
        Z = R;
        b.insert(0, 0);
    }

    ~wlt() {
        delete l;
        delete r;
    }

    void append(int x) {
        if (A >= Z)
            return;

        int M = (A + Z) / 2;

        if (x <= M) {
            b.append(1);
            l = l ?: new wlt(A, M);
            l->append(x);
        } else {
            b.append(0);
            r = r ?: new wlt(M + 1, Z);
            r->append(x);
        }
    }

    void insert(int idx, int x) {
        if (A >= Z)
            return;

        int M = (A + Z) / 2;

        if (x <= M) {
            l = l ?: new wlt(A, M);
            l->insert(b.insert(idx, 1), x);
        } else {
            r = r ?: new wlt(M + 1, Z);
            r->insert(idx - b.insert(idx, 0), x);
        }
    }

    void erase(int idx) {
        if (A == Z)
            return;

        auto p = b.get(idx);
        int lf = p->l ? p->l->y : 0;
        int x = p->x;
        b.erase(idx);
        if (x == 1)
            l->erase(lf);
        else
            r->erase(idx - lf);
    }

    int kth(int L, int R, int k) {
        if (A == Z)
            return A;

        int x = b.rank(L);
        int y = b.rank(R);

        if (k <= y - x)
            return l->kth(x, y, k);
        else
            return r->kth(L - x, R - y, k - (y - x));
    }
};

// Operation:
    wlt t(-M, M);
    ll n, q; cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        int a; cin >> a; t.insert(i, a);
    }
    while (q--) {
        int l, r, k; cin >> l >> r >> k;
        cout << t.kth(l - 1, r, k) << '\n';
    }