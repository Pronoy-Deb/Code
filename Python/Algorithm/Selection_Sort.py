# Complexity: O(n^2)

def ssrt(ls):
    n = len(ls)
    for i in range(n - 1):
        mnin = i
        for j in range(i + 1, n):
            if ls[j] < ls[mnin]: mnin = j
        if i != mnin: ls[i], ls[mnin] = ls[mnin], ls[i]