# Complexity: O(n^2)
# Substring:

def sstr(s):
    n = len(s); sub = []
    for i in range(n):
        tmp = ""
        for j in range(i, n):
            tmp += s[j]; sub.append(tmp)
    return sub

# Subarray:

def sar(v):
    n = len(v); sub = []
    for i in range(n):
        tmp = []
        for j in range(i, n):
            tmp.append(v[j]); sub.append(tmp.copy())
    return sub