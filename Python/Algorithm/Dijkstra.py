# Complexity: O(V + E*log(V))
# Use: Used to determine the shortest distance between source and destination vertex
# Note: Does not work for negative (-ve) value of weights, use Bellman-Ford instead

import heapq
def dij(src, vr, edges):
    grp = [[] for _ in range(vr)]
    for v1, v2, wt in edges:
        grp[v1].append((v2, wt)); grp[v2].append((v1, wt))
    dis = [float('inf')] * vr
    dis[src] = 0; path = [-1] * vr; vis = [False] * vr
    pq = [(0, src)]
    while pq:
        dist, node = heapq.heappop(pq)
        if vis[node]: continue
        vis[node] = True
        for child_v, wt in grp[node]:
            if dis[node] + wt < dis[child_v]:
                dis[child_v] = dis[node] + wt
                path[child_v] = node
                heapq.heappush(pq, (dis[child_v], child_v))
    return dis, path

# Operation
vr, eg = map(int, input().split())
edges = [tuple(map(int, input().split())) for _ in range(eg)]
src = int(input())
dis, path = dij(src, vr, edges)

# Printing the shortest distance to a vertex
print(dis[vr])

# Storing and printing the shortest path
def print_path(vr, path):
    if vr == -1 or path[vr] == -1:
        print(-1); return
    route = []
    while vr != -1:
        route.append(vr); vr = path[vr]
    route.reverse()
    print(' '.join(map(str, route)))

print_path(vr, path)