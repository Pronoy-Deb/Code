// Sparse Table approach: For Static Array:
// Complexity: Make: O(nlog(n)) Query: O(1)

const int L = 21;
int tab[N][L], ar[N], n;
void make() {
	for (int i = 1; i <= n; ++i) tab[i][0] = ar[i];
	for (int k = 1; k < L; ++k) {
		for (int i = 1; i + (1 << k) - 1 <= n; ++i)
			tab[i][k] = min(tab[i][k - 1], tab[i + (1 << (k - 1))][k - 1]);
	}
}
int get(int l, int r) {
	int k = 31 - __builtin_clz(r - l + 1);
	return min(tab[l][k], tab[r - (1 << k) + 1][k]);
}

// Segment Tree approach:
// Complexity: Make: O(n) Query: O(log(n))
// For Dynamic Array:

long long tre[N << 1], ar[N], n;
long long com(long long x, long long y) { return min(x, y); }
void make() {
    for (int i = 0; i < n; ++i) tre[n + i] = ar[i];
    for (int i = n - 1; i > 0; --i) tre[i] = com(tre[i << 1], tre[i << 1 | 1]);
}
void up(int in, long long val) {
    in += n; tre[in] = val;
    for (int i = in; i > 1; i >>= 1) tre[i >> 1] = com(tre[i], tre[i ^ 1]);
}
long long get(int l, int r) {
    long long res = LLONG_MAX;
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = com(res, tre[l++]); if (r & 1) res = com(res, tre[--r]);
    }
    return res;
}

// With Range Compression:
// const long long N = 4 * 2e5 + 5;
long long l[N], r[N], n;
long long com() {
    set<long long> st;
	for (int i = 0; i < n; ++i) {
        st.insert(l[i]); st.insert(l[i] + 1);
        st.insert(r[i]); st.insert(r[i] + 1);
    }
    map<long long, int> mp;
    int k = 0; for (auto &e : st) mp[e] = ++k;
    for (int i = 0; i < n; ++i) {
        l[i] = mp[l[i]]; r[i] = mp[r[i]];
    }
    return k;
}

// Operation:
    cin >> n; k = n;
    for (i = 0; i < n; ++i) { cin >> l[i] >> r[i]; }
    n = com();
    for (i = 0; i < k; ++i) {
        ar[l[i]]++; ar[r[i] + 1]--;
    }
    for (i = 1; i <= n; ++i) ar[i] += ar[i - 1];
    make();
    for (i = 0; i < k; ++i) {
        if (get(l[i], r[i]) > 1) {
            cout << i + 1 << '\n'; return;
        }
    }
    cout << -1;

// Problem: https://codeforces.com/contest/863/problem/E

// With the frequency of the minimum number:
// Problem: https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/C

pair<long long, int> tre[N << 1]; long long ar[N], n;
void make() {
    for (int i = 0; i < n; ++i) tre[n + i] = {ar[i], 1};
    for (int i = n - 1; i > 0; --i) {
        if (tre[i << 1].first < tre[i << 1 | 1].first) tre[i] = tre[i << 1];
        else if (tre[i << 1].first > tre[i << 1 | 1].first) tre[i] = tre[i << 1 | 1];
        else tre[i] = {tre[i << 1].first, tre[i << 1].second + tre[i << 1 | 1].second};
    }
}
void up(int in, long long val) {
    in += n; tre[in] = {val, 1};
    for (int i = in; i > 1; i >>= 1) {
        if (tre[i].first < tre[i ^ 1].first) tre[i >> 1] = tre[i];
        else if (tre[i].first > tre[i ^ 1].first) tre[i >> 1] = tre[i ^ 1];
        else tre[i >> 1] = {tre[i].first, tre[i].second + tre[i ^ 1].second};
    }
}
auto get(int l, int r) {
    pair<long long, int> res = {LLONG_MAX, 0}; ++r;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            if (tre[l].first < res.first) res = tre[l];
            else if (tre[l].first == res.first) res.second += tre[l].second;
            ++l;
        }
        if (r & 1) {
            if (tre[--r].first < res.first) res = tre[r];
            else if (tre[r].first == res.first) res.second += tre[r].second;
        }
    }
    return res;
}

// WITH lazy Propagation: O(n)

long long tre[N << 1], lz[N], ar[N], n;
long long com(long long x, long long y) { return min(x, y); }
void make() {
    for (int i = 0; i < n; ++i) tre[i + n] = ar[i];
    for (int i = n - 1; i > 0; --i) tre[i] = com(tre[i << 1], tre[i << 1 | 1]);
}
void apply(int in, long long val) { tre[in] += val; if (in < n) lz[in] += val; }
void push(int l, int r) {
    int s = (sizeof(int) << 3) - __builtin_clz(n);
    for (l += n, r += n - 1; s > 0; --s) {
        for (int i = l >> s; i <= r >> s; ++i) {
            if (lz[i]) {
                apply(i << 1, lz[i]); apply(i << 1 | 1, lz[i]); lz[i] = 0;
            }
        }
    }
}
void rebuild(int l, int r) {
    for (l += n, r += n - 1; l > 1;) {
        l >>= 1, r >>= 1;
        for (int i = r; i >= l; --i) tre[i] = com(tre[i << 1], tre[i << 1 | 1]) + lz[i];
    }
}
void add(int l, int r, long long val) {
    push(l, l + 1); push(r, ++r); int l0 = l, r0 = r;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) apply(l++, val); if (r & 1) apply(--r, val);
    }
    rebuild(l0, l0 + 1); rebuild(r0 - 1, r0);
}
long long get(int l, int r) {
    push(l, l + 1); push(r, ++r); long long res = LLONG_MAX;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = com(res, tre[l++]); if (r & 1) res = com(res, tre[--r]);
    }
    return res;
}

