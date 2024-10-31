# Complexity: O(log(pow))
# Iterative Approach:

def bex(base, pow = M - 2):
    base %= M; ans = 1
    while pow:
        if pow & 1: ans = (ans * base) % M
        base = (base * base) % M; pow >>= 1
    return ans

# Recursive Approach

def bex(base, pow = M - 2):
    if not pow: yield 1
    call = yield bex(base, pow >> 1)
    if pow & 1: yield (base * (call * call) % M) % M
    yield (call * call) % M

# M = 10**18 + 7

def bmul(a, b):
    ans = 0
    while b:
        if b & 1: ans = (ans + a) % M
        a = (a + a) % M; b >>= 1
    return ans

def bex_long(base, pow):
    ans = 1
    while pow:
        if pow & 1: ans = bmul(ans, base)
        base = bmul(base, base); pow >>= 1
    return ans

# Purpose: To Calculate a ^ b ^ c or, pow(a, pow(b, c)):

def bex(base, pow, m):
    ans = 1
    while pow:
        if pow & 1: ans = (ans * base) % m
        base = (base * base) % m; pow >>= 1
    return ans

def bex3(a, b, c):
    return bex(a, bex(b, c, M - 1), M)

# Example usage
print(bex3(50, 64, 32)) # a ^ b ^ c example