# Complexity: O(1)

from math import sqrt
def ed(x1, y1, x2, y2):
    a = (x2 - x1) * (x2 - x1)
    b = (y2 - y1) * (y2 - y1)
    return sqrt(a + b)