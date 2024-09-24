# Complexity: O(n^2 * 2^n),  n = Number of Vertices

import sys
def tsp(grp, vr):
    sum = 0; vis = [False] * vr
    vis[0] = True; route = []; c = 0
    for _ in range(vr - 1):
        mn = sys.maxsize; sel = -1
        for j in range(vr):
            if not vis[j] and grp[c][j] < mn:
                mn = grp[c][j]; sel = j
        route.append(sel); vis[sel] = True
        sum += mn; c = sel
    sum += grp[c][0]; return sum

# Example operation
vr, eg = map(int, input().split())
grp = [[sys.maxsize for _ in range(vr)] for __ in range(vr)]
for _ in range(eg):
    u, v, w = map(int, input().split())
    grp[u-1][v-1] = w; grp[v-1][u-1] = w
print(tsp(grp, vr))