# Complexity: O(log(n))
# Use: Solves the equation: ax + by = gcd(a, b) and determines gcd(a, b), x and y
# Note: The equation ax + by = gcd(a, b) has a solution if and only if gcd(a, b) divides c (c is the gcd of a and b) and the equation is known as linear diophantine equation

def ee(a, b):
    if a == 0: return b, 0, 1
    gcd, x1, y1 = ee(b % a, a)
    x = y1 - (b // a) * x1; y = x1
    return gcd, x, y

# Example usage
a, b = map(int, input().split())
gcd, x, y = ee(a, b)
print("GCD:", gcd)
print("x:", x, "y:", y)