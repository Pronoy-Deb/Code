https://cses.fi/problemset/task/1131

vector<int> tre[N]; int last, dmr;
void dfs(int vr, int par = 0, int dep = 0) {
    for (auto cld : tre[vr]) {
        if (cld == par) continue;
        if (dmr <= dep) {
            dmr = dep + 1; last = cld;
        }
        dfs(cld, vr, dep + 1);
    }
}

// Operation:
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int a, b; cin >> a >> b;
        tre[a].push_back(b); tre[b].push_back(a);
    }
    dfs(1); dmr = 0; dfs(last); cout << dmr;

https://cses.fi/problemset/task/1132
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 9;

vector<int> g[N];
int farthest(int s, int n, vector<int> &d) {
    static const int inf = N;
    d.assign(n + 1, inf);
    d[s] = 0;
    vector<bool> vis(n + 1);
    queue<int> q;
    q.push(s);
    vis[s] = 1;
    int last = s;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v : g[u])
        {
            if (vis[v])
                continue;
            d[v] = d[u] + 1;
            q.push(v);
            vis[v] = 1;
        }
        last = u;
    }
    return last;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> dx, dy;
    int x = farthest(1, n, dx);
    int y = farthest(x, n, dx);
    farthest(y, n, dy);
    for (int i = 1; i <= n; i++)
    {
        cout << max(dx[i], dy[i]) << ' ';
    }
    cout << '\n';
    return 0;
}