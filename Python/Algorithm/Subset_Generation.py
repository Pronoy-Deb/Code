# Bitmasking Approach:
# Complexity: O(2^n)

def sset(input):
    n = len(input); res = []
    for i in range(1 << n):
        sub = []
        for j in range(n):
            if i & (1 << j): sub.append(input[j])
        res.append(sub)
    return res

# Recursive Approach:
# Complexity: O(2^n)

def sset(input, sub = [], ind = 0):
    if ind == len(input): return [sub.copy()]
    res = sset(input, sub, ind + 1)
    sub.append(input[ind])
    res += sset(input, sub, ind + 1)
    sub.pop(); return res