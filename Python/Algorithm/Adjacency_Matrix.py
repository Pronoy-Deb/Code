# Space Complexity: O(n^2)

# Note: Cannot take input of a high edge valued graph
# e = Number of edges, v = Number of vertices

# Taking input of an undirected graph without weight:

v, e = map(int, input().split())  # Number of vertices and edges
gp = [[0 for _ in range(v + 1)] for _ in range(v + 1)]

for _ in range(e):
    v1, v2 = map(int, input().split())
    gp[v1][v2] = 1
    gp[v2][v1] = 1


# Taking input of an undirected graph with weight:
# wt = weight of the edges

v, e = map(int, input().split())  # Number of vertices and edges
gp = [[0 for _ in range(v + 1)] for _ in range(v + 1)]

for _ in range(e):
    v1, v2, wt = map(int, input().split())
    gp[v1][v2] = wt
    gp[v2][v1] = wt


# Checking the connectivity or weight between two nodes:
# Complexity: O(1)

def con(nd, nd1):
    return gp[nd][nd1]