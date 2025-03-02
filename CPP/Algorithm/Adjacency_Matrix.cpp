// Space Complexity: O(n^2)
// Note: Cannot take input of a high edge valued graph
// e = Number of edges, v = Number of vertices

// Taking input of an undirected graph without weight:

bool gp[v + 5][v + 5];
for (int i = 0; i < e; ++i) {
    int v1, v2; cin >> v1 >> v2;
    gp[v1][v2] = 1; gp[v2][v1] = 1;
}

// Taking input of an undirected graph with weight:
// wt = weight of the edges

int64_t gp[v + 1][v + 1];
for (int i = 0; i < e; ++i) {
    int v1, v2, wt; cin >> v1 >> v2 >> wt;
    gp[v1][v2] = wt; gp[v2][v1] = wt;
}

// Checking the connectivity or weight between two nodes:
// Complexity: O(1)

auto con(auto nd, auto nd1) {
    return gp[nd][nd1];
}