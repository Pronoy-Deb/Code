# Complexity: O(n * 2^n)
# Application: Determine the possibility of having any subset sum equal to given value
# Subset Sum Generation:

def ssum(ar):
    n, sz = len(ar), 1 << n; res = [0] * sz
    for i in range(sz):
        sum = 0
        for j in range(n):
            if i & (1 << j): sum += ar[j]
        res[i] = sum
    return res

# Problem: https://cses.fi/problemset/task/1623

def psbl(ar):
    tot = sum(ar)
    if tot & 1: return False
    ssum, n = tot >> 1, len(ar)
    dp = [[-1 for _ in range(ssum + 1)] for __ in range(n)]
    def is_psbl(ind, csum):
        if not csum: return True
        if ind < 0 or csum < 0: return False
        if dp[ind][csum] != -1: return dp[ind][csum]
        without = is_psbl(ind - 1, csum)
        withc = is_psbl(ind - 1, csum - ar[ind])
        dp[ind][csum] = without or withc
        return dp[ind][csum]
    return is_psbl(n - 1, ssum)

# Problem: https://leetcode.com/problems/partition-equal-subset-sum/