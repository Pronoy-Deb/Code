// Complexity: O(V + E)
https://cses.fi/problemset/task/1666

vector<int> gp[N]; bool vis[N];
void dfs(int par = 1) {
	vis[par] = true;
	for (auto &cld : gp[par]) {
		if (!vis[cld]) dfs(cld);
	}
}

// Operation:
	int vr, eg; cin >> vr >> eg;
	for (i = 0; i < eg; ++i) {
		int v1, v2; cin >> v1 >> v2;
		gp[v1].push_back(v2); gp[v2].push_back(v1);
	}
	vector<int> com;
	for (i = 1; i <= vr; ++i) {
		if (!vis[i]) {
			com.push_back(i); dfs(i);
		}
	}
    n = com.size(); cout << n - 1 << '\n';
	for (i = 0; i < n - 1; ++i) cout << com[i] << ' ' << com[i + 1] << '\n';