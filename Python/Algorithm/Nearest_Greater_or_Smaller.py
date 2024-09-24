# Complexity: O(n)
# Next Greater Element:

def nge(ls):
    n = len(ls); ng = [-1] * n; sk = []
    for i in range(n):
        while sk and ls[i] > ls[sk[-1]]:
            ng[sk.pop()] = i
        sk.append(i)
    return ng

# Previous Smaller Element:

def pse(ls):
    n = len(ls); ps = [-1] * n; sk = []
    for i in range(n-1, -1, -1):
        while sk and ls[i] < ls[sk[-1]]:
            ps[sk.pop()] = i
        sk.append(i)
    return ps