// Complexity: O(log5(n))

auto tz(auto n) {
	long long c = 0;
	for (long long i = 5; i <= n; i *= 5) c += n / i;
	return c;
}