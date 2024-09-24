// Complexity: O(n * log(n))

void merge(int l, int h, int mid) {
    long long tmp[h - l + 1]; i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= h) tmp[k++] = ar[(ar[i] < ar[j]) ? i++ : j++];
    while (i <= mid) tmp[k++] = ar[i++];
    while (j <= h) tmp[k++] = ar[j++];
    for (i = l; i <= h; ++i) ar[i] = tmp[i - l];
}
void msrt(int l = 0, int h = n - 1) {
	if (l < h) {
		long long mid = (l + h) >> 1;
		msrt(l, mid); msrt(mid + 1, h);
		merge(l, h, mid);
	}
}