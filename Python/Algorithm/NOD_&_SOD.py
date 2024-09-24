# Complexity: O(n * log(n))
# Application: Used to determine the Number of Divisors and Sum of Divisors from number 1 to n.

def nod(n):
    nd = [0] * (n + 1)
    for i in range(1, n + 1):
        for j in range(i, n + 1, i): nd[j] += 1
    return nd

def sod(n):
    sd = [0] * (n + 1)
    for i in range(1, n + 1):
        for j in range(i, n + 1, i): sd[j] += i
    return sd