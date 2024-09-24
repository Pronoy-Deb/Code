# Complexity: O(log(min(a, b)))
# Built-in: math.lcm(a, b)
# GCD Approach:

def gcd(a, b):
    while b: a, b = b, a % b
    return a
def lcm(a, b):
    return (a * b) // gcd(a, b)

# Pre-computation Approach:
# Complexity: O(n^2 * log(n))

N = 1001
gd = [[0 for _ in range(N)] for _ in range(N)]

def pre():
    for i in range(2, N):
        for j in range(i, N, i):
            gd[i][j] = i
            for k in range(j + i, N, i):
                gd[j][k] = gd[k][j] = i
def lcm(a, b):
    return (a * b) // (gd[a][b] if gd[a][b] else 1)

# Operation:
pre()
print(lcm(2, 10))