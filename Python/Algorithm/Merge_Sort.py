# Complexity: O(n*log(n))

def merge(arr, lo, hi, mid):
    tmp = []; i, j = lo, mid + 1
    while i <= mid and j <= hi:
        if arr[i] < arr[j]:
            tmp.append(arr[i]); i += 1
        else:
            tmp.append(arr[j]); j += 1
    while i <= mid:
        tmp.append(arr[i]); i += 1
    while j <= hi:
        tmp.append(arr[j]); j += 1
    for i in range(lo, hi + 1):
        arr[i] = tmp[i - lo]
        
def msrt(arr, lo=0, hi=None):
    if hi is None: hi = len(arr) - 1
    if lo < hi:
        mid = (lo + hi) >> 1
        msrt(arr, lo, mid); msrt(arr, mid + 1, hi)
        merge(arr, lo, hi, mid)