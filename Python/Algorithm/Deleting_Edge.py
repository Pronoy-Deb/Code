# Complexity:
# Work: Divides the tree into two parts so that product of the summation of the trees be maximum

def dfs(ver, par = 0):
    ssum[ver] += ver
    for child in tre[ver]:
        if child == par: continue
        dfs(child, ver)
        ssum[ver] += ssum[child]

# Reading the number of vertices
global tre, ssum
vr = int(input())
tre = [[] for _ in range(vr + 1)]
ssum = [0] * (vr + 1)

# Building the tree
for _ in range(vr - 1):
    v1, v2 = map(int, input().split())
    tre[v1].append(v2); tre[v2].append(v1)

# Start DFS from root (assuming root is 1)
dfs(1)

ans = 0
for i in range(2, vr + 1):
    part1 = ssum[i]; part2 = ssum[1] - part1
    ans = max(ans, (part1 * part2) % M)
print(ans)