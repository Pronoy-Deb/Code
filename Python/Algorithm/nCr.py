# Formula: 1. nCr = n! / (r! * (n-r)!)
# 2. nCr + (n+1)Cr + (n+2)Cr + ... + (n+m)Cr = (n+m+1)C(r+1)
# 3. nC0 + nC1 + nC2 + ... + nCn = 2^n
# Complexity: O(r)

def ncr(n, r):
    if r > n: return 0
    r = min(r, n - r); num = den = 1
    for i in range(r):
        num *= (n - i); den *= (i + 1)
    return num // den

# Recursive Approach:
# Complexity: O(2^n)

def ncr(n, r):
    if r == 0 or n == r: return 1
    if r == 1: return n
    return (ncr(n - 1, r - 1) + ncr(n - 1, r)) % M

# Modular Multiplicative Inverse(MMI) Appraoch:
# Complexity: O(n)
# To calculate modular multiplicative inverse: 1/n = bex(n, M-2)

def mmi(base, exp):
    res = 1
    while exp:
        if exp & 1: res = (res * base) % M
        base = (base * base) % M; exp >>= 1
    return res
def ncr(n, r):
    fac = [1] * (n + 1)
    for i in range(2, n + 1):
        fac[i] = fac[i - 1] * i % M
    return (fac[n] * mmi(fac[r], M - 2) * mmi(fac[n - r], M - 2)) % M

# Pre-calculation of nCr:
# Complexity: O(N)

fac, inv, finv = [1] * N, [1] * N, [1] * N
def pre():
    for i in range(2, N):
        fac[i] = fac[i - 1] * i % M
        inv[i] = M - M // i * inv[M % i] % M
        finv[i] = finv[i - 1] * inv[i] % M

def ncr(n, r):
    if r > n: return 0
    return (fac[n] * finv[r] * finv[n - r]) % M