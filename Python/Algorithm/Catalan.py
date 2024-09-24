# Complexity: O(n)
# For n catalan numbers using pre-calculation:

cat = []
def cata():
    cat.append(1)
    for i in range(1, 20):
        cat.append(cat[i - 1] * (4 * i - 2) // (i + 1))

# For n-th catalan number:

def cat(n):
    res = 1
    for i in range(n):
        res *= ((n << 1) - i); res //= (i + 1)
    return res // (n + 1)