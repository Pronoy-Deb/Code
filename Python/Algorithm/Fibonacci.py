# Using Matrix Exponentiation to determine n-th fibonacci number:
# Complexity: O(logn)

def multiply(a, b):
    mul = [[0, 0, 0] for _ in range(3)]
    for i in range(3):
        for j in range(3):
            for k in range(3):
                mul[i][j] += a[i][k] * b[k][j]
    for i in range(3):
        for j in range(3): a[i][j] = mul[i][j]

def power(F, n):
    M = [[1, 1, 0], [1, 0, 0], [0, 1, 0]]
    if n == 1: return F[0][0] + F[0][1]
    power(F, n // 2); multiply(F, F)
    if n % 2 != 0: multiply(F, M)
    return F[0][0] + F[0][1]

def fib(n):
    F = [[1, 1, 0], [1, 0, 0], [0, 1, 0]]
    if n == 0: return 0
    if n <= 2: return 1
    return power(F, n - 2)

# Usage
n = int(input())
print(fib(n))

# Using DP: Complexity: O(n)
# Bottom Up Approach:

def fib(n):
    dp = [0] * (n + 1); dp[1] = 1
    for i in range(2, n + 1):
        dp[i] = dp[i - 1] + dp[i - 2]
    return dp[n]

# Usage
n = int(input())
print(fib(n))

# Top Down Approach:

def fib(n, dp):
    if n == 0 or n == 1: return n
    if dp[n] != -1: return dp[n]
    dp[n] = fib(n - 1, dp) + fib(n - 2, dp)
    return dp[n]

# Usage
n = int(input())
dp = [-1] * (n + 1)
print(fib(n, dp))