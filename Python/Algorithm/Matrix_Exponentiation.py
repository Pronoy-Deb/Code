# Complexity: O(log(n))

def mul(a, b):
	mul = [[0 for x in range(3)] for y in range(3)]
	for i in range(3):
		for j in range(3):
			mul[i][j] = 0
			for k in range(3): mul[i][j] += a[i][k] * b[k][j]
	for i in range(3):
		for j in range(3): a[i][j] = mul[i][j]
	return a
def pow(F, n):
	M = [[1, 1, 1], [1, 0, 0], [0, 1, 0]]
	if (n == 1): return F[0][0] + F[0][1]
	pow(F, n >> 1); F = mul(F, F)
	if (n & 1): F = mul(F, M)
	return F[0][0] + F[0][1]
def find(n):
	F = [[1, 1, 1], [1, 0, 0], [0, 1, 0]]
	return pow(F, n - 2)

# Operation:
n = 5
print("F(5) is", find(n))