// Complexity: O(r)

int64_t npr(int n, int r) {
    int64_t res = 1;
    for (int i = n - r + 1; i <= n; ++i) res *= i;
    return res;
}