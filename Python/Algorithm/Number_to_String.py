# Complexity: O(d)  // d = Number of digits in the number
# Built-in: str(n);

def string(n):
    if not n: return "0"
    s = ""
    while n:
        s += str(n % 10); n //= 10
    return s[::-1]