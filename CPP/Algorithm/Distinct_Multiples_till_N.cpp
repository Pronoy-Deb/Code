// Complexity: O(log(min(a, b)))
int64_t lcm(int64_t a, int64_t b) {
	int64_t c = a * b;
	while (b) {
		int64_t tmp = a; a = b; b = tmp % b;
	}
	return (c / a);
}

// For 3 numbers:

int64_t cnt(int64_t a, int64_t b, int64_t c, int64_t n) {
	return ((n / a) + (n / b) + (n / c) - (n / lcm(a, b)) - (n / lcm(b, c)) - (n / lcm(c, a)) + (n / lcm(lcm(a, b), c)));
}

// For 2 numbers:

int64_t cnt(int64_t a, int64_t b, int64_t n) {
	return ((n / a) + (n / b) - (n / lcm(a, b)));
}