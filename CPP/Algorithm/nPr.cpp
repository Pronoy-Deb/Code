// Complexity: O(r)

long long npr(auto n, auto r) {
    long long res = 1;
    for (int i = n - r + 1; i <= n; ++i) res *= i;
    return res;
}