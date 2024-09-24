// Complexity: O(log(min(a, b)))
long long lcm(long long a, long long b) {
	long long c = a * b;
	while (b) {
		long long tmp = a; a = b; b = tmp % b;
	}
	return (c / a);
}

// For 3 numbers:

long long cnt(long long a, long long b, long long c, long long n) {
	return ((n / a) + (n / b) + (n / c) - (n / lcm(a, b)) - (n / lcm(b, c)) - (n / lcm(c, a)) + (n / lcm(lcm(a, b), c)));
}

// For 2 numbers:

long long cnt(long long a, long long b, long long n) {
	return ((n / a) + (n / b) - (n / lcm(a, b)));
}