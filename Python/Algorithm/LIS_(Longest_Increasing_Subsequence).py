# Note: Gives result of STRICTLY incresing seq
# For longest non-decreasing seq, replace 'lower_bound' with 'upper_bound' and for longest decreasing seq, replace ar[i]*=-1;
# To determine the length:
# Iterative Approach:
# Complexity: O(n * log(n))

def lis(arr):
    from bisect import bisect_left
    ans = [arr[0]]
    for i in range(1, len(arr)):
        if arr[i] > ans[-1]: ans.append(arr[i])
        else:
            low = bisect_left(ans, arr[i])
            ans[low] = arr[i]
    return len(ans)

# Complexity: O(n ^ 2)
# DP Approach:

def lis(v):
    dp = [1] * len(v)
    for i in range(len(v)):
        for j in range(i):
            if v[j] < v[i]: dp[i] = max(dp[i], dp[j] + 1)
    return max(dp)

# Recursive Approach:

def rec(i, v, dp):
    if dp[i] != -1: return dp[i]
    ans = 1
    for j in range(i):
        if v[i] > v[j]: ans = max(ans, rec(j, v, dp) + 1)
    dp[i] = ans; return ans

def lis(v):
    n, ans = len(v), 0; dp = [-1] * n
    for i in range(n):
        ans = max(ans, rec(i, v, dp))
    return ans

# To determine the sequence:

def lis(arr):
    dp = [1] * len(arr); prev = [-1] * len(arr)
    for i in range(len(arr)):
        for j in range(i):
            if arr[j] < arr[i] and dp[i] < dp[j] + 1:
                dp[i] = dp[j] + 1; prev[i] = j
    idx = dp.index(max(dp)); seq = []
    while idx != -1:
        seq.append(arr[idx]); idx = prev[idx]
    seq.reverse(); return seq