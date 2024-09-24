# Complexity: O(n*log(n))

def partition(ar, lo, hi):
    pivot, i, j = ar[lo], lo, hi
    while i < j:
        while i < len(ar) and ar[i] <= pivot: i += 1
        while ar[j] > pivot: j -= 1
        if i < j: ar[i], ar[j] = ar[j], ar[i]
    ar[lo], ar[j] = ar[j], ar[lo]
    return j
def qsrt(ar, lo = 0, hi = None):
    if hi is None: hi = len(ar) - 1
    if lo < hi:
        pi = partition(ar, lo, hi)
        qsrt(ar, lo, pi - 1); qsrt(ar, pi + 1, hi)