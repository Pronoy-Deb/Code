# Complexity: O(log(n))
# Returns: (0/1) whether the element is present or not
# -> Works only on monotonic (sorted) arrays
# Built-in:

from bisect import bisect_left
def bs(ls, val):
    ind = bisect_left(ls, val)
    return ind != len(ls) and ls[ind] == val

# User-defined:

def bs(val):
    lo, hi = 0, n - 1
    while lo <= hi:
        mid = (hi + lo) >> 1
        if ls[mid] == val: return True
        if ls[mid] < val: lo = mid + 1
        else: hi = mid - 1
    return False

# OR,

def bs(val):
    lo, hi = 0, n - 1
    while lo < hi:
        mid = (hi + lo + 1) >> 1
        if ls[mid] < val: lo = mid + 1
        else: hi = mid
    return ls[lo] == val