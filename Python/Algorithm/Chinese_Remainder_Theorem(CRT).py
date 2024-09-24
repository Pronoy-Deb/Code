# Complexity: O(n*logn)
# Use: Used to determine the minimum number x such that: x % val[i] = rem[i] for all i. Here, val[i] are pairwise coprime.
# Note: If val[i] are not pairwise coprime, then: x % lcm(val[i]) = rem[i] for all i

def inv(a, m):
    if m == 1: return 0
    m0, x0, x1 = m, 0, 1
    while a > 1:
        q, t = divmod(a, m); m, a = t, m
        x0, x1 = x1 - q * x0, x0
    return x1 + m0 if x1 < 0 else x1
def minv():
    pro, res = 1, 0
    for v in val: pro *= v
    for i in range(n):
        pp = pro // val[i]; res += rem[i] * inv(pp, val[i]) * pp
    return res % pro

# Operation:
global n, val, rem
n = int(input())
val = list(map(int, input().split()))
rem = list(map(int, input().split()))
print(minv())