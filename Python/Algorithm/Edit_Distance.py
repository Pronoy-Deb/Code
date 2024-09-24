# Complexity: O(N ^ 2)
# Application: Used to determine the minimum number of operations needed to make two strings equal.

def ed(s, s1):
    m, n = len(s), len(s1)
    dp = [[0] * (n + 1) for _ in range(m + 1)]
    for i in range(m + 1):
        for j in range(n + 1):
            if not i: dp[i][j] = j
            elif not j: dp[i][j] = i
            elif s[i - 1] == s1[j - 1]: dp[i][j] = dp[i - 1][j - 1]
            else: dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1])
    return dp[m][n]

# Example usage:
s = input("Enter first string: ")
s1 = input("Enter second string: ")
print("Edit distance:", ed(s, s1))

# Problem: https://cses.fi/problemset/task/1639