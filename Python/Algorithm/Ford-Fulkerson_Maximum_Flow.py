# Complexity: O(V * E^2)
# Use: Used to determine the maximum flow from source to sink
# Note: Dinic's algorithm is faster than it

from collections import deque
import sys
def bfs(graph, rgrp, src, sink, par):
    vis = [False] * len(graph)
    queue = deque(); queue.append(src)
    vis[src] = True
    while queue:
        u = queue.popleft()
        for ind, val in enumerate(rgrp[u]):
            if vis[ind] == False and val > 0:
                queue.append(ind)
                vis[ind] = True; par[ind] = u
                if ind == sink: return True
    return False

def edKarp(graph, source, sink):
    rgrp = [row[:] for row in graph]  # Residual graph
    par = [-1] * len(graph); mxflo = 0
    while bfs(graph, rgrp, source, sink, par):
        pflo = float("Inf"); s = sink
        while(s != source):
            pflo = min(pflo, rgrp[par[s]][s])
            s = par[s]
        mxflo += pflo; v = sink
        while(v != source):
            u = par[v]; rgrp[u][v] -= pflo
            rgrp[v][u] += pflo; v = par[v]
    return mxflo

# Example Usage
vertices, edges, source, sink = map(int, input("Enter vertices, edges, source, sink: ").split())
graph = [[0 for _ in range(vertices)] for _ in range(vertices)]

for _ in range(edges):
    u, v, w = map(int, input().split())
    graph[u][v] = w

print("The maximum flow is:", edKarp(graph, source, sink))

# Problem: lightoj 1153