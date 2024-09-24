# In-built Approach:
# Complexity: O(log(min(a, b)))
# Built-in Approach:

from math import gcd
def cprime(a, b):
    return gcd(a, b) == 1

# Pre-computation Approach:
# Complexity: O(N^2 * log(N))
# cp[a][b]==false ? co-prime

N = 1005
cp = [[False] * N for _ in range(N)]
def cprime():
    for i in range(2, N):
        for j in range(i, N, i):
            cp[i][j] = True
            for k in range(j + i, N, i):
                cp[j][k] = cp[k][j] = True