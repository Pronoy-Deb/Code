// Complexity: O(n^2 * 2^n), n = Number of Vertices

int64_t gp[N], vr;
bool hp() {
	int n = (1ll << vr); bool dp[vr][n]{};
	for (int i = 0; i < vr; ++i) dp[i][(1ll << i)] = true;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < vr; ++j) {
			if (i & (1ll << j)) {
				for (int k = 0; k < vr; ++k) {
					if (i & (1ll << k) && (gp[k] == j || gp[j] == k) && j != k && dp[k][i^(1ll << j)]) {
						dp[j][i] = true; break;
					}
				}
			}
		}
	}
	for (int i = 0; i < vr; ++i) {
		if (dp[i][n - 1]) return true;
	}
	return false;
}

// Operation:
    int eg; cin >> vr >> eg;  // vr < 20
    for (i = 0; i < eg; ++i) {
        int u, v; cin >> u >> v;
        gp[--u] = --v; gp[v] = u;
    }
    cout << hp();