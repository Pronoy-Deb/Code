# Complexity: O(n * log(n))
# Use: Uses Kasai Algorithm to calculate the LCP array of a string.

def kasai(s):
    n = len(s); suf = [0] * n; lcp = [0] * n; mp = {}; sub = ""
    for i in range(n - 1, -1, -1):
        sub = s[i] + sub; mp[sub] = i
    l = -1; suf = sorted(mp.items(), key=lambda x: x[0])
    for e in suf:
        l += 1; suf[l] = e[1]
    rank = [0] * n
    for i in range(n): rank[suf[i]] = i
    k = 0
    for i in range(n):
        if rank[i] == n - 1:
            k = 0; continue
        j = suf[rank[i] + 1]
        while i + k < n and j + k < n and s[i + k] == s[j + k]: k += 1
        lcp[rank[i]] = k
        if k: k -= 1
    return lcp