// Complexity: O(n)

long long xsum() {
	long long bit = 0;
	for (int i = 0; i < n; ++i) bit |= ar[i];
	return bit * (1ll << (n - 1));
}