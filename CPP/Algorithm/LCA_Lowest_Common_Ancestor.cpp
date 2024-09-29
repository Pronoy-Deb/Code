// Sparse Table Approach: O(1)

const int L = 20;
vector<int> tre[N]; int anc[N][L], lvl[N];
void dfs(int u, int par = 0) {
	lvl[u] = lvl[par] + 1; anc[u][0] = par;
	for (int k = 1; k < L; ++k) anc[u][k] = anc[anc[u][k - 1]][k - 1];
	for (auto &v : tre[u]) {
		if (v != par) dfs(v, u);
	}
}
int lca(int u, int v) {
	if (lvl[u] > lvl[v]) swap(u, v);
	for (int k = L - 1; k >= 0; --k) {
		if (lvl[u] + (1ll << k) <= lvl[v]) v = anc[v][k];
	}
	if (u == v) return u;
	for (int k = L - 1; k >= 0; --k) {
		if (anc[u][k] != anc[v][k]) u = anc[u][k], v = anc[v][k];
	}
	return anc[u][0];
}
int getanc(int u, int d) {
	for (int k = 0; k < L; ++k) {
		if (d & (1ll << k)) u = anc[u][k];
	}
	return u;
}
int dis(int u, int v) {
	int g = lca(u, v); return lvl[u] + lvl[v] - (lvl[g] << 1);
}

// Operation:
	cin >> n;
	for (i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		tre[u].push_back(v); tre[v].push_back(u);
	}
	dfs(1);

// OR,

const int L = 20;
vector<int> tre[N]; int par[N][L], dep[N], sz[N];
void dfs(int u, int p = 0) {
	par[u][0] = p; dep[u] = dep[p] + 1; sz[u] = 1;
	for (int i = 1; i < L; ++i) par[u][i] = par[par[u][i - 1]][i - 1];
	for (auto &v : tre[u]) {
		if (v != p) {
			dfs(v, u); sz[u] += sz[v];
		}
	}
}
int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	for (int k = L - 1; k >= 0; --k) {
		if (dep[par[u][k]] >= dep[v]) u = par[u][k];
	}
	if (u == v) return u;
	for (int k = L - 1; k >= 0; --k) {
		if (par[u][k] != par[v][k]) u = par[u][k], v = par[v][k];
	}
	return par[u][0];
}
int dis(int u, int v) {
	int l = lca(u, v); return dep[u] + dep[v] - (dep[l] << 1);
}
int go(int u, int k) {
	assert(k >= 0);
	for (int i = 0; i < L; ++i) {
		if (k & (1 << i)) u = par[u][i];
	}
	return u;
}
// kth node from u to v, 0th node is u
int kth(int u, int v, int k) {
	int l = lca(u, v), d = dep[u] + dep[v] - (dep[l] << 1);
	assert(k <= d);
	if (dep[l] + k <= dep[u]) return go(u, k);
	k -= dep[u] - dep[l]; return go(v, dep[v] - dep[l] - k);
}

// Operation:
	cin >> n;
	for (i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		tre[u].push_back(v); tre[v].push_back(u);
	}
	dfs(1);
	int q; cin >> q;
	while (q--) {
		int u, v; cin >> u >> v;
		cout << dis(u, v) << '\n';
	}

// OR, Comlexity: O(V + E)

vector<int> tre[N]; int par[N];
void dfs(int vr, int p = -1) {
	par[vr] = p;
	for (auto &cld : tre[vr]) {
		if (cld != p) dfs(cld, vr);
	}
}
auto path(int vr) {
	vector<int> ans;
	while (vr != -1) { ans.push_back(vr); vr = par[vr]; }
	reverse(ans.begin(), ans.end()); return ans;
}

// Operation:
	int vr; cin >> vr;
	for (i = 0; i < vr - 1; ++i) {
		int v1, v2; cin >> v1 >> v2;
		tre[v1].push_back(v2); tre[v2].push_back(v1);
	}
	dfs(1);
	int n1, n2; cin >> n1 >> n2;
	vector<int> pn1 = path(n1), pn2 = path(n2);
	int lca = -1, mn = min((int)pn1.size(), (int)pn2.size());
	for (i = 0; i < mn and pn1[i] == pn2[i]; ++i) lca = pn1[i];
	cout << lca;

