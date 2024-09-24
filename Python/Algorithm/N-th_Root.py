# Complexity: O(n*log(num*(10^d))); for n-th root of number num with d decimal accuracy
# Returns: n-th root of a number with 5 decimal accuracy
# Built-in: pow(num, 1.0/n)

def mul(mid, n):
    ans = 1.0
    for _ in range(n): ans *= mid
    return ans
def nth_root(n, num):
    lo, hi = 1.0, max(1, num)
    while hi - lo > 1e-6:
        mid = (hi + lo) / 2
        if mul(mid, n) < num: lo = mid
        else: hi = mid
    return round(lo, 5)