// Complexity: O(n)

long long sum() {
    long long tot = 0;
    for (int i = 0; i < n; ++i)
        tot += (ar[i] * (n - 1));
    return tot;
}