// OR,
/*
 * LCA in O(1)
 * depth calculates weighted distance
 * lvl calculates distance by number of edges
 * Preprocessing in N*log(N)
 */

const int L = 21;
long long dep[N], lvl[N], st[N], en[N], LOG[N], par[N], a[N], id[N], tab[L][N], n, rt, Time, cur;
vector<pair<int, long long>> tre[N];
void pre(int nodes, int root_) {
	n = nodes, rt = root_, LOG[0] = LOG[1] = 0;
	for (int i = 2; i <= n; ++i) LOG[i] = LOG[i >> 1] + 1;
	// for (int i = 0; i <= n; ++i) tre[i].clear();
}
int lca(int u, int v) {
	if (en[u] > en[v]) swap(u, v);
	if (st[v] <= st[u] && en[u] <= en[v]) return v;
	int l = LOG[id[v] - id[u] + 1];
	int p1 = id[u], p2 = id[v] - (1ll << l) + 1;
	int d1 = lvl[tab[l][p1]], d2 = lvl[tab[l][p2]];
	if (d1 < d2) return par[tab[l][p1]];
	else return par[tab[l][p2]];
}
int dis(int u, int v) {
	int l = lca(u, v); return (dep[u] + dep[v] - (dep[l] << 1));
}
/* Euler tour */
void dfs(int u, int p) {
	st[u] = ++Time, par[u] = p;
	for (auto &[v, w] : tre[u]) {
		if (v != p) {
			dep[v] = dep[u] + w; lvl[v] = lvl[u] + 1; dfs(v, u);
		}
	}
	en[u] = ++Time; a[++cur] = u, id[u] = cur;
}
/* RMQ */
void cal() {
	cur = Time = 0, dfs(rt, rt);
	for (int i = 1; i <= n; ++i) tab[0][i] = a[i];
	for (int l = 0; l < L - 1; ++l) {
		for (int i = 1; i <= n; ++i) {
			tab[l + 1][i] = tab[l][i];
			bool C1 = (1ll << l) + i <= n;
			bool C2 = lvl[tab[l][i + (1ll << l)]] < lvl[tab[l][i]];
			if (C1 && C2) tab[l + 1][i] = tab[l][i + (1ll << l)];
		}
	}
}
// tested on kattis-greatestpair

// OR,

template <class T>
struct RMQ
{ // 0-based
	vector<vector<T>> rmq;
	T kInf = numeric_limits<T>::max();
	void build(const vector<T> &V)
	{
		int n = V.size(), on = 1, dep = 1;
		while (on < n)
			on *= 2, ++dep;
		rmq.assign(dep, V);

		for (int i = 0; i < dep - 1; ++i)
			for (int j = 0; j < n; ++j)
			{
				rmq[i + 1][j] = min(rmq[i][j], rmq[i][min(n - 1, j + (1 << i))]);
			}
	}
	T query(int a, int b)
	{ // [a, b)
		if (b <= a)
			return kInf;
		int dep = 31 - __builtin_clz(b - a); // log(b - a)
		return min(rmq[dep][a], rmq[dep][b - (1 << dep)]);
	}
};

struct LCA
{ // 0-based
	vector<int> enter, depth, exxit;
	vector<vector<int>> G;
	vector<pair<int, int>> linear;
	RMQ<pair<int, int>> rmq;
	int timer = 0;
	LCA() {}
	LCA(int n) : enter(n, -1), exxit(n, -1), depth(n), G(n), linear(2 * n) {}
	void dfs(int node, int dep)
	{
		linear[timer] = {dep, node};
		enter[node] = timer++;
		depth[node] = dep;
		for (auto vec : G[node])
			if (enter[vec] == -1)
			{
				dfs(vec, dep + 1);
				linear[timer++] = {dep, node};
			}
		exxit[node] = timer;
	}
	void add_edge(int a, int b)
	{
		G[a].push_back(b);
		G[b].push_back(a);
	}
	void build(int root)
	{
		dfs(root, 0);
		rmq.build(linear);
	}
	int query(int a, int b)
	{
		a = enter[a], b = enter[b];
		return rmq.query(min(a, b), max(a, b) + 1).second;
	}
	int dist(int a, int b)
	{
		return depth[a] + depth[b] - 2 * depth[query(a, b)];
	}
};

LCA lca;

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	return 0;
}