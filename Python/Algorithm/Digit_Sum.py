# Complexity: O(log(n))

def dsum(n):
    sum = 0
    while n:
        sum += n % 10; n //= 10
    return sum

# Recursive Approach:

def dsum(n):
    if n < 10: return n
    return dsum(n // 10) + n % 10
