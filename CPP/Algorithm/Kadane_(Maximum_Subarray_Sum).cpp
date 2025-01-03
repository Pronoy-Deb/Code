// Complexity: O(n)
// To determine the summation:

long long mss(auto &ar) {
	long long n = ar.size(), mx = ar[0], res = 0;
	for (int i = 0; i < n; ++i) {
		res += ar[i]; mx = max(mx, res); res = max(res, 0ll);
	}
	return mx;
}

// To determine the indices of the range with the summation:
auto mss(auto &ar) {
	long long n = ar.size(), mx = ar[0], res = 0, start = 0, end = 0, s = 0;
	for (int i = 0; i < n; ++i) {
		res += ar[i];
		if (mx < res) { mx = res; start = s; end = i; }
		if (res < 0) { res = 0; s = i + 1; }
	}
	return make_pair(make_pair(start, end), mx);
}

// Recursive Approach:
long long ar[N], n;
long long mss() {
	if (n == 1) return ar[0];
	long long m = (n >> 1), lmx = mss(ar, m), rmx = mss(ar + m, n - m);
	long long lsum = LLONG_MIN, rsum = LLONG_MIN, sum = 0;
	for (int i = m; i < n; ++i) {
		sum += ar[i]; rsum = max(rsum, sum);
	}
	sum = 0;
	for (int i = m - 1; i >= 0; --i) {
		sum += ar[i]; lsum = max(lsum, sum);
	}
	return max(lsum + rsum, max(lmx, rmx));
}