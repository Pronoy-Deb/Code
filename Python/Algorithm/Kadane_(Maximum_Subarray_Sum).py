# Complexity: O(n)
# Application: Used to determine the maximum subarray sum.

# To determine the summation:

def kad():
    mx , csum = ls[0], 0
    for e in ls:
        csum += e; mx = max(mx, csum); csum = max(csum, 0)
    return mx

# To determine the indices with summation:

def kad():
    msum, csum = float("-inf"), 0
    start = end = s = 0
    for i, num in enumerate(ls):
        csum += num
        if csum > msum: msum = csum; start, end = s, i
        if csum < 0: csum = 0; s = i + 1
    return start, end, msum


# Operation:
start, end, msum = kad(ls)

# Recursive Approach:

def kad(ls, left = None, right = None):
    if left is None and right is None:
        left, right = 0, len(ls)
    if left == right - 1: return ls[left]
    mid = (left + right) >> 1
    lmx = kad(ls, left, mid); rmx = kad(ls, mid, right)
    lsum = float('-inf'); rsum = float('-inf'); temp = 0
    for i in range(mid, right):
        temp += ls[i]; rsum = max(rsum, temp)
    temp = 0
    for i in range(mid - 1, left - 1, -1):
        temp += ls[i]; lsum = max(lsum, temp)
    return max(lsum + rsum, max(lmx, rmx))