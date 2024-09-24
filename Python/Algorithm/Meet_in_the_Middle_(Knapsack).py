# Complexity: O(2^(n/2) * log(2^(n/2)))

from bisect import bisect_left
from bisect import bisect_right
def ssum(ls, s, e):
    n = 1 << (e - s); res = []
    for i in range(n):
        sum = 0
        for j in range(e - s):
            if i & (1<<j): sum += ls[j+s]
        res.append(sum)
    return res

def cnt(ls, tot):
    sz = len(ls)
    l = ssum(ls, 0, sz >> 1); r = ssum(ls, sz >> 1, sz)
    r.sort(); c, n = 0, len(l)
    for i in range(n):
        if tot >= l[i]:
            lo = bisect_left(r, tot-l[i]); hi = bisect_right(r, tot-l[i])
            c += hi - lo
    return c

# Problems:
# https://cses.fi/problemset/task/1628/
# https://atcoder.jp/contests/abc184/tasks/abc184_f