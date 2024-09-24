# Complexity: O(r)

def npr(n, r):
    res = 1
    for i in range(n-r+1, n+1): res *= i
    return res