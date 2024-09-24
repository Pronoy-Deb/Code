# Complexity = O(alpha(n)) or, O(E*log(E)) or, O(E*log(V))
# Use: Used to determine the cost for building an MST and the connected vertices
# Note: 1-based index

def find(nd, par):
    if nd == par[nd]: return nd
    par[nd] = find(par[nd], par)
    return par[nd]

def mst(vr, grp):
    grp.sort(); par = [i for i in range(vr + 1)]
    sz = [1] * (vr + 1); cost = 0; cv = []
    for wt, (v1, v2) in grp:
        a = find(v1, par); b = find(v2, par)
        if a == b: continue
        cv.append((v1, v2))
        if sz[a] < sz[b]: a, b = b, a
        par[b] = a; sz[a] += sz[b]; cost += wt
    return cost, cv

# Operation:
vr, eg = map(int, input().split()); grp = []
for _ in range(eg):
    v1, v2, wt = map(int, input().split())
    grp.append((wt, (v1, v2)))
cost, cv = mst(vr, grp)
print(cost)
for f, s in cv: print(f, s)