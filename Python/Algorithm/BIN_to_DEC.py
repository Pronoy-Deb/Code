# Input is a Binary String:
# Complexity: O(n)

# Method 1: Conversion from Binary String
def str(s):
    n = 0
    for i in s:
        n = (n << 1) | (int(i) - 0)
    return n

# Method 2: Direct Method using Python's built-in functionality
s = "1011"
n = int(s, 2)  # Convert binary string to integer
print(n)  # Output: 11

# Equivalent to binary literals
a = 0b1011
print(a)  # Output: 11