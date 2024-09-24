# // Complexity: O(V + E)

from collections import deque

def bfs(src, gp, lvl, vis):
    vis[src] = True
    q = deque([src])
    while q:
        node = q.popleft()
        for child in gp[node]:
            if not vis[child]:
                q.append(child)
                vis[child] = True
                lvl[child] = lvl[node] + 1

# Operation
vr = int(input())
gp = [[] for _ in range(vr + 1)]
lvl = [0] * (vr + 1)
vis = [False] * (vr + 1)

for _ in range(vr - 1):
    v1, v2 = map(int, input().split())
    gp[v1].append(v2)
    gp[v2].append(v1)

rt = 1 # Assuming the root is 1, or replace with the desired root
bfs(rt, gp, lvl, vis)

# Printing Level
for i in range(1, vr + 1):
    print(f"{i} : {lvl[i]}")