// Complexity: O(n)
// Application: Used to determine the maximum subarray sum.
// To determine the summation:
long long ar[N], n;
long long kad() {
	long long mx = ar[0], res = 0;
	for (int i = 0; i < n; ++i) {
		res += ar[i]; mx = max(mx, res); res = max(res, 0ll);
	}
	return mx;
}

// To determine the indices with summation:
long long ar[N], n;
auto kad() {
	long long mx = ar[0], res = 0, start = 0, end = 0, s = 0;
	for (int i = 0; i < n; ++i) {
		res += ar[i];
		if (mx < res) {
			mx = res; start = s; end = i;
		}
		if (res < 0) {
			res = 0; s = i + 1;
		}
	}
	return make_pair(make_pair(start, end), mx);
}

// Recursive Approach:
long long ar[N], n;
long long kad() {
	if (n == 1) return ar[0];
	long long m = (n >> 1), lmx = kad(ar, m), rmx = kad(ar + m, n - m);
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