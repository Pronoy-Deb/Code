// All pair summation: O(n)

int64_t sum(auto &ar) {
    int64_t tot = 0;
    for (int i = 0, n = ar.size(); i < n; ++i)
        tot += (ar[i] * (n - 1));
    return tot;
}

// All pair difference summation: O(nlogn)

int64_t dsum(auto &ar) {
    sort(ar.begin(), ar.end()); // if not sorted
    int64_t tot = 0;
    for (int i = 0, n = ar.size(); i < n; ++i)
        tot += i * ar[i] - (n - 1 - i) * ar[i];
    return tot;
}