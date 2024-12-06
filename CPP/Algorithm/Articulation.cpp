// Articulation Points:
// Complexity: O()

ll tin[N], low[N], timer; bool vis[N], is_cut[N];
vector<ll> gp[N];
void dfs(ll v, ll p = -1) {
	vis[v] = true; tin[v] = low[v] = timer++; ll cld = 0;
	for (auto &to : gp[v]) {
		if (to == p) continue;
		if (vis[to]) low[v] = min(low[v], tin[to]);
		else {
			dfs(to, v); low[v] = min(low[v], low[to]);
			if (low[to] >= tin[v] && p != -1) is_cut[v] = true;
			++cld;
		}
	}
	if (p == -1 && cld > 1) is_cut[v] = true;
}
void cutpoint(ll n) {
	timer = 0;
	for (int i = 0; i <= n; ++i) {
		vis[i] = is_cut[i] = false; tin[i] = low[i] == -1;
	}
	for (int i = 0; i < n; ++i) {
		if (!vis[i]) dfs(i);
	}
}

// Operation:
	cin >> n >> m;
	for (i = 1; i <= m; ++i) {
		int u, v; cin >> u >> v;
		gp[u].push_back(v); gp[v].push_back(u);
	}
	cutpoint(n); ll ans = 0;
	for (i = 1; i <= n; ++i) ans += is_cut[i];
	cout << ans << "\n";
	for (i = 0; i <= n; ++i) gp[i].clear();

// Problem: https://lightoj.com/problem/ant-hills

// Articulation Bridges:

#include <bits/stdc++.h>
using namespace std;

struct TECC
{ // 0 indexed
	int n, k;
	vector<vector<int>> g, t;
	vector<bool> used;
	vector<int> comp, ord, low;
	using edge = pair<int, int>;
	vector<edge> br;
	void dfs(int x, int prv, int &c)
	{
		used[x] = 1;
		ord[x] = c++;
		low[x] = n;
		bool mul = 0;
		for (auto y : g[x])
		{
			if (used[y])
			{
				if (y != prv || mul)
					low[x] = min(low[x], ord[y]);
				else
					mul = 1;
				continue;
			}
			dfs(y, x, c);
			low[x] = min(low[x], low[y]);
		}
	}
	void dfs2(int x, int num)
	{
		comp[x] = num;
		for (auto y : g[x])
		{
			if (comp[y] != -1)
				continue;
			if (ord[x] < low[y])
			{
				br.push_back({x, y});
				k++;
				dfs2(y, k);
			}
			else
				dfs2(y, num);
		}
	}
	TECC(const vector<vector<int>> &g) : g(g), n(g.size()), used(n), comp(n, -1), ord(n), low(n), k(0)
	{
		int c = 0;
		for (int i = 0; i < n; i++)
		{
			if (used[i])
				continue;
			dfs(i, -1, c);
			dfs2(i, k);
			k++;
		}
	}
	void build_tree()
	{
		t.resize(k);
		for (auto e : br)
		{
			int x = comp[e.first], y = comp[e.second];
			t[x].push_back(y);
			t[y].push_back(x);
		}
	}
};
int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> g(n);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	TECC t(g);
	vector<vector<int>> ans(t.k);
	for (int i = 0; i < n; i++)
	{
		ans[t.comp[i]].push_back(i);
	}
	cout << ans.size() << '\n';
	for (auto x : ans)
	{
		cout << x.size();
		for (auto y : x)
			cout << ' ' << y;
		cout << '\n';
	}
	return 0;
}
// https://judge.yosupo.jp/problem/two_edge_connected_components

