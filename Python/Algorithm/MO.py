# Complexity: O((m+n) * sqrt(n))
# Application: Used to determine the answer of query by sorting them.
# The algorithm is also known as "Square Root Decomposition".

from math import sqrt
def cmp(q, blk): return (q[0][0] // blk, q[0][1])
def mo(ls, qr):
    n, m, blk = len(ls), len(qr), int(sqrt(n)); ans = [0] * m
    qr = sorted(enumerate(qr), key=lambda x: cmp(x[1], blk))
    curL, curR, curSum = 0, 0, 0
    for idx, (L, R) in qr:
        while curL < L:
            curSum -= ls[curL]; curL += 1
        while curL > L:
            curL -= 1; curSum += ls[curL]
        while curR <= R:
            curSum += ls[curR]; curR += 1
        while curR > R + 1:
            curR -= 1; curSum -= ls[curR]
        ans[idx] = curSum
    return ans

# Example operation
n, m = map(int, input().split())
ls = [int(input()) for _ in range(n)]
qr = [tuple(map(int, input().split())) for _ in range(m)]
result = mo(ls, qr)
for res in result: print(res)