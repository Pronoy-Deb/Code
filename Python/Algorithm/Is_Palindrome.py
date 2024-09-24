# Complexity: O(len(s))

def pal(s):
    for i in range(len(s) // 2):
        if s[i] != s[-(i + 1)]: return False
    return True

# OR,

def pal(s):
    return all(s[i] == s[~i] for i in range(len(s)//2))

# Hashing Approach:

def pal(s, base = 29):
    sz = len(s); tmp = ord(s[0]) - ord('a') + 1
    temp = ord(s[sz - 1]) - ord('a') + 1; p = 1
    for i in range(1, sz):
        p = (p * base) % M
        tmp = (tmp + (ord(s[i]) - ord('a') + 1) * p) % M
    p = 1
    for i in range(sz - 2, -1, -1):
        p = (p * base) % M
        temp = (temp + (ord(s[i]) - ord('a') + 1) * p) % M
    return tmp == temp