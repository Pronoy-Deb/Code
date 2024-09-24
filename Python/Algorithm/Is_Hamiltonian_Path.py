# Complexity: O(n^2 * 2^n), n = Number of Vertices

def hp(vr, grp):
    n = 1 << vr; dp = [[False] * n for _ in range(vr)]
    for i in range(vr): dp[i][1 << i] = True
    for i in range(n):
        for j in range(vr):
            if i & (1 << j):
                for k in range(vr):
                    if i & (1 << k) and (grp[k] == j or grp[j] == k) and j != k and dp[k][i ^ (1 << j)]:
                        dp[j][i] = True
                        break
    for i in range(vr):
        if dp[i][n - 1]: return True
    return False

def check(vr, edges):
    grp = [0] * vr
    for u, v in edges:
        u, v = u - 1, v - 1
        grp[u] = v; grp[v] = u
    return hp(vr, grp)

# Example usage
vr = 4  # Number of vertices
edges = [(1, 2), (2, 3), (3, 4)]  # Example edges
print(check(vr, edges))