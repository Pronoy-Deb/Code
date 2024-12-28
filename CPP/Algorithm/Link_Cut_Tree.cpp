https://www.codechef.com/problems/QTREE6

struct node {
    int p = 0, c[2] = {0, 0}, pp = 0;
    bool flip = 0; int sz = 0, ssz = 0, vsz = 0; // sz -> aux tree size, ssz = subtree size in rep tree, vsz = virtual tree size
    long long val = 0, sum = 0, lazy = 0, subsum = 0, vsum = 0;
    node() {}
    node(int x) {
        val = sum = subsum = x; sz = ssz = 1; lazy = vsz = vsum = 0;
    }
};
struct lct {
    vector<node> tre;
    lct() {}
    lct(int n) : tre(n + 1) {}
    int dir(int x, int y) { return tre[x].c[1] == y; }
    void set(int x, int d, int y) {
        if (x) tre[x].c[d] = y, pull(x);
        if (y) tre[y].p = x;
    }
    void pull(int x) {
        if (!x) return; int &l = tre[x].c[0], &r = tre[x].c[1];
        push(l); push(r);
        tre[x].sum = tre[l].sum + tre[r].sum + tre[x].val;
        tre[x].sz = tre[l].sz + tre[r].sz + 1;
        tre[x].ssz = tre[l].ssz + tre[r].ssz + tre[x].vsz + 1;
        tre[x].subsum = tre[l].subsum + tre[r].subsum + tre[x].vsum + tre[x].val;
    }
    void push(int x) {
        if (!x) return; int &l = tre[x].c[0], &r = tre[x].c[1];
        if (tre[x].flip) {
            swap(l, r); if (l) tre[l].flip ^= 1;
            if (r) tre[r].flip ^= 1; tre[x].flip = 0;
        }
        if (tre[x].lazy) {
            tre[x].val += tre[x].lazy;
            tre[x].sum += tre[x].lazy * tre[x].sz;
            tre[x].subsum += tre[x].lazy * tre[x].ssz;
            tre[x].vsum += tre[x].lazy * tre[x].vsz;
            if (l) tre[l].lazy += tre[x].lazy;
            if (r) tre[r].lazy += tre[x].lazy;
            tre[x].lazy = 0;
        }
    }
    void rotate(int x, int d) {
        int y = tre[x].p, z = tre[y].p, w = tre[x].c[d];
        swap(tre[x].pp, tre[y].pp); set(y, !d, w);
        set(x, d, y); set(z, dir(z, y), x);
    }
    void splay(int x) {
        for (push(x); tre[x].p;) {
            int y = tre[x].p, z = tre[y].p;
            push(z); push(y); push(x);
            int dx = dir(y, x), dy = dir(z, y);
            if (!z) rotate(x, !dx);
            else if (dx == dy) rotate(y, !dx), rotate(x, !dx);
            else rotate(x, dy), rotate(x, dx);
        }
    }
    // making it a root in the rep. tree
    void make_root(int u) {
        access(u); int l = tre[u].c[0]; tre[l].flip ^= 1;
        swap(tre[l].p, tre[l].pp); tre[u].vsz += tre[l].ssz;
        tre[u].vsum += tre[l].subsum; set(u, 0, 0);
    }
    // make the path from root to u a preferred path
    // returns last path-parent of a node as it moves up the tree
    int access(int _u) {
        int last = _u;
        for (int v = 0, u = _u; u; u = tre[v = u].pp) {
            splay(u); splay(v); tre[u].vsz -= tre[v].ssz;
            tre[u].vsum -= tre[v].subsum; int r = tre[u].c[1];
            tre[u].vsz += tre[r].ssz; tre[u].vsum += tre[r].subsum;
            tre[v].pp = 0; swap(tre[r].p, tre[r].pp); set(u, 1, v); last = u;
        }
        splay(_u); return last;
    }
    void link(int u, int v) { // add edge u -- v
        // assert(!connected(u, v));
        make_root(v); access(u); splay(u); tre[v].pp = u;
        tre[u].vsz += tre[v].ssz; tre[u].vsum += tre[v].subsum;
    }
    void cut(int u) { // remove par[u] -- u, u is non root vertex
        access(u); assert(tre[u].c[0] != 0);
        tre[tre[u].c[0]].p = 0; tre[u].c[0] = 0; pull(u);
    }
    void cut(int u, int v) { // remove edge u -- v
        // assert(connected(u, v));
        make_root(u); access(v); tre[v].c[0] = tre[u].p = 0;
        tre[v].vsz -= tre[u].ssz; tre[v].vsum -= tre[u].subsum; pull(v);
    }
    // parent of u in the rep. tree
    int get_parent(int u) {
        access(u); splay(u); push(u); u = tre[u].c[0]; push(u);
        while (tre[u].c[1]) { u = tre[u].c[1]; push(u); }
        splay(u); return u;
    }
    // root of the rep. tree containing this node
    int find_root(int u) {
        access(u); splay(u); push(u);
        while (tre[u].c[0]) {
            u = tre[u].c[0]; push(u);
        }
        splay(u); return u;
    }
    bool connected(int u, int v) {
        return find_root(u) == find_root(v);
    }
    // depth in the rep. tree
    int depth(int u) {
        access(u); splay(u); return tre[u].sz;
    }
    int lca(int u, int v) {
        // assert(connected(u, v));
        if (u == v) return u;
        if (depth(u) > depth(v)) swap(u, v);
        access(v); return access(u);
    }
    int is_root(int u) { return get_parent(u) == 0; }
    int component_size(int u) { return tre[find_root(u)].ssz; }
    int subtree_size(int u) {
        int p = get_parent(u);
        if (p == 0) return component_size(u); cut(u);
        int ans = component_size(u); link(p, u); return ans;
    }
    long long component_sum(int u) {
        return tre[find_root(u)].subsum;
    }
    long long subtree_sum(int u) {
        int p = get_parent(u);
        if (p == 0) return component_sum(u); cut(u);
        long long ans = component_sum(u); link(p, u); return ans;
    }
    // sum of the subtree of u when root is specified
    long long subtree_query(int u, int root) {
        int cur = find_root(u); make_root(root);
        long long ans = subtree_sum(u); make_root(cur); return ans;
    }
    // path sum
    long long query(int u, int v) {
        int cur = find_root(u); make_root(u); access(v);
        long long ans = tre[v].sum; make_root(cur); return ans;
    }
    void upd(int u, int x) {
        access(u); splay(u); tre[u].val += x;
    }
    // add x to the nodes on the path from u to v
    void upd(int u, int v, int x) {
        int cur = find_root(u); make_root(u);
        access(v); tre[v].lazy += x; make_root(cur);
    }
} t[2];
vector<int> gp[N]; int par[N], col[N];
void dfs(int u, int p = 0) {
    par[u] = p;
    for (auto v : gp[u]) {
        if (v ^ p) dfs(v, u);
    }
}

