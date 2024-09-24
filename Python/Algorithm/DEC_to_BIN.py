# Complexity: O(n)
# Returns the value as a string:

def bin(n):
    if n == 0: return "0"
    s = ""
    while n: s += str(n & 1); n >>= 1
    return s[::-1]

# Returns the value as an integer:

def bin(n):
    if n == 0: return 0
    s = ""
    while n: s += str(n & 1); n >>= 1
    ans = 0
    for ch in s[::-1]: ans = ans * 10 + int(ch == '1')
    return ans

# Or,

def bin(n):
    ans = 0
    for i in range(18, -1, -1):
        ans = ans * 10 + ((n >> i) & 1)
    return ans