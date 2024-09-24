# Note: Number of divisors of a number is equal to the product of (a + 1) where a is the power of each prime factor of that number.
# Naive Approach:
# Complexity: O(sqrt(n))

def div(n):
    divs = []; lim = int(n**0.5) + 1
    for i in range(1, lim):
        if n % i == 0:
            divs.append(i)
            if i != n // i: divs.append(n // i)
    return divs

# For summation of the divisors:

def sdiv(n):
    res = 1; i = 2
    while i * i <= n:
        csum, cterm = 1, 1
        while n % i == 0:
            n //= i; cterm *= i; csum += cterm
        res *= csum; i += 1
    if n > 1: res *= (1 + n)
    return res
