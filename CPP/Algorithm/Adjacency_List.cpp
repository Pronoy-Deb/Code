// Space Complexity: O(V + E)
// e = Number of edges, v = Number of vertices

// Taking input of an undirected graph without weight:

vector<int64_t> gp[v + 5];
for (int i = 0; i < e; ++i) {
    int64_t v1, v2; cin >> v1 >> v2;
    gp[v1].emplace_back(v2); gp[v2].emplace_back(v1);
}
// Checking the connectivity of two nodes:
// Complexity: O(n)

vector<int64_t> gp[v + 5];
bool con(int64_t nd, int64_t nd1) {
    for (auto &child : gp[nd]) {
        if (child == nd1) return true;
    }
    return false;
}

// Taking input of an undirected graph with weight:
// wt = weight of the edges

vector<pair<int64_t, int64_t>> gp(v + 5);
for (int i = 0; i < e; ++i) {
    int64_t v1, v2, wt; cin >> v1 >> v2 >> wt;
    gp[v1].emplace_back(v2, wt); gp[v2].emplace_back(v1, wt);
}

// Checking the weight of the edge between two nodes:
// Complexity: O(n)

vector<pair<int64_t, int64_t>> gp(v + 5);
int64_t wet(auto nd, auto nd1) {
    for(auto &child : gp[nd]) {
        if(child.first == nd1) return child.second;
    }
    return -1;
}