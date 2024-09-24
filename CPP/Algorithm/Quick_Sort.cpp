// Complexity: O(n*log(n))

long long partition(auto l, auto h) {
	long long pivot = ar[l], i = l, j = h;
    while (i < j) {
        while (ar[i] <= pivot) ++i;
        while (ar[j] > pivot) --j;
        if (i < j) swap(ar[i], ar[j]);
    }
    swap(ar[l], ar[j]); return j;
}
void qsrt(auto l = 0, auto h = n - 1) {
	if (l < h) {
		long long pi = partition(l, h);
		qsrt(l, pi - 1); qsrt(pi + 1, h);
	}
}