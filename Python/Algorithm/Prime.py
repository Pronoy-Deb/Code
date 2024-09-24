# Complexity: O(sqrt(n))

def prime(n):
    if n in (2, 3): return True
    if n < 2 or n % 2 == 0 or n % 3 == 0: return False
    i = 5
    while i * i <= n:
        if n % i == 0 or n % (i + 2) == 0: return False
        i += 6
    return True

# OR,

def prime(n):
    if n < 2: return False
    if n == 2: return True
    if ~n & 1: return False
    i = 3
    while i * i <= n:
        if n % i == 0: return False
        i += 2
    return True