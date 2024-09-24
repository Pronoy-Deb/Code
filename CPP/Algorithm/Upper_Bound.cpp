// Complexity: O(log(n))
// Returns:
// 1. The index of the higher element if higher element is present once
// 2. The lowest index of the higher element if element is present more than once
// 3. The index of the higher element if it is not present & higher one is present
// 4. "-1" if neither the element nor the higher element is present
// Works only on monotonic (strictly increasing or decreasing) vectors
// Alternate: upper_bound(v.begin(), v.end(), n) - v.begin();

auto ub(auto &v, auto n) {
    int lo = 0, hi = v.size() - 1;
    while (hi - lo > 1) {
        int mid = (hi + lo) >> 1;
        if (v[mid] <= n) lo = mid + 1;
        else hi = mid;
    }
    if (v[lo] > n) return lo;
    if (v[hi] > n) return hi;
    return -1;
}