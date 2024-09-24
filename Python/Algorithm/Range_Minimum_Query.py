# Segment Tree approach:
# Complexity: Make: O(n) Query: O(log(n))
# For Static List:

def make():
    tre = [0] * (n << 1)
    for i in range(n): tre[n + i] = ls[i]
    for i in range(n - 1, 0, -1):
        tre[i] = min(tre[i << 1], tre[i << 1 | 1])

def mini(l, r):
    res = float('inf'); l += n; r += n
    while l < r:
        if l & 1:
            res = min(res, tre[l]); l += 1
        if r & 1:
            r -= 1; res = min(res, tre[r])
        l >>= 1; r >>= 1
    return res

# Operation:
global ls, tre, n
n = int(input())
ls = list(map(int, input().split()))

# For Dynamic lsray:

def make():
    tre = [0] * (n << 1)
    for i in range(n): tre[n + i] = ls[i]
    for i in range(n - 1, 0, -1):
        tre[i] = min(tre[i << 1], tre[i << 1 | 1])

def up(ind, val):
    ind += n; tre[ind] = val
    while ind > 1:
        tre[ind >> 1] = min(tre[ind], tre[ind ^ 1]); ind >>= 1

def mini(l, r):
    res = float('inf'); l += n; r += n
    while l < r:
        if l & 1:
            res = min(res, tre[l]); l += 1
        if r & 1:
            r -= 1; res = min(res, tre[r])
        l >>= 1; r >>= 1
    return res

# Operation:
global ls, tre, n
n = int(input())
ls = list(map(int, input().split()))

# Sparse Table Approach (For Static lsray):
# Note: 0-based indexing
# Complexity: Make: O(n * log(n)) Query: O(1)

from math import log2, floor

def make():
    P = floor(log2(n)) + 1
    tab = [[float('inf') for _ in range(P)] for __ in range(n)]
    for i in range(n): tab[i][0] = ls[i]
    for j in range(1, P):
        for i in range(n):
            if i + (1 << j) - 1 < n:
                tab[i][j] = min(tab[i][j - 1], tab[i + (1 << (j - 1))][j - 1])

def mini(L, R):
    j = int(log2(R - L + 1))
    return min(tab[L][j], tab[R - (1 << j) + 1][j])
    
# Operation:
global ls, tre, n
n = int(input())
ls = list(map(int, input().split()))
