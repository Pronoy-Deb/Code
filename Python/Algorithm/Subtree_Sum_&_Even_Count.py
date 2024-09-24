# Complexity:
# Work: Sums up and Count the value of vertices

tre = [[] for _ in range(N)]
ssum = [0] * N; sevn = [0] * N
def dfs(vr, par = -1):
    if ~vr & 1: sevn[vr] += 1
    ssum[vr] += vr
    for child in tre[vr]:
        if child == par: continue
        dfs(child, vr)
        ssum[vr] += ssum[child]
        sevn[vr] += sevn[child]

# Operation:
vr = int(input())
for _ in range(vr - 1):
    v1, v2 = map(int, input().split())
    tre[v1].append(v2); tre[v2].append(v1)
dfs(1)
for i in range(1, vr + 1):
    print(f"vrtex {i}: Sum = {ssum[i]}, Even Count = {sevn[i]}")