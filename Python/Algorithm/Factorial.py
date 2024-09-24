# Complexity: O(n)

def fac(n):
    res = 1
    for i in range(2, n + 1): res *= i
    return res

def fac(n):
    res = 1
    for i in range(2, n + 1): res = (res * i) % M
    return res

# Recursive Approach:

def fac(n): return 1 if n == 0 else n * fac(n - 1)

# Storing the fac values:

fac = [1] * N
for i in range(2, N): fac[i] = fac[i - 1] * i % M

# String Approach: O(n^2)

def fac(n):
    s = "1"
    for i in range(2, n + 1):
        car = 0
        s = [int(digit) for digit in s]
        for j in range(len(s)):
            a = s[j] * i + car
            s[j] = a % 10; car = a // 10
        while car: s.append(car % 10); car //= 10
        s = ''.join(map(str, s[::-1]))
    return s

# Vector Approach:

def fac(n):
    v = [1]
    for i in range(2, n + 1):
        car = 0
        for j in range(len(v)):
            a = v[j] * i + car
            v[j] = a % 10; car = a // 10
        while car: v.append(car % 10); car //= 10
        v.reverse()
    return v