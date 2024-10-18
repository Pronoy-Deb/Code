// All pair summation: O(n)

long long sum(auto &ar) {
    long long tot = 0;
    for (int i = 0, n = ar.size(); i < n; ++i)
        tot += (ar[i] * (n - 1));
    return tot;
}

// All pair difference summation: O(nlogn)

long long dsum(auto &ar) {
    sort(ar.begin(), ar.end()); // if not sorted
    long long tot = 0;
    for (int i = 0, n = ar.size(); i < n; ++i)
        tot += i * ar[i] - (n - 1 - i) * ar[i];
    return tot;
}