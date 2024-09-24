# Complexity: O(n)
# Application: Used to determine the number of consecutive smaller elements of a number before it.

# Stack Approach:

def ss(price):
    n = len(price); ans = [0] * n; sk = [0]; ans[0] = 1
    for i in range(1, n):
        while sk and price[sk[-1]] <= price[i]: sk.pop()
        ans[i] = i + 1 if not sk else i - sk[-1]
        sk.append(i)
    return ans

# DP Approach:

def ss(price):
    n = len(price); ans = [1] * n
    for i in range(1, n):
        cnt = 1
        while i - cnt >= 0 and price[i] >= price[i - cnt]:
            cnt += ans[i - cnt]
        ans[i] = cnt
    return ans