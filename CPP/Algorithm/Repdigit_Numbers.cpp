// Complexity: O(n)
// Note: Repdigit Number is a number n which has all the digits in its representation in base b equal.

bool rd(int64_t n, int64_t b) {
	int64_t p = -1;
	while (n) {
		int64_t d = n % b; n /= b;
		if (p != -1 && d != p) return false;
		p = d;
	}
	return true;
}