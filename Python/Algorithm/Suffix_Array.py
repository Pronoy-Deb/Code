# Complexity: O(n*log(n))
# Use: Sorts the suffixes of a string in lexicographical order and stores the starting index of each suffix.

def sa(s):
    n = len(s); suf = [(s[i:], i) for i in range(n)]
    ssuf = sorted(suf, key=lambda x: x[0])
    suf = [index for _, index in ssuf]
    return suf