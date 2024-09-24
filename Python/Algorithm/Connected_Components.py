# Complexity: O(V + E)
# eg = Number of edges, vr = Number of vertices

def dfs(root):
    vis[root] = True
    for child in grp[root]:
        if vis[child]: continue
        dfs(child)

# Reading number of vertices and edges
vr, eg = map(int, input().split())

# Initializing graph and visited array
global grp, vis
grp = [[] for _ in range(vr + 1)]
vis = [False] * (vr + 1)

# Building the graph
for _ in range(eg):
    v1, v2 = map(int, input().split())
    grp[v1].append(v2); grp[v2].append(v1)

# Counting connected components
ct = 0
for i in range(1, vr + 1):
    if not vis[i]: dfs(i); ct += 1

print(ct)

# To store the connected components

def dfs(root):
    vis[root] = True
    cur.append(root)
    for child in grp[root]:
        if vis[child]: continue
        dfs(child)

global grp, vis
grp = [[] for _ in range(vr + 1)]
vis = [False] * (vr + 1)

cc = []  # List to store connected components
for i in range(1, vr + 1):
    if not vis[i]: cur = []; dfs(i); cc.append(cur)

print(len(cc))
for r in cc: print(' '.join(map(str, r)))