// OR,

long long tre[N << 2], lz[N << 2], ar[N], n;
long long com(long long x, long long y) { return min(x, y); }
void make(int s = 0, int e = n - 1, int i = 0) {
	if (s >= e) {
        if (s == e) tre[i] = ar[s]; return;
	}
	int m = (s + e) >> 1, lc = (i << 1) + 1, rc = lc + 1;
	make(s, m, lc); make(m + 1, e, rc);
	tre[i] = com(tre[lc], tre[rc]);
}
void propagate(int s, int e, int i) {
	if (lz[i]) {
		tre[i] += lz[i];
		if (s != e) {
			lz[(i << 1) + 1] += lz[i]; lz[(i << 1) + 2] += lz[i];
		}
		lz[i] = 0;
	}
}
void add(int l, int r, long long val, int s = 0, int e = n - 1, int i = 0) {
    propagate(s, e, i);
	if (s > e || s > r || e < l) return;
	int m = (s + e) >> 1, lc = (i << 1) + 1, rc = lc + 1;
	if (s >= l && e <= r) {
		tre[i] += val;
		if (s != e) {
			lz[lc] += val; lz[rc] += val;
		}
		return;
	}
	add(l, r, val, s, m, lc); add(l, r, val, m + 1, e, rc);
	tre[i] = com(tre[lc], tre[rc]);
}
long long get(int l, int r, int s = 0, int e = n - 1, int i = 0) {
	if (l < 0 || r > n - 1 || l > r) return LLONG_MAX;
	propagate(s, e, i);
	if (s > e || s > r || e < l) return LLONG_MAX;
	if (s >= l && e <= r) return tre[i];
	int m = (s + e) >> 1, lc = (i << 1) + 1, rc = lc + 1;
	return com(get(l, r, s, m, lc), get(l, r, m + 1, e, rc));
}

// OR,

int lg2[N];
void pre() {
    lg2[1] = 0; for (int i = 2; i < N; ++i) lg2[i] = lg2[i >> 1] + 1;
}
struct rmq {
    vector<long long> v[25];
    long long com(long log x, long long y) { return min(x, y); }
    rmq(const vector<long long> &a) {
        int n = a.size(); v[0] = a;
        for (int k = 0; (1 << (k + 1)) <= n; ++k) {
            v[k + 1].resize(n);
            for (int i = 0; i - 1 + (1 << (k + 1)) < n; ++i)
                v[k + 1][i] = com(v[k][i], v[k][i + (1 << k)]);
        }
    }
    long long get(int i, int j) {
        int k = lg2[j - i + 1];
        return com(v[k][i], v[k][j + 1 - (1 << k)]);
    }
};

// Operation:
    pre();
    vector<long long> v = {1, 2, 3, 4};
    rmq rmq(v);
    cout << rmq.get(1, 2);

// 2-D Range Minimum Query (Static) Using Sparse Table:

const int N = 5e2 + 5, L = 11;
long long tab[L][N][L][N], lg2[N], ar[N][N], n, m;
void make() {
	for (int j = 0; j < n; ++j) {
		lg2[j] = (j > 1 ? lg2[j >> 1] + 1 : 0);
		for (int l = 0; l < m; ++l) tab[0][j][0][l] = ar[j][l];
		for (int k = 0; (1 << (k + 1)) <= m; ++k) {
			for (int l = 0; l + (1 << (k + 1)) <= m; ++l)
				tab[0][j][k + 1][l] = min(tab[0][j][k][l], tab[0][j][k][l + (1 << k)]);
		}
	}
	for (int i = n, j = (n > m ? n : m); i <= j; ++i) lg2[i] = lg2[i >> 1] + 1;
	for (int i = 0; (1 << (i + 1)) <= n; ++i) {
		for (int j = 0; j + (1 << (i + 1)) <= n; ++j) {
			for (int k = 0; (1 << k) <= m; ++k) {
				for (int l = 0; l + (1 << k) <= m; ++l)
					tab[i + 1][j][k][l] = min(tab[i][j][k][l], tab[i][j + (1 << i)][k][l]);
			}
		}
	}
}
long long get(int x1, int y1, int x2, int y2) {
	int x = lg2[x2 - x1 + 1], y = lg2[y2 - y1 + 1];
	return min({tab[x][x1][y][y1], tab[x][x1][y][y2 - (1 << y) + 1], tab[x][x2 - (1 << x) + 1][y][y1], tab[x][x2 - (1 << x) + 1][y][y2 - (1 << y) + 1]});
}