// Online Articulation Bridges:

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9;
// Given number of nodes n and q queries
// add edge (u,v)
// output the bridges in current graph
struct OnlineBridge
{
	// 1 indexed
	vector<int> par, dsu_2ecc, dsu_cc, dsu_cc_size;
	int bridges;
	int lca_iteration;
	vector<int> last_visit;
	OnlineBridge() {}
	OnlineBridge(int n)
	{
		dsu_2ecc.resize(n + 1); // contains info of the forest of 2-edge-connected components
		dsu_cc.resize(n + 1);	// contains the info of the forest of bridge trees
		par.resize(n + 1);		// stores the correct parent of the root of each 2-edge-connected component in the bridge tree
		dsu_cc_size.resize(n + 1);
		lca_iteration = 0;
		last_visit.assign(n + 1, 0);
		for (int i = 0; i <= n; ++i)
		{
			dsu_2ecc[i] = i;
			dsu_cc[i] = i;
			dsu_cc_size[i] = 1;
			par[i] = -1;
		}
		bridges = 0;
	}
	// returns representative of the 2-edge-connected component u is in
	int find_2ecc(int u)
	{
		if (u == -1)
			return -1;
		return dsu_2ecc[u] == u ? u : dsu_2ecc[u] = find_2ecc(dsu_2ecc[u]);
	}
	// returns representative of the bridge tree u is in
	int find_cc(int u)
	{
		u = find_2ecc(u);
		return dsu_cc[u] == u ? u : dsu_cc[u] = find_cc(dsu_cc[u]);
	}
	// let v = the root of the 2-edge-connected component u is in
	// now make v the root of the bridge tree v is in
	void make_root(int u)
	{
		u = find_2ecc(u);
		int root = u;
		int child = -1;
		while (u != -1)
		{
			int p = find_2ecc(par[u]);
			par[u] = child;
			dsu_cc[u] = root;
			child = u;
			u = p;
		}
		// at this moment child = the previous root of the tree
		int previous_root = child;
		dsu_cc_size[root] = dsu_cc_size[previous_root];
	}
	// contract everything from u to v into a single node, to be precise, their LCA
	void merge_path(int u, int v)
	{
		++lca_iteration;
		vector<int> path_u, path_v;
		int lca = -1;
		while (lca == -1)
		{
			if (u != -1)
			{
				u = find_2ecc(u);
				path_u.push_back(u);
				if (last_visit[u] == lca_iteration)
				{
					lca = u;
					break;
				}
				last_visit[u] = lca_iteration;
				u = par[u];
			}
			if (v != -1)
			{
				v = find_2ecc(v);
				path_v.push_back(v);
				if (last_visit[v] == lca_iteration)
				{
					lca = v;
					break;
				}
				last_visit[v] = lca_iteration;
				v = par[v];
			}
		}
		// all the vertices of the cycle get compressed by attaching them to the LCA
		for (int x : path_u)
		{
			dsu_2ecc[x] = lca;
			if (x == lca)
				break;
			--bridges;
		}
		for (int x : path_v)
		{
			dsu_2ecc[x] = lca;
			if (x == lca)
				break;
			--bridges;
		}
	}
	void add_edge(int u, int v)
	{
		int x = u, y = v;
		u = find_2ecc(u);
		v = find_2ecc(v);
		// if they are already in the same 2-edge-connected component, then return immediately
		if (u == v)
			return;

		// now check if they are in the same bridge tree
		int comp_u = find_cc(u);
		int comp_v = find_cc(v);

		if (comp_u != comp_v)
		{
			++bridges;
			if (dsu_cc_size[comp_u] > dsu_cc_size[comp_v])
			{
				swap(u, v);
				swap(comp_u, comp_v);
			}
			make_root(u);
			par[u] = dsu_cc[u] = v;
			dsu_cc_size[comp_v] += dsu_cc_size[u];
		}
		else
		{
			merge_path(u, v);
		}
	}
} online_bridge;

int main()
{
	int n, q;
	cin >> n >> q;
	online_bridge = OnlineBridge(n);
	while (q--)
	{
		int u, v;
		cin >> u >> v;
		online_bridge.add_edge(u, v);
		cout << online_bridge.bridges << '\n';
	}
	return 0;
}
// https://cp-algorithms.com/graph/bridge-searching-online.html