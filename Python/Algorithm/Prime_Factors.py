# General Approach:
# Complexity: O(sqrt(n))
# To store all the prime facors:

def pfac(n):
    fac = []; i = 3
    while ~n & 1: fac.append(2); n >>= 1
    while i * i <= n:
        while n % i == 0:
            fac.append(i); n //= i
        i += 2
    if n > 2: fac.append(n)
    return fac

# To store the count of prime fac:

def pfac(n):
    cnt = {}
    while ~n & 1: cnt[2] = cnt.get(2, 0) + 1; n >>= 1
    i = 3
    while i * i <= n:
        while n % i == 0:
            cnt[i] = cnt.get(i, 0) + 1; n //= i
        i += 2
    if n > 2: cnt[n] = cnt.get(n, 0) + 1
    return cnt

# sv Approach:
# Complexity: O(n * (log(log(n))) + log(n))

low = [0] * N; sv = [False] * N
def lp():
    low[2] = 2
    for i in range(4, N, 2):
        sv[i] = True; low[i] = 2
    for i in range(3, N, 2):
        if not sv[i]:
            low[i] = i
            for j in range(i * i, N, i << 1):
                sv[j] = True
                if not low[j]: low[j] = i

def pfac(n):
    fac = []
    while n > 1:
        p = low[n]
        while n % p == 0:
            n //= p; fac.append(p)
    return fac

lp()  # Initialize the sieve once

# To store the count of prime numbers:
# Complexity: O(N * (log(log(N))) + log(n))

low = [0] * N; sv = [False] * N
def lp():
    low[2] = 2
    for i in range(4, N, 2):
        sv[i] = True; low[i] = 2
    for i in range(3, N, 2):
        if not sv[i]:
            low[i] = i
            for j in range(i * i, N, i << 1):
                sv[j] = True
                if not low[j]: low[j] = i

def pfac(n):
    cnt = {}
    while n > 1:
        p = low[n]
        while n % p == 0:
            n //= p; cnt[p] = cnt.get(p, 0) + 1
    return cnt