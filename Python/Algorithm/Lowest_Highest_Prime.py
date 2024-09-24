# Complexity: O(n*(log(log(n))))

lh = [(0, 0) for _ in range(N)]; sv = [False] * N
def lhp():
    lh[2] = (2, 2)
    for i in range(4, N, 2):
        sv[i] = True; lh[i] = (2, 2)
    for i in range(3, N, 2):
        if not sv[i]:
            lh[i] = (i, i)
            for j in range((i << 1), N, i):
                sv[j] = True
                if not lh[j][0]: lh[j] = (i, lh[j][1])
                lh[j] = (lh[j][0], i)