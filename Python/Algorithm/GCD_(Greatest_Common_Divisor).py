# Complexity: O(log(min(a, b)))
# Note: The algorithm is also called Euclidean Algorithm
# Built-in: __gcd(a, b);
# Iterative Approach:

def gcd(a, b):
    while b: a, b = b, a % b
    return a

# Recursive Approach
def gcd(a, b):
    if not b: return a
    return gcd(b, a % b)

# Test the functions
a, b = 48, 18
print("Iterative GCD:", gcd(a, b))
print("Recursive GCD:", gcd(a, b))

def gcd(a, b):
    if not a or a == b: return b
    if not b: return a
    if not a & 1:  # a is even
        if b & 1: return gcd(a >> 1, b)
        else: return gcd(a >> 1, b >> 1) << 1
    if not b & 1: return gcd(a, b >> 1)
    if a > b: return gcd((a - b) >> 1, b)
    return gcd((b - a) >> 1, a)

# Example usage
a, b = 48, 18
print("Optimized Recursive GCD:", gcd(a, b))

# Pre-computation in a 2-D array:
# Complexity: O(n^2 * log(n))

def pre():
    gd = [[0] * N for _ in range(N)]
    for i in range(2, N):
        for j in range(i, N, i):
            gd[i][j] = i
            for k in range(j + i, N, i):
                gd[j][k] = gd[k][j] = i
    return gd

# Precompute GCDs
gcd_table = pre()

# Example usage
a, b = 48, 18
print("Precomputed GCD:", gcd_table[a][b] if gcd_table[a][b] else 1)