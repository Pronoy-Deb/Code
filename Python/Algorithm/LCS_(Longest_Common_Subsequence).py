# Complexity: O(n^2)
# To determine the length:
# Iterative Approach:

def lcs(s1, s2):
    l1, l2 = len(s1), len(s2)
    dp = [[0] * (l2 + 1) for _ in range(l1 + 1)]
    for i in range(1, l1 + 1):
        for j in range(1, l2 + 1):
            if s1[i - 1] == s2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1] + 1
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
    return dp[-1][-1]

# Recursive Approach (DP):

def lcs_rec(s1, s2, i, j, dp):
    if i < 0 or j < 0: return 0
    if dp[i][j] != -1: return dp[i][j]
    if s1[i] == s2[j]: dp[i][j] = 1 + lcs_rec(s1, s2, i - 1, j - 1, dp)
    else: dp[i][j] = max(lcs_rec(s1, s2, i - 1, j, dp), lcs_rec(s1, s2, i, j - 1, dp))
    return dp[i][j]

def lcs(s1, s2):
    dp = [[-1 for _ in range(len(s2))] for _ in range(len(s1))]
    return lcs_rec(s1, s2, len(s1) - 1, len(s2) - 1, dp)

# To determine the subsequence:

def lcs(s1, s2):
    l1, l2 = len(s1), len(s2)
    dp = [[0] * (l2 + 1) for _ in range(l1 + 1)]
    for i in range(1, l1 + 1):
        for j in range(1, l2 + 1):
            if s1[i - 1] == s2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1] + 1
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
    i, j = l1, l2; lcs = []
    while i > 0 and j > 0:
        if s1[i - 1] == s2[j - 1]:
            lcs.append(s1[i - 1]); i -= 1; j -= 1
        elif dp[i - 1][j] > dp[i][j - 1]: i -= 1
        else: j -= 1
    lcs.reverse(); return ''.join(lcs)

# OR,

def lcs(i, j, dp, mark, s, s1, n, m):
    if i == n or j == m: return 0
    if dp[i][j] != -1: return dp[i][j]
    if s[i] == s1[j]:
        mark[i][j] = 1
        dp[i][j] = 1 + lcs(i + 1, j + 1, dp, mark, s, s1, n, m)
    else:
        a = lcs(i, j + 1, dp, mark, s, s1, n, m)
        b = lcs(i + 1, j, dp, mark, s, s1, n, m)
        if a > b: mark[i][j] = 2
        dp[i][j] = max(a, b)
    return dp[i][j]

def show(i, j, mark, s, n, m, result):
    if i == n or j == m: return
    if mark[i][j] == 1:
        result.append(s[i])
        show(i + 1, j + 1, mark, s, n, m, result)
    elif mark[i][j] == 2: show(i, j + 1, mark, s, n, m, result)
    else: show(i + 1, j, mark, s, n, m, result)

# Example operation
s = input(); s1 = input()
n, m = len(s), len(s1)
dp = [[-1 for _ in range(m)] for _ in range(n)]
mark = [[0 for _ in range(m)] for _ in range(n)]
lcs(0, 0, dp, mark, s, s1, n, m)
result = []
show(0, 0, mark, s, n, m, result)
print("".join(result))