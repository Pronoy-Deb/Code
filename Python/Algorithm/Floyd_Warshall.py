# Complexity: O(n^3)
# Use: Used to determine the shortest distance of all connected nodes

def fw(vr, eg):
    dist = [[float('inf') for _ in range(vr)] for _ in range(vr)]
    for i in range(vr): dist[i][i] = 0
    for v1, v2, weight in eg: dist[v1-1][v2-1] = weight
    for k in range(vr):
        for i in range(vr):
            for j in range(vr):
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
    return dist

# Example usage
vr = int(input("Enter number of vr: "))
eg = []
print("Enter eg in the format: v1 v2 weight (Enter 'done' when finished):")
while True:
    edge = input()
    if edge == 'done': break
    v1, v2, weight = map(int, edge.split())
    eg.append((v1, v2, weight))
dis = fw(vr, eg)

# Printing the shortest dis
for i in range(vr):
    for j in range(vr):
        print(-1 if dis[i][j] == float('inf') else dis[i][j], end=' ')
    print()