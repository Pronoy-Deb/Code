# Complexity: O(n + m)

n = 0
adj, adj_t = [], []
used, assignment = [], []
order, comp = [], []

def dfs1(v):
    used[v] = True
    for u in adj[v]:
        if not used[u]: dfs1(u)
    order.append(v)

def dfs2(v, cl):
    comp[v] = cl
    for u in adj_t[v]:
        if comp[u] == -1: dfs2(u, cl)

def solve_2SAT():
    global order, used, comp, assignment
    order.clear(); used = [False] * n
    for i in range(n):
        if not used[i]: dfs1(i)
    comp = [-1] * n; j = 0
    for i in range(n):
        v = order[n - i - 1]
        if comp[v] == -1:
            dfs2(v, j); j += 1
    assignment = [False] * (n // 2)
    for i in range(0, n, 2):
        if comp[i] == comp[i + 1]: return False
        assignment[i // 2] = comp[i] > comp[i + 1]
    return True

def add_disjunction(a, na, b, nb):
    a = (a << 1) ^ na; b = (b << 1) ^ nb
    neg_a = a ^ 1; neg_b = b ^ 1
    adj[neg_a].append(b); adj[neg_b].append(a)
    adj_t[b].append(neg_a); adj_t[a].append(neg_b)
