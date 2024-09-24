# Complexity: O(n)

def mxsum(ls, k):
    mx_sum = sum(ls[:k])
    winsum = mx_sum
    for i in range(k, len(ls)):
        winsum += ls[i] - ls[i - k]
        mx_sum = max(mx_sum, winsum)
    return mx_sum

# Operation:
n, k = map(int, input().split())
ls = list(map(int, input().split()))
print(mxsum(ls, k))