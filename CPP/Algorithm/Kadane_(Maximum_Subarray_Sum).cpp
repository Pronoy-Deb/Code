// Complexity: O(n)
// To determine the summation:

int64_t mss(auto &aa) {
	int64_t n = aa.size(), mx = aa[0], res = 0;
	for (int i = 0; i < n; ++i) {
		res += aa[i]; mx = max(mx, res); res = max(res, 0ll);
	}
	return mx;
}

// To determine the indices of the range with the summation:
auto mss(auto &aa) {
	int64_t n = aa.size(), mx = aa[0], res = 0, start = 0, end = 0, s = 0;
	for (int i = 0; i < n; ++i) {
		res += aa[i];
		if (mx < res) { mx = res; start = s; end = i; }
		if (res < 0) { res = 0; s = i + 1; }
	}
	return make_pair(make_pair(start, end), mx);
}

// Recursive Approach:
int64_t aa[N], n;
int64_t mss() {
	if (n == 1) return aa[0];
	int64_t m = (n >> 1), lmx = mss(aa, m), rmx = mss(aa + m, n - m);
	int64_t lsum = LLONG_MIN, rsum = LLONG_MIN, sum = 0;
	for (int i = m; i < n; ++i) {
		sum += aa[i]; rsum = max(rsum, sum);
	}
	sum = 0;
	for (int i = m - 1; i >= 0; --i) {
		sum += aa[i]; lsum = max(lsum, sum);
	}
	return max(lsum + rsum, max(lmx, rmx));
}