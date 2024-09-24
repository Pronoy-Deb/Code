# Complexity:
# Work: Checks if there is any cycle in the graph

def dfs(root, par):
    vis[root] = True
    for cld in grp[root]:
        if vis[cld] and cld == par: continue
        if vis[cld]: return True
        if dfs(cld, root): return True
    return False

def cycle(v):
    for i in range(1, v + 1):
        if not vis[i]:
            if dfs(i, -1): return True
    return False

# Reading number of edges and vertices
eg, vr = map(int, input().split())

# Initializing graph and visited array
global grp, vis
grp = [[] for _ in range(vr + 1)]
vis = [False] * (vr + 1)

# Building the graph
for _ in range(eg):
    v1, v2 = map(int, input().split())
    grp[v1].append(v2); grp[v2].append(v1)

# Checking for cycle
if cycle(vr): print("Cycle detected")
else: print("No cycle detected")