// Complexity: O(N * log(max(ar[i]) * log(N))

long long tab[N][(int)log2(N)], ar[N], n;
void pre() {
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
long long sum() {
	make(); long long ans = 0;
	for (int i = 0; i < n; ++i) {
		long long ep = i, pep = i, val = ar[i];
		while (ep < n) {
			long long lo = pep, hi = n - 1;
			while (hi > lo) {
				long long mid = (hi + lo + 1) >> 1;
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