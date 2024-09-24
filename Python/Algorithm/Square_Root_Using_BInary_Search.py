# Complexity: O(log(n))

def rt(n):
    lo, hi = 1, n
    while hi - lo > 1e-6:
        mid = (lo + hi) / 2
        if mid * mid < n: lo = mid
        else: hi = mid
    return lo