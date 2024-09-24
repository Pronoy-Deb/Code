# Complexity: O(V * E)
# Use: Used to determine the shortest distance between source and destination vertex
# Note: Works for negative (-ve) value of weights

import heapq
def bmf(src, grp, dis):
    V = len(dis)
    dis[src] = 0
    up = False

    for _ in range(V - 1):
        up = False
        for u in range(V):
            if dis[u] != sys.maxsize:
                for v, w in grp[u]:
                    if dis[u] + w < dis[v]:
                        dis[v] = dis[u] + w
                        up = True

    # Check for negative weight cycle
    for u in range(V):
        for v, w in grp[u]:
            if dis[u] + w < dis[v]:
                return True
    return False


# Example operation
vr, eg = map(int, input().split())
grp = [[] for _ in range(vr + 1)]
dis = [sys.maxsize] * (vr + 1)

for _ in range(eg):
    u, v, w = map(int, input().split())
    grp[u].append((v, w))

src = int(input())  # Specify the source

if bmf(src, grp, dis):
    print(-1)
else:
    for i in range(vr):
        print(dis[i])
