// Complexity: O(n^2)

int64_t aa[N], n;
void ssrt() {
    for (int i = 0; i < n - 1; ++i) {
        int mnin = i;
        for (int j = i + 1; j < n; ++j) {
            if (aa[j] < aa[mnin]) mnin = j;
        }
        if (i != mnin) swap(aa[i], aa[mnin]);
    }
}