// Complexity: O(V * E^2)
// Use: Used to determine the maximum flow from source to sink
// Note: Dinic's algorithm is faster than it

long long vr, eg, src, snk, gp[N][N], rgp[N][N], par[N];
bool bfs() {  // added by Edmonds-Karp
	bool vis[N] = {}; vis[src] = true; par[src] = -1;
	queue<int> q; q.emplace(src);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int v = 0; v < vr; ++v) {
			if (vis[v] == false && rgp[u][v] > 0) {
				if (v == snk) {
					par[v] = u; return true;
				}
				q.emplace(v); par[v] = u; vis[v] = true;
			}
		}
	}
	return false;
}
long long mflo() {
	long long mx = 0;
	while (bfs()) {
		long long pflo = LLONG_MAX;
		for (int v = snk; v != src; v = par[v])
			pflo = min(pflo, rgp[par[v]][v]);
		for (int v = snk; v != src; v = par[v]) {
			rgp[par[v]][v] -= pflo; rgp[v][par[v]] += pflo;
		}
		mx += pflo;
	}
	return mx;
}

// Operation:
    cin >> vr >> eg >> src >> snk;
    for (i = 0; i < eg; ++i) {
        long long u, v, w; cin >> u >> v >> w;
        gp[u][v] = w; rgp[u][v] = w;
    }
	cout << mflo();

// Problem: lightoj 1153