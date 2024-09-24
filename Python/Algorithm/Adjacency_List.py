# Space Complexity: O(V + E)
# e = Number of edges, v = Number of vertices

# Taking input of an undirected graph without weight :

v, e = map(int, input().split())  # Number of vertices and edges
gp = [[] for _ in range(v + 1)]

for _ in range(e):
    v1, v2 = map(int, input().split())
    gp[v1].append(v2)
    gp[v2].append(v1)


# Checking the connectivity of two nodes:
# Complexity: O(n)

def con(nd, nd1):
    return nd1 in gp[nd]

# Example usage
node1, node2 = map(int, input().split())
print(con(node1, node2))


# Taking input of an undirected graph with weight:
# wt = weight of the edges

v, e = map(int, input().split())  # Number of vertices and edges
gp = [[] for _ in range(v + 1)]

for _ in range(e):
    v1, v2, wt = map(int, input().split())
    gp[v1].append((v2, wt))
    gp[v2].append((v1, wt))


# Checking the weight of the edge between two nodes:
# Complexity: O(n)

def wet(nd, nd1):
    for child, weight in gp[nd]:
        if child == nd1:
            return weight
    return -1

# Example usage
node1, node2 = map(int, input().split())
print(wet(node1, node2))