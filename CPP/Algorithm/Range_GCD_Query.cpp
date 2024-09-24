// Sparse Table Approach:
// Note: 0-based indexing
// Complexity: Make: O(N * log(N)) Query: O(1)

long long tab[N][(int)log2(N)], ar[N], n;
auto make() {
	for (int i = 0; i < n; ++i) tab[i][0] = ar[i];
	for (int j = 1; (1ll << j) <= n; ++j) {
		for (int i = 0; i <= n - (1ll << j); ++i)
			tab[i][j] = gcd(tab[i][j - 1], tab[i + (1ll << (j - 1))][j - 1]);
	}
}
long long gc(auto L, auto R) {
	int j = log2(R - L + 1);
	return gcd(tab[L][j], tab[R - (1ll << j) + 1][j]);
}

// Operation:
	cin >> n;
	for (i = 0; i < n; ++i) cin >> ar[i];
	make();
	cout << gc(0, 2) << '\n';


// Segment Tree Approach:
// Note: 0-based indexing
// Complexity: Make: O(N * log(min(a, b))) Query: O(log(N) * log(min(a, b)))

long long* tre; long long ar[N], n;

long long build(auto ss = 0, auto se = n - 1, auto si = 0) {
	if (ss == se) return tre[si] = ar[ss];
	long long mid = ss + ((se - ss) >> 1);
	return tre[si] = gcd(build(ss, mid, (si << 1) + 1), build(mid + 1, se, (si << 1) + 2));
}
auto* make() {
	tre = new long long[((1 << (int)(ceil(log2(n)))) << 1) - 1];
	build(); return tre;
}
long long gc(auto qs, auto qe, auto ss = 0, auto se = n - 1, auto si = 0) {
	if (ss > qe || se < qs) return 0;
	if (qs <= ss && qe >= se) return tre[si];
	long long mid = ss + ((se - ss) >> 1);
	return gcd(gc(qs, qe, ss, mid, (si << 1) + 1), gc(qs, qe, mid + 1, se, (si << 1) + 2));
}

// Operation:
	cin >> n;
	for (i = 0; i < n; ++i) cin >> ar[i];
	make();
	cout << gc(1, 2) << '\n';