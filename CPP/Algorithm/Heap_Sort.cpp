// Complexity: O(n*log(n))

void heapify(auto i, auto j) {
	int mx = j, l = (j << 1) + 1, r = (j << 1) + 2;
	if (l < i && ar[l] > ar[mx]) mx = l;
	if (r < i && ar[r] > ar[mx]) mx = r;
	if (mx != j) {
        swap(ar[j], ar[mx]); heapify(i, mx);
	}
}
void hsrt() {
	for (int i = (n >> 1) - 1; i >= 0; --i)
		heapify(n, i);
	for (int i = n - 1; i > 0; --i) {
		swap(ar[0], ar[i]); heapify(i, 0);
	}
}