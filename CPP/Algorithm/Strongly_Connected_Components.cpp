// Complexity: O(v^2)

bool dfs(auto cur, auto des, auto& gp, auto& vis) {
	if (cur == des) return true;
	vis[cur] = 1;
	for (auto &x : gp[cur]) {
		if (!vis[x]) {
			if (dfs(x, des, gp, vis)) return true;
		}
	}
	return false;
}
auto isPath(auto src, auto des, auto& gp) {
	vector<int64_t> vis(gp.size() + 5);
	return dfs(src, des, gp, vis);
}
auto scc(auto n, auto& a) {
	vector<vector<int64_t>> ans, gp(n + 5);
	bool is_scc[n + 5]; int sz = a.size();
	for (int i = 0; i < sz; ++i) gp[a[i][0]].push_back(a[i][1]);
	for (int i = 1; i <= n; ++i) {
		if (!is_scc[i]) {
			vector<int64_t> con; con.push_back(i);
			for (int j = i + 1; j <= n; ++j) {
				if (!is_scc[j] && isPath(i, j, gp) && isPath(j, i, gp)) {
					is_scc[j] = 1; con.push_back(j);
				}
			}
			ans.push_back(con);
		}
	}
	return ans;
}

// Operation:
	int64_t v; cin >> v;
	vector<vector<int64_t>> edges;
	for (i = 0; i < v; ++i){
		int64_t a, b; cin >> a >> b;
		edges.push_back({a, b});
	}
	auto ans = scc(v, edges);
	cout << "Strongly Connected Components are:\n";
	for (auto &x : ans) {
		for (auto &y : x) cout << y << " ";
		cout << "\n";
	}