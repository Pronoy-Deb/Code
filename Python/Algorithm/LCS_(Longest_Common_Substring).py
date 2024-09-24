# Complexity: O(m * n)
# To determine the length:

def lcs(s1, s2):
    m, n = len(s1), len(s2); res = 0
    dp = [[0] * (m + 1) for _ in range(n + 1)]
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            if s1[j - 1] == s2[i - 1]:
                dp[i][j] = dp[i - 1][j - 1] + 1
                res = max(res, dp[i][j])
    return res

# To determine the substring:

def lcs(s1, s2):
    m, n, res, end, cur = len(s1), len(s2), 0, 0, 0
    dp = [[0 for _ in range(n + 1)] for _ in range(2)]
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if s1[i - 1] == s2[j - 1]:
                dp[cur][j] = dp[1 - cur][j - 1] + 1
                if dp[cur][j] > res:
                    res = dp[cur][j]; end = i - 1
        cur ^= 1
    return "" if not res else s1[end - res + 1: end + 1]

# OR,

def lcs(s1, s2):
    l1, l2 = len(s1), len(s2)
    dp1 = [0] * (l2 + 1); dp2 = [0] * (l2 + 1)
    ans, end = 0, 0
    for i in range(1, l1 + 1):
        for j in range(1, l2 + 1):
            if s1[i-1] == s2[j-1]:
                dp1[j] = dp2[j-1] + 1
                if dp1[j] > ans:
                    ans = dp1[j]; end = i
            else: dp1[j] = 0
        dp2 = dp1[:]
    start = end - ans; return s1[start:end]