// Complexity: O(n)
// Note: Repdigit Number is a number n which has all the digits in its representation in base b equal.

bool rd(auto n, auto b) {
	long long p = -1;
	while (n) {
		long long d = n % b; n /= b;
		if (p != -1 && d != p) return false;
		p = d;
	}
	return true;
}