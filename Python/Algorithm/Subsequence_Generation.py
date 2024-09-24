# Note: Number of ssequences of a string : 2^n - 1
# Bitmasking Approach:
# Complexity: O(2^n)  // n = input.size()

def sseq(input):
    n = len(input); res = []
    for i in range(1, 1 << n):
        sub = ""
        for j in range(n):
            if i & (1 << j): sub += input[j]
        res.append(sub)
    return res

# Recursive Approach:
# Complexity: O(2^n)  // n = input.size()

def sseq(input, ind = 0, sub = ""):
    if ind == len(input):
        if sub: return [sub]
        return []
    res = sseq(input, ind + 1, sub)
    res += sseq(input, ind + 1, sub + input[ind])
    return res