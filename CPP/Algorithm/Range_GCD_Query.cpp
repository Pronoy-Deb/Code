// Sparse Table Approach:
// Note: 0-based indexing
// Complexity: Make: O(N * log(N)) Query: O(1)

int64_t tab[N][21], aa[N], n;
auto make() {
	for (int i = 0; i < n; ++i) tab[i][0] = aa[i];
	for (int j = 1; (1ll << j) <= n; ++j) {
		for (int i = 0; i <= n - (1ll << j); ++i)
			tab[i][j] = gcd(tab[i][j - 1], tab[i + (1ll << (j - 1))][j - 1]);
	}
}
int64_t gc(int L, int R) {
	int j = log2(R - L + 1);
	return gcd(tab[L][j], tab[R - (1ll << j) + 1][j]);
}

// Operation:
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> aa[i];
	make();
	cout << gc(0, 2) << '\n';


// Segment Tree Approach:
// Note: 0-based indexing
// Complexity: Make: O(N * log(min(a, b))) Query: O(log(N) * log(min(a, b)))

int64_t* tre; int64_t aa[N], n;

int64_t build(auto ss = 0, auto se = n - 1, auto si = 0) {
	if (ss == se) return tre[si] = aa[ss];
	int64_t mid = ss + ((se - ss) >> 1);
	return tre[si] = gcd(build(ss, mid, (si << 1) + 1), build(mid + 1, se, (si << 1) + 2));
}
auto* make() {
	tre = new int64_t[((1 << (int)(ceil(log2(n)))) << 1) - 1];
	build(); return tre;
}
int64_t gc(auto qs, auto qe, auto ss = 0, auto se = n - 1, auto si = 0) {
	if (ss > qe || se < qs) return 0;
	if (qs <= ss && qe >= se) return tre[si];
	int64_t mid = ss + ((se - ss) >> 1);
	return gcd(gc(qs, qe, ss, mid, (si << 1) + 1), gc(qs, qe, mid + 1, se, (si << 1) + 2));
}

// Operation:
	cin >> n;
	for (i = 0; i < n; ++i) cin >> aa[i];
	make();
	cout << gc(1, 2) << '\n';