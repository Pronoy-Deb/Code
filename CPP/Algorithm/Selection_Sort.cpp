// Complexity: O(n^2)

long long ar[N], n;
void ssrt() {
    for (int i = 0; i < n - 1; ++i) {
        int mnin = i;
        for (int j = i + 1; j < n; ++j) {
            if (ar[j] < ar[mnin]) mnin = j;
        }
        if (i != mnin) swap(ar[i], ar[mnin]);
    }
}