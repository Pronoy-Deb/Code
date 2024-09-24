# Complexity: O(log(n))
# Returns:
# 1. The index of the element if it is present once
# 2. The lowest index of the element if it is present more than once
# 3. The index of the higher element if it is not present & higher one is present
# 4. "-1" if neither the element nor the higher element is present
# Works only on monotonic (strictly increasing or decreasing) vectors

def lb(v, n):
    lo, hi = 0, len(v) - 1
    while hi - lo > 1:
        mid = (hi + lo) >> 1
        if v[mid] < n: lo = mid + 1
        else: hi = mid
    if v[lo] >= n: return lo
    if v[hi] >= n: return hi
    return -1