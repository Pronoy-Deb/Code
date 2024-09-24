# Complexity: O(E * V^2)
# Use: Used to determine the maximum flow from source to sink

from collections import deque
class Edge:
    def __init__(self, to, cap):
        self.to = to; self.cap = cap
def add_edge(from_, to, cap, edges, graph):
    edges.append(Edge(to, cap)); edges.append(Edge(from_, 0))
    graph[from_].append(len(edges) - 2); graph[to].append(len(edges) - 1)
def bfs(src, snk, graph, edges, dep):
    dep[:] = [-1] * len(dep); dep[src] = 0; q = deque([src])
    while q:
        u = q.popleft()
        for i in graph[u]:
            v = edges[i].to
            if edges[i].cap > 0 and dep[v] == -1:
                dep[v] = dep[u] + 1; q.append(v)
    return dep[snk] != -1
def dfs(u, snk, graph, edges, dep, cur, limit):
    if u == snk: return limit
    flow = 0
    while cur[u] < len(graph[u]):
        i = graph[u][cur[u]]; v = edges[i].to
        if dep[v] == dep[u] + 1 and edges[i].cap > 0:
            f = dfs(v, snk, graph, edges, dep, cur, min(limit - flow, edges[i].cap))
            if f > 0:
                edges[i].cap -= f; edges[i ^ 1].cap += f; flow += f
                if flow == limit: break
        cur[u] += 1
    return flow
def mflo(src, snk, graph, edges):
    flow = 0; dep = [-1] * len(graph)
    while bfs(src, snk, graph, edges, dep):
        cur = [0] * len(graph)
        flow += dfs(src, snk, graph, edges, dep, cur, float('inf'))
    return flow

# Operation
eg, src, snk = map(int, input().split())
graph = [[] for _ in range(max(eg, src, snk) + 1)]
edges = []
for _ in range(eg):
    u, v, w = map(int, input().split())
    add_edge(u, v, w, edges, graph)
print(mflo(src, snk, graph, edges))
