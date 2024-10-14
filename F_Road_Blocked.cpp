#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

const int N = 305;
const long long INF = 1e12;
long long dis[N][N], h[N], graph[N][N];
int n, m, q;

void reset() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            graph[i][j] = (i == j) ? 0 : INF;
            dis[i][j] = graph[i][j];
        }
    }
}

// Bellman-Ford to remove negative weights
bool BellmanFord() {
    vector<long long> dist(n + 1, INF);
    dist[n] = 0;  // Extra vertex connected to all vertices

    for (int i = 0; i <= n; ++i) {
        bool updated = false;
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                if (graph[u][v] < INF && dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                    updated = true;
                }
            }
        }
        if (!updated) break;
        if (i == n) return false;  // Negative cycle detected
    }

    for (int i = 1; i <= n; ++i) h[i] = dist[i];
    return true;
}

// Dijkstra with re-weighting
void Dijkstra(int src) {
    vector<long long> dist(n + 1, INF);
    dist[src] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;

        for (int v = 1; v <= n; ++v) {
            if (graph[u][v] < INF) {
                long long cost = graph[u][v] + h[u] - h[v];
                if (dist[u] + cost < dist[v]) {
                    dist[v] = dist[u] + cost;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    for (int v = 1; v <= n; ++v) {
        dis[src][v] = dist[v] + h[v] - h[src];
    }
}

// Johnson's algorithm
void Johnson() {
    if (!BellmanFord()) {
        cout << "Negative weight cycle detected!\n";
        return;
    }

    for (int i = 1; i <= n; ++i) {
        Dijkstra(i);
    }
}

// Add an edge
void add_edge(int a, int b, long long c) {
    graph[a][b] = min(graph[a][b], c);
    graph[b][a] = min(graph[b][a], c);
    Johnson();  // Recalculate shortest paths after adding an edge
}

// Remove an edge
void remove_edge(int a, int b) {
    graph[a][b] = graph[b][a] = INF;
    Johnson();  // Recalculate shortest paths after removing an edge
}

int main() {
    cin >> n >> m >> q;
    reset();

    vector<vector<int>> edges(m);
    int a, b;
    long long c;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b >> c;
        edges[i] = {a, b, c};
        add_edge(a, b, c);
    }

    vector<vector<int>> queries(q);
    for (int i = 0; i < q; ++i) {
        int type;
        cin >> type;
        if (type == 1) {  // Remove edge
            int x;
            cin >> x;
            --x;
            int u = edges[x][0], v = edges[x][1];
            remove_edge(u, v);
            queries[i] = {1, x};
        } else {  // Shortest path query
            int x, y;
            cin >> x >> y;
            queries[i] = {2, x, y};
        }
    }

    vector<long long> answers;
    for (int i = q - 1; i >= 0; --i) {
        if (queries[i][0] == 2) {  // Shortest path query
            int x = queries[i][1], y = queries[i][2];
            if (dis[x][y] >= INF) answers.push_back(-1);
            else answers.push_back(dis[x][y]);
        } else {  // Restore the edge
            int edge_id = queries[i][1];
            int u = edges[edge_id][0], v = edges[edge_id][1];
            long long c = edges[edge_id][2];
            add_edge(u, v, c);  // Restore the edge
        }
    }

    for (int i = answers.size() - 1; i >= 0; --i) {
        cout << answers[i] << '\n';
    }

    return 0;
}
