# Comlexity: O(V + E)

def dfs(tre, vertex, par, par = -1):
    par[vertex] = par
    for child in tre[vertex]:
        if child == par: continue
        dfs(tre, child, par, vertex)

def path(vertex, par):
    ans = []
    while vertex != -1:
        ans.append(vertex); vertex = par[vertex]
    ans.reverse(); return ans

# Operation:
vr = int(input())
tre = [[] for _ in range(vr + 1)]
par = [-1 for _ in range(vr + 1)]
for _ in range(vr - 1):
    v1, v2 = map(int, input().split())
    tre[v1].append(v2); tre[v2].append(v1)
rt = 1; dfs(tre, rt, par)
n1, n2 = map(int, input().split())
pn1, pn2 = path(n1, par), path(n2, par); lca = -1
for i in range(min(len(pn1), len(pn2))):
    if pn1[i] == pn2[i]: lca = pn1[i]
    else: break
print(f"LCA: {lca}")