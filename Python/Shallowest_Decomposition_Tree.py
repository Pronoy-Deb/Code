def ctz(x): return (x & -x).bit_length() - 1
def shallowest_decomposition_tree(graph, root=0):
    n = len(graph); forbidden = [0] * n
    decomposition_tree = [[] for _ in range(n)]
    stacks = [[] for _ in range(n.bit_length())]
    def extract_chain(labels, u):
        while labels:
            label = labels.bit_length() - 1; labels ^= 2**label
            v = stacks[label].pop(); decomposition_tree[u].append(v); u = v
    dfs = [root]
    while dfs:
        u = dfs.pop()
        if u >= 0:
            forbidden[u] = -1; dfs.append(~u)
            for v in graph[u]:
                if not forbidden[v]: dfs.append(v)
        else:
            u = ~u; forbidden_once = forbidden_twice = 0
            for v in graph[u]:
                forbidden_twice |= forbidden_once & (forbidden[v] + 1)
                forbidden_once |= forbidden[v] + 1
            forbidden[u] = forbidden_once | ((1 << forbidden_twice.bit_length()) - 1)
            label_u = ctz(forbidden[u] + 1); stacks[label_u].append(u)
            for v in graph[u]:
                extract_chain((forbidden[v] + 1) & ((1 << label_u) - 1), u)
    max_label = (forbidden[root] + 1).bit_length() - 1
    decomposition_root = stacks[max_label].pop()
    extract_chain((forbidden[root] + 1) & ((1 << max_label) - 1), decomposition_root)
    return decomposition_tree, decomposition_root