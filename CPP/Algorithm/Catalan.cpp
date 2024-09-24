// Complexity: O(n)
// For n catalan numbers using pre-calculation:

long long cat[N];
void pre() {
	cat[0] = 1;
	for (int i = 1; i < N; ++i)
		cat[i] = (cat[i - 1] * ((i << 2) - 2)) / (i + 1);
}

// For n-th catalan number:

long long cat(long long n) {
	long long res = 1;
	for (int i = 0; i < n; ++i) {
		res *= ((n << 1) - i); res /= (i + 1);
	}
	return res / ++n;
}