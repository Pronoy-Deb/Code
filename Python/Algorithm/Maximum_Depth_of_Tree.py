# Comlexity: O(v)

def dfs(ver, tre, dep, par = -1):
    for child in tre[ver]:
        if child == par: continue
        dep[child] = dep[ver] + 1
        dfs(child, tre, dep, ver)

# Taking input and preparing for the operation
vr = int(input())
tre = [[] for _ in range(vr)]
dep = [0] * vr
for _ in range(vr-1):
    v1, v2 = map(int, input().split())
    tre[v1].append(v2); tre[v2].append(v1)

dfs(0, tre, dep)

# Finding the farthest node from the root
mxnd = max(range(len(dep)), key=dep.__getitem__)

# Resetting depths and calling DFS from the farthest node
dep = [0] * vr; dfs(mxnd, tre, dep)

# Outputting the tree's diameter
print(max(dep))