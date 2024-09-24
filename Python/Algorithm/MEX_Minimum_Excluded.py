# Compelxity: O(n)
# For an unchanging array:

def mex(v):
    n = len(v); vis = [False] * (n + 1)
    for num in v:
        if num < n: vis[num] = True
    for i in range(n + 1):
        if not vis[i]: return i