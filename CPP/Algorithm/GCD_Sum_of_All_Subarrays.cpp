// Complexity: O(N * log(max(ar[i]) * log(N))

int64_t tab[N][21], ar[N], n;
void pre() {
	for (int i = 0; i < n; ++i) tab[i][0] = ar[i];
	for (int j = 1; (1ll << j) <= n; ++j) {
		for (int i = 0; i <= n - (1ll << j); ++i)
			tab[i][j] = gcd(tab[i][j - 1], tab[i + (1ll << (j - 1))][j - 1]);
	}
}
int64_t gc(int L, int R) {
	int j = log2(R - L + 1);
	return gcd(tab[L][j], tab[R - (1ll << j) + 1][j]);
}
int64_t sum() {
	make(); int64_t ans = 0;
	for (int i = 0; i < n; ++i) {
		int64_t ep = i, pep = i, val = ar[i];
		while (ep < n) {
			int64_t lo = pep, hi = n - 1;
			while (hi > lo) {
				int64_t mid = (hi + lo + 1) >> 1;
				if (gc(i, mid) == val) lo = mid;
				else hi = mid - 1;
			}
			ep = lo + 1;
			ans += ((ep - pep) * val); pep = ep;
            // val = gcd, (ep - pep) = number of subarrays with gcd == val
			if (ep < n) val = gcd(val, ar[ep]);
		}
	}
	return ans;
}

// Operation:
	cin >> n;
	for (i = 0; i < n; ++i) cin >> ar[i];
	cout << sum();