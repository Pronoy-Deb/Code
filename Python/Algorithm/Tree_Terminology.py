# Complexity: O(n)

tre = [[] for _ in range(N)]
par = [-1] * N; lvl = [0] * N; sz = [0] * N
def dfs(u, p=-1):
    par[u] = p; sz[u] = 1
    for v in tre[u]:
        if v != p:
            lvl[v] = lvl[u] + 1
            dfs(v, u); sz[u] += sz[v]

# Example operation to read a tree and perform DFS
eg = int(input())
for _ in range(eg):
    u, v = map(int, input().split())
    tre[u].append(v); tre[v].append(u)
dfs(1)
for i in range(1, eg + 2):
    print(f"Vertex {i}: Parent = {par[i]}, Level = {lvl[i]}, Subtree Size = {sz[i]}")