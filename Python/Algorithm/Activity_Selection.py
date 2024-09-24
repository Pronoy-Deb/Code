# Complexity: O(n*log(n))

def cmp(item): return item[1]
def act():
    ls.sort(key = cmp)
    ans, cur = 0, 0
    for item in ls:
        if item[0] >= cur:
            cur = item[1]; ans += 1
    return ans

# Operation:
global ls
n = int(input())
ls = []
for _ in range(n):
    start, end = map(int, input().split())
    ls.append((start, end))
print(act())

# Problem: https://cses.fi/problemset/task/1629