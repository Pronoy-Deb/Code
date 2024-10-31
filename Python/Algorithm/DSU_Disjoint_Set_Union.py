# Complexity: O(alpha(n))

def make(n):
    par = [i for i in range(n + 1)]
    sz = [1] * (n + 1)

def find(nd):
    if par[nd] == nd: return nd
    par[nd] = find(par[nd])
    return par[nd]

def union(a, b):
    a_root = find(a); b_root = find(b)
    if a_root != b_root:
        if sz[a_root] < sz[b_root]:
            a_root, b_root = b_root, a_root
        par[b_root] = a_root
        sz[a_root] += sz[b_root]

def cnt():
    return sum(find(i) == i for i in range(1, len(par)))

# Example usage:
global par, sz
n = int(input())
make(n)
uf = union(n)
for _ in range(n-1):
    u, v = map(int, input().split()); uf.union(u, v)
cc = uf.cnt(); print(cc)

# Problem: https://codeforces.com/contest/1857/problem/G

OR,

class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))

    def find(self, a):
        acopy = a
        while a != self.parent[a]:
            a = self.parent[a]
        while acopy != a:
            self.parent[acopy], acopy = a, self.parent[acopy]
        return a

    def union(self, a, b):
        self.parent[self.find(b)] = self.find(a)