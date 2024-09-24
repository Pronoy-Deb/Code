def centroid_decomposition_tree(graph):
    n = len(graph); graph = [c[:] for c in graph]; bfs = [0]
    for node in bfs:
        bfs += graph[node]
        for nei in graph[node]:
            graph[nei].remove(node)
    size = [0] * n
    for node in reversed(bfs):
        size[node] = 1 + sum(size[child] for child in graph[node])
    decomposition_tree = [[] for _ in range(n)]
    def centroid_reroot(u):
        N = size[u]
        while True:
            for v in graph[u]:
                if size[v] > (N >> 1):
                    size[u] = N - size[v]; graph[u].remove(v)
                    graph[v].append(u); u = v; break
            else: # u is the centroid
                decomposition_tree[u] = [centroid_reroot(v) for v in graph[u]]; return u
    decomposition_root = centroid_reroot(0)
    return decomposition_tree, decomposition_root