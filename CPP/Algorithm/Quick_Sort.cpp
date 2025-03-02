// Complexity: O(n * log(n)); Worst Case: O(n^2)

int n, aa[N];
int partition(int l, int r) {
	int pivot = aa[l], i = l, j = r;
    while (i < j) {
        while (aa[i] <= pivot) ++i;
        while (aa[j] > pivot) --j;
        if (i < j) swap(aa[i], aa[j]);
    }
    swap(aa[l], aa[j]); return j;
}
void qsrt(int l = 0, int r = n - 1) {
	if (l < r) {
		int pi = partition(l, r);
		qsrt(l, pi - 1); qsrt(pi + 1, r);
	}
}