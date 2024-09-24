# Complexity: O(n)
# Note: Inspired from Manacher algorithm

def man(s):
    t = "$#" + "#".join(s) + "#^"
    n = len(t); p = [0] * n; c = r = l = ind = 0
    for i in range(1, n-1):
        mirr = (c << 1) - i
        if i < r: p[i] = min(r - i, p[mirr])
        while t[i + (1 + p[i])] == t[i - (1 + p[i])]: p[i] += 1
        if i + p[i] > r: c = i; r = i + p[i]
        if p[i] > l: l = p[i]; ind = i
    start = (ind - l) >> 1
    return s[start : start + l]

# Problem: https://cses.fi/problemset/task/1111