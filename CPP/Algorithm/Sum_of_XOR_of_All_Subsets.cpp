// Complexity: O(n)

int64_t xsum() {
	int64_t bit = 0;
	for (int i = 0; i < n; ++i) bit |= ar[i];
	return bit * (1ll << (n - 1));
}