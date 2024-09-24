# Complexity: O(|main| * |sub|)

# Built-in Approach:

def sstr(main, sub): return sub in main

# Iterative Approach:

def sstr(main, sub):
    m, n = len(main), len(sub)
    for i in range(m - n + 1):
        for j in range(n):
            if main[i + j] != sub[j]: break
        else: return True
    return False