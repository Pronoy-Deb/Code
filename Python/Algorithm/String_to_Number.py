# Complexity: O(l)  // l = Length of the string
# Built-in: int(s)

def num(s):
    n = 0
    for i in s:
        n *= 10; n += int(i)
    return n