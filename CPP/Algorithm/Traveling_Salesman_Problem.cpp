// Complexity: O(n^2 * 2^n),  n = Number of Vertices

int64_t gp[N][N], vr;
auto tsp() {
	int64_t c = 0, j = 0, i = 0, mn = LLONG_MAX, route[vr], sum = 0; bool vis[vr]{true};
	while (i < vr && j < vr) {
		if (c >= vr - 1) break;
		if (j != i && !vis[j]) {
			if (gp[i][j] < mn) {
				mn = gp[i][j]; route[c] = j + 1;
			}
		}
		if (++j == vr) {
			sum += mn; mn = LLONG_MAX;
			vis[route[c] - 1] = true;
			i = route[c++] - 1; j = 0;
		}
	}
	i = route[c - 1] - 1;
	for (j = 0; j < vr; ++j) {
		if ((i != j) && gp[i][j] < mn) {
			mn = gp[i][j]; route[c] = j + 1;
		}
	}
    return sum + mn;
}

// Operation:
    int eg; cin >> vr >> eg;
    for (i = 0; i < eg; ++i) {
        int u, v, w; cin >> u >> v >> w;
        gp[--u][--v] = w; gp[v][u] = w;
    }
	cout << tsp();