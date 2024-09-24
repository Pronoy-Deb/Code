# Complexity: O(log(min(a,b)))
# In-built Approach: math.gcd(a, b)

# Iterative Approach:

def gcd(a, b):
    while b:
        tmp = a; a = b; b = tmp % b
    return a

def lcm(a, b): return (a // gcd(a, b)) * b

# Recursive Approach:

def gcd(a, b):
    if not b: return a
    return gcd(b, a % b)

# OR, for the alternative approach with bitwise operations

def gcd(a, b):
    if a == b or not b: return a
    if not a: return b
    if not a & 1:
        if b & 1: return gcd(a >> 1, b)
        return gcd(a >> 1, b >> 1) << 1
    if not b & 1: return gcd(a, b >> 1)
    if a > b: return gcd((a - b) >> 1, b)
    return gcd((b - a) >> 1, a)

# LCM:

def lcm(a, b):
    if a < b: a, b = b, a
    tmp = a
    while tmp % b: tmp += a
    return tmp