# Complexity: O(n)

def xsum(ar):
    bit, n = 0, len(ar)
    for i in range(n): bit |= ar[i]
    return bit * (1 << (n - 1))