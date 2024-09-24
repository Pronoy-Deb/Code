# Complexity: O(n^2)

# For the same array:

r, c = map(int, input().split())
ar = [[0] * (c + 1) for _ in range(r + 1)]

for i in range(1, r + 1):
    row = list(map(int, input().split()))
    for j in range(1, c + 1):
        ar[i][j] = row[j - 1] + ar[i - 1][j] + ar[i][j - 1] - ar[i - 1][j - 1]

# To output the summation of a specific rectangular shaped range (x1, y1, x2, y2):

x1, y1, x2, y2 = map(int, input().split())
print(ar[x2][y2] - ar[x1 - 1][y2] - ar[x2][y1 - 1] + ar[x1 - 1][y1 - 1])

# For a different array:

r, c = map(int, input().split())
ar = [[0] * (c + 1) for _ in range(r + 1)]
pre = [[0] * (c + 1) for _ in range(r + 1)]

for i in range(1, r + 1):
    row = list(map(int, input().split()))
    for j in range(1, c + 1):
        ar[i][j] = row[j - 1]
        pre[i][j] = ar[i][j] + pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1]

# To output the summation of a specific rectangular shaped range (x1, y1, x2, y2):

x1, y1, x2, y2 = map(int, input().split())
print(pre[x2][y2] - pre[x1 - 1][y2] - pre[x2][y1 - 1] + pre[x1 - 1][y1 - 1])