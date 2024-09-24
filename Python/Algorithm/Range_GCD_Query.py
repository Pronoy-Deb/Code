# Splsse Table Approach:
# Note: 0-based indexing
# Complexity: Make: O(N * log(N)) Query: O(1)

from math import log2, floor, gcd
def make(ls):
    n = len(ls); P = floor(log2(n)) + 1
    tab = [[0 for _ in range(P)] for __ in range(n)]
    for i in range(n): tab[i][0] = ls[i]
    for j in range(1, P):
        for i in range(n - (1 << j) + 1):
            tab[i][j] = gcd(tab[i][j-1], tab[i + (1 << (j-1))][j-1])
    return tab

def gc(L, R):
    j = int(log2(R - L + 1))
    return gcd(tab[L][j], tab[R - (1 << j) + 1][j])

# Example Usage:
global tab
ls = [18, 17, 23, 24, 12, 33]
tab = make(ls)
print(gc(1, 3))  # GCD of range [1, 3]

# Segment Tree Approach:
# Note: 0-based indexing
# Complexity: Make: O(N * log(min(a, b))) Query: O(log(N) * log(min(a, b)))

def make(ar):
    n = len(ar); tre = [0] * P
    P = (1 << (int(log2(n - 1)) + 1)) * 2 - 1
    def build(ss, se, si):
        if ss == se: tre[si] = ar[ss]; return ar[ss]
        mid = (ss + se) >> 1
        tre[si] = gcd(build(ss, mid, si * 2 + 1), build(mid + 1, se, si * 2 + 2))
        return tre[si]
    build(0, n - 1, 0)
    return tre

def srch(tre, n, qs, qe):
    def query(ss, se, si):
        if se < qs or ss > qe: return 0
        if ss >= qs and se <= qe: return tre[si]
        mid = (ss + se) >> 1
        return gcd(query(ss, mid, si * 2 + 1), query(mid + 1, se, si * 2 + 2))
    return query(0, n - 1, 0)

# Example Usage:
ar = [18, 17, 23, 24, 12, 33]
stre = make(ar)
n = len(ar)
print(srch(stre, n, 1, 3))  # GCD of range [1, 3]