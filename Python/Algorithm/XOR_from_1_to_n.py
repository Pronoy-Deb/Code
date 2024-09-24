# Complexity: O(1)

def xor(n):
    rem = n % 4
    if rem == 0: return n
    if rem == 1: return 1
    if rem == 2: return n + 1
    return 0