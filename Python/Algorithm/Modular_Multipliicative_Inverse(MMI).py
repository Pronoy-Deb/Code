# Complexity: O(log(pow))

def mmi(base):
    ans, pow = 1, M - 2
    while pow > 0:
        if pow & 1: ans = (ans * base) % M
        base = (base * base) % M; pow >>= 1
    return ans