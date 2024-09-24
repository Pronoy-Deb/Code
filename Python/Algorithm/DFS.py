# Complexity: O(V + E)
# eg = Number of edges, vr = Number of vertices

def dfs(par):
    vis[par] = True
    for cld in gp[par]:
        if not vis[cld]: dfs(cld)

# Operation
global gp, vis
vr, eg = map(int, input().split())
gp = {i: [] for i in range(vr)}
vis = [False] * vr

for _ in range(eg):
    v1, v2 = map(int, input().split())
    gp[v1].append(v2); gp[v2].append(v1)

dfs(1)