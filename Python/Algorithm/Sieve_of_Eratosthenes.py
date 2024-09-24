# Index: 1-based, Note: if (!sv[n]) --> Prime
# Comlexity: O(n)

sv = [False] * N; spf = [0] * N; prime = []
def siv():
    sv[0] = sv[1] = True
    for i in range(2, N):
        if not sv[i]: prime.append(i); spf[i] = i
        sz = len(prime)
        for j in range(sz):
            if i * prime[j] < N and prime[j] <= spf[i]:
                sv[i * prime[j]] = True
                spf[i * prime[j]] = prime[j]
            else: break

# Comlexity: O(n * (log(log(n))))

sv = [False] * N
def siv():
    sv[0] = sv[1] = True
    for i in range(4, N, 2): sv[i] = True
    i = 3
    while i * i <= N:
        if not sv[i]:
            for j in range(i * i, N, i << 1): sv[j] = True
        i += 2

# Alternate (Slower):

sv = [False] * N
def siv():
    sv[0] = sv[1] = True
    for i in range(2, N):
        if not sv[i]:
            for j in range(i << 1, N, i):
                sv[j] = True

# Bitwise Sieve:
# Note: if sv(n): --> Prime

sv = [0] * ((N//32) + 2)
def sv(x): return not sv[x >> 5] & (1 << (x & 31))
def siv():
    for i in range(4, N, 2): sv[i >> 5] |= (1 << (i & 31))
    i = 3
    while i * i <= N:
        if sv(i):
            for j in range(i * i, N, i << 1):
                sv[j >> 5] |= (1 << (j & 31))


Segmented sv:

