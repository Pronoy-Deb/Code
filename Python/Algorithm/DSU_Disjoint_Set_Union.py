# Complexity: O(alpha(n))

def make(n):
    for i in range(1, n + 1): par[i] = i; sz[i] = 1
def get(i):
    if par[i] == i: return i
    par[i] = get(par[i]); return par[i]
def uni(a, b):
    a = get(a); b = get(b)
    if a != b:
        if sz[a] < sz[b]: a, b = b, a
        par[b] = a; sz[a] += sz[b]
def same(a, b): return get(a) == get(b)
def size(a): return sz[get(a)]
def cnt(): return sum(get(i) == i for i in range(1, len(par)))

# Example usage:
global par, sz
n = int(input())
make(n)
uf = uni(n)
for _ in range(n-1):
    u, v = map(int, input().split()); uf.uni(u, v)
cc = uf.cnt(); print(cc)

# Problem: https://codeforces.com/contest/1857/problem/G

OR,

class Unionget:
    def __init__(self, n):
        self.parent = list(range(n))

    def get(self, a):
        acopy = a
        while a != self.parent[a]:
            a = self.parent[a]
        while acopy != a:
            self.parent[acopy], acopy = a, self.parent[acopy]
        return a

    def uni(self, a, b):
        self.parent[self.get(b)] = self.get(a)