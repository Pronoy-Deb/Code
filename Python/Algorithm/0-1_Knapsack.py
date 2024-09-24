# Complexity: O(n * wt)
# wt = Total weight, p = profit, w = weight

def knap():
    dp = [0] * (wt + 1)
    for i in range(n):
        for j in range(wt, w[i] - 1, -1):
            dp[j] = max(dp[j], p[i] + dp[j - w[i]])
    return dp[wt]

# Operation:
global n, wt, w, p
n, wt = map(int, input().split())
w = list(map(int, input().split()))
p = list(map(int, input().split()))
print(knap())

# Problem: https://cses.fi/problemset/task/1158/