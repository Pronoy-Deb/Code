# Complexity: O(v^2)

def dfs(curr, des, adj, vis):
	if curr == des: return True
	vis[curr] = 1
	for x in adj[curr]:
		if not vis[x]:
			if dfs(x, des, adj, vis): return True
	return False
def isPath(src, des, adj):
	vis = [0] * (len(adj) + 1)
	return dfs(src, des, adj, vis)
def findSCC(n, a):
	ans = []; is_scc = [0] * (n + 1)
	adj = [[] for _ in range(n + 1)]
	for i in range(len(a)): adj[a[i][0]].append(a[i][1])
	for i in range(1, n + 1):
		if not is_scc[i]:
			scc = [i]
			for j in range(i + 1, n + 1):
				if not is_scc[j] and isPath(i, j, adj) and isPath(j, i, adj):
					is_scc[j] = 1; scc.append(j)
			ans.append(scc)
	return ans

if __name__ == "__main__":
	v = int(input())
	edges = []
	for i in range(v):
		edges.append(list(map(int, input().split())))
	ans = findSCC(v, edges)
	print("Strongly Connected Components are:")
	for x in ans:
		for y in x: print(y, end=" ")
		print()
