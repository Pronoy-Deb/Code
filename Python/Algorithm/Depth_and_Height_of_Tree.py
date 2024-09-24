# Complexity:
# Note: For Tree -> No of Edges = No of Vertices - 1

def dfs(ver, par=0):
    for child in tre[ver]:
        if child == par: continue
        dep[child] = dep[ver] + 1; dfs(child, ver)
        hit[ver] = max(hit[ver], hit[child] + 1)

# Reading the number of vertices
global tre, dep, hit
vr = int(input())
tre = [[] for _ in range(vr + 1)]
dep = [0] * (vr + 1); hit = [0] * (vr + 1)

# Building the tree
for _ in range(vr - 1):
    v1, v2 = map(int, input().split())
    tre[v1].append(v2); tre[v2].append(v1)

# Assuming the root is 1 (modify if needed)
dfs(1)

# Displaying the depth and height for each node
for i in range(1, vr + 1): print(dep[i], hit[i])