// Operation:
    int n; cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        gp[u].push_back(v); gp[v].push_back(u);
    }
    dfs(1, n + 1); t[0] = lct(n + 1); t[1] = lct(n + 1);
    for (int i = 1; i <= n + 1; ++i) {
        t[0].tre[i] = node(i); t[1].tre[i] = node(i);
    }
    for (int i = 1; i <= n; ++i) t[0].link(par[i], i);
    int q; cin >> q;
    while (q--) {
        int ty, u; cin >> ty >> u;
        if (!ty) {
            int z = t[col[u]].find_root(u);
            int c = t[col[u]].tre[z].c[1];
            cout << t[col[u]].tre[c].ssz << '\n';
        } else {
            t[col[u]].cut(u); col[u] ^= 1;
            t[col[u]].link(par[u], u);
        }
    }

https://www.spoj.com/problems/DYNACON1/
// struct lct {}; // no t array
// Operation:
    int n, q; cin >> n >> q;
    lct t(n);
    for (int i = 1; i <= n; ++i) t.tre[i] = node(i);
    while (q--) {
        string s; cin >> s; int u, v; cin >> u >> v;
        if (s == "add") {
            if (!t.connected(u, v)) t.link(u, v);
        }
        else if (s == "rem") {
            if (t.connected(u, v)) t.cut(u, v);
        }
        else ps(t.connected(u, v));
    }
