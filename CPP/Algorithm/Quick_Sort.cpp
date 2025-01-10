// Complexity: O(n * log(n)); Worst Case: O(n^2)

int n, ar[N];
int partition(int l, int r) {
	int pivot = ar[l], i = l, j = r;
    while (i < j) {
        while (ar[i] <= pivot) ++i;
        while (ar[j] > pivot) --j;
        if (i < j) swap(ar[i], ar[j]);
    }
    swap(ar[l], ar[j]); return j;
}
void qsrt(int l = 0, int r = n - 1) {
	if (l < r) {
		int pi = partition(l, r);
		qsrt(l, pi - 1); qsrt(pi + 1, r);
	}
}