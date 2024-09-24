# Complexity: O(N * log(max(ar[i]) * log(N))

from math import log2
from typing import List

def gcd(a: int, b: int) -> int:
    while b: a, b = b, a % b
    return a

def make(ar: List[int], n: int) -> List[List[int]]:
    log_n = int(log2(n)) + 1
    tab = [[0] * log_n for _ in range(n)]
    for i in range(n): tab[i][0] = ar[i]
    for j in range(1, log_n):
        for i in range(n - (1 << j) + 1):
            tab[i][j] = gcd(tab[i][j-1], tab[i + (1 << (j-1))][j-1])
    return tab

def gc(tab: List[List[int]], L: int, R: int) -> int:
    j = int(log2(R - L + 1))
    return gcd(tab[L][j], tab[R - (1 << j) + 1][j])

def sum(ar: List[int], n: int) -> int:
    tab = make(ar, n); ans = 0
    for i in range(n):
        ep, pep, val = i, i, ar[i]
        while ep < n:
            lo, hi = pep, n - 1
            while hi > lo:
                mid = (hi + lo + 1) // 2
                if gc(tab, i, mid) == val: lo = mid
                else: hi = mid - 1
            ep = lo + 1; ans += ((ep - pep) * val); pep = ep
            if ep < n: val = gcd(val, ar[ep])
    return ans

# Example usage
n = 4
ar = [4, 6, 2, 8]
print(sum(ar, n))