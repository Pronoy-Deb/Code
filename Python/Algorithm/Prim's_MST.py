# Complexity: O(E*log(V))
# Use: Used to determine the cost for building an MST and the connected vertices
# Note: 1-based index

from heapq import heappop, heappush; import sys
grp = [[] for _ in range(N)]; par = [-1] * N
def mst(vr):
    src, cost = 1, 0
    key = [sys.maxsize] * (vr + 1)
    vis = [False] * (vr + 1); pq = []
    heappush(pq, (0, src)); key[src] = 0
    while pq:
        _, u = heappop(pq)
        if vis[u]: continue
        vis[u] = True
        for f, s in grp[u]:
            if not vis[f] and key[f] > s:
                if key[f] != sys.maxsize: cost -= key[f]
                key[f] = s; cost += s; par[f] = u
                heappush(pq, (s, f))
    return cost

# Example usage:
vr, eg = map(int, input().split())
for _ in range(eg):
    u, v, w = map(int, input().split())
    grp[u].append((v, w)); grp[v].append((u, w))
print(mst(vr))
for i in range(1, vr + 1):
    if par[i] != -1: print(f"{i} {par[i]}")