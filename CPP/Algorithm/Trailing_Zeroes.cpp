// Complexity: O(log5(n))

int64_t tz(int64_t n) {
	int64_t c = 0;
	for (int64_t i = 5; i <= n; i *= 5) c += n / i;
	return c;
}