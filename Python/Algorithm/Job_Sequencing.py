# Complexity: O(n * log(n))

import heapq
def js(ar):
    ar.sort(); n, c, sum = len(ar), 0, 0; pq = []
    for i in range(n - 1, -1, -1):
        slot = ar[i][0] - (ar[i - 1][0] if i else 0)
        heapq.heappush(pq, -ar[i][1])
        while slot > 0 and pq:
            c += 1; sum += -heapq.heappop(pq); slot -= 1
    return c, sum

# Example operation
n = int(input()); ar = []
for _ in range(n):
    first, second = map(int, input().split())
    ar.append((first, second))
ans = js(ar)
print(ans[0], ans[1])