# Complexity: O(n*log(n))
# Coprime: __gcd(a, b) == 1
# Note: phi[i] tells how many numbers from 1 to n-1 are coprime with n.

# Number of co-primes of a number n:
#     n * (1 - 1/a) * (1 - 1/b) * (1 - 1/c) * .......; a,b,c = Prime factors of n
    # Ex: Prime factors of 5 -> 5 & 6 -> 2, 3

def etf():
    phi = [0] * N; sv = [False] * N
    for i in range(2, N, 2): phi[i] = i // 2
    for i in range(3, N, 2):
        if not sv[i]:
            for j in range(i, N, i):
                sv[j] = True
                if phi[j] == 0: phi[j] = j
                phi[j] = (phi[j] * (i - 1)) // i
    return phi