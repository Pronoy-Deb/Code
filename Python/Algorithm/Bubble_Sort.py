# Complexity: O(n^2)
# Iterative approach:

def bsrt():
    for i in range(n-1):
        ok = True
        for j in range(n-i-1):
            if ls[j] > ls[j+1]:
                ls[j], ls[j+1] = ls[j+1], ls[j]; ok = False
        if ok: break

# Recursive approach

def bsrt(a = None):
    if a is None: a = n
    if a <= 1: return
    for i in range(a-1):
        if ls[i] > ls[i+1]:
            ls[i], ls[i+1] = ls[i+1], ls[i]  # Swapping elements
    bsrt(a-1)