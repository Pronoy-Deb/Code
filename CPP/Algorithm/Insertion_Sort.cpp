// Complexity: O(n^2)

void isrt() {
    for (int i = 1, j = i; i < n; ++i, j = i) {
        while (j > 0 && ar[j] < ar[--j]) swap(ar[j], ar[j + 1]);
    }
}