# Complexity: O(n)
# Application: Used to determine the number of palindromes in a string.

def man(s):
    t = "$#" + "#".join(s) + "#^"; n = len(t); p = [0] * n; cn = rt = 0
    for i in range(1, n - 1):
        mr = (cn << 1) - i
        if i < rt: p[i] = min(rt - i, p[mr])
        while t[i + (1 + p[i])] == t[i - (1 + p[i])]: p[i] += 1
        if i + p[i] > rt: cn = i; rt = i + p[i]
    p = [x for x in p[1:-1] if x > 0]; return p