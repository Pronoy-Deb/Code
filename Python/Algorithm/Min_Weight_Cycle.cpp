// Minimum Mean Weight Cycle:

#include <bits/stdc++.h>
using namespace std;

const int N = 26 * 27;

vector<pair<int, int>> g[N];
bool vis[N];
double d[N];
bool spfa(int u, double x)
{
    vis[u] = 1;
    for (auto e : g[u])
    {
        double w = -x + e.second;
        int v = e.first;
        if (d[u] + w > d[v])
        { // d[u] + w < d[v] for minimum mean weight
            if (vis[v])
                return 0;
            d[v] = d[u] + w;
            if (!spfa(v, x))
                return 0;
        }
    }
    vis[u] = 0;
    return 1;
}

bool ok(int n, double x)
{
    for (int i = 1; i <= n; i++)
        d[i] = 0, vis[i] = 0;
    for (int s = 1; s <= n; s++)
    {
        if (!spfa(s, x))
            return 1;
    }
    return 0;
}
void add_edge(char a, char b, char c, char d, int w)
{
    int u = (a - 'a') * 26 + (b - 'a' + 1);
    int v = (c - 'a') * 26 + (d - 'a' + 1);
    g[u].push_back({v, w});
}
// this code is for MAXIMUM mean weight cycle
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    while (cin >> n && n)
    {
        for (int i = 1; i <= n; i++)
        {
            string s;
            cin >> s;
            int len = s.size();
            if (len < 2)
                continue;
            add_edge(s[0], s[1], s[len - 2], s[len - 1], len);
        }
        int n = 26 * 26;
        double l = 0, r = 1010;
        int it = 200;
        while (it--)
        {
            double mid = (l + r) * 0.5;
            if (ok(n, mid))
                l = mid; // r = mid for minimum
            else
                r = mid; // l = mid = for minimum
        }
        if (l == 0.0)
            cout << "No solution.\n"; // l = 1010.0 for mimimum
        else
            cout << fixed << setprecision(2) << l << '\n';
        for (int i = 0; i < N; i++)
            g[i].clear();
    }
    return 0;
}
// https://www.spoj.com/problems/WORDRING/

// Minimum Weight Cycle for Each Edge:

#include <bits/stdc++.h>
using namespace std;

const int N = 205, inf = 1e9;

int d[N], vis[N], par[N];
int g[N][N], ans[N * N], last[N], dp[N * N], id[N][N], W[N * N];
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t, cs = 0;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                g[i][j] = inf;
            }
        }
        for (int i = 1; i <= m; i++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            ++u;
            ++v;
            g[u][v] = g[v][u] = w;
            id[u][v] = id[v][u] = i;
            ans[i] = inf;
            W[i] = w;
        }
        for (int u = 1; u <= n; u++)
        {
            memset(vis, 0, sizeof vis);
            for (int i = 0; i <= n; i++)
            {
                d[i] = inf;
                par[i] = i;
                last[i] = -1;
            }
            for (int i = 1; i <= m; i++)
            {
                dp[i] = inf;
            }
            d[u] = 0;
            par[u] = u;
            last[u] = 0;
            while (1)
            {
                int cur = 0;
                for (int i = 1; i <= n; i++)
                {
                    if (!vis[i] and d[i] < d[cur])
                    {
                        cur = i;
                    }
                }
                if (cur == 0)
                    break;
                if (vis[cur])
                    break;
                vis[cur] = 1;
                if (par[cur] != cur)
                {
                    dp[id[last[cur]][cur]] = min(dp[id[last[cur]][cur]], d[cur] + g[cur][u]);
                    ans[id[cur][u]] = min(ans[id[cur][u]], d[cur] + g[cur][u]);
                    ans[id[u][cur]] = min(ans[id[u][cur]], d[cur] + g[cur][u]);
                }
                for (int i = 1; i <= n; i++)
                {
                    if (i != u)
                    {
                        if (vis[i])
                        {
                            if (par[i] != par[cur])
                            {
                                dp[id[last[cur]][cur]] = min(dp[id[last[cur]][cur]], d[cur] + d[i] + g[cur][i]);
                                dp[id[last[i]][i]] = min(dp[id[last[i]][i]], d[cur] + d[i] + g[cur][i]);
                                ans[id[cur][i]] = min(ans[id[cur][i]], d[cur] + d[i] + g[cur][i]);
                                ans[id[i][cur]] = min(ans[id[i][cur]], d[cur] + d[i] + g[cur][i]);
                            }
                        }
                        else if (d[cur] + g[cur][i] < d[i])
                        {
                            d[i] = d[cur] + g[cur][i];
                            last[i] = cur;
                            if (cur == u)
                            {
                                par[i] = i;
                            }
                            else
                            {
                                par[i] = par[cur];
                            }
                        }
                    }
                }
            }
            for (int i = 1; i <= n; i++)
            {
                if (last[i] == -1)
                    continue;
                int x = dp[id[last[i]][i]];
                for (int cur = i; cur; cur = last[cur])
                {
                    if (last[cur])
                    {
                        dp[id[last[cur]][cur]] = min(dp[id[last[cur]][cur]], x);
                    }
                }
            }
            for (int i = 1; i <= m; i++)
            {
                ans[i] = min(ans[i], dp[i]);
            }
        }
        cout << "Case " << ++cs << ":\n";
        for (int i = 1; i <= m; i++)
        {
            if (ans[i] == inf)
                cout << "impossible\n";
            else
                cout << ans[i] - W[i] + 1 << '\n';
        }
    }
    return 0;
}
// https://lightoj.com/contest/loj-homecoming/arena/problem/14

// Minimum Weight Cycle for Each Vertex:

#include <bits/stdc++.h>
using namespace std;

const int N = 305, inf = 1e9;

int g[N][N], d[N], vis[N], par[N];
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> g[i][j];
            if (g[i][j] == -1)
            {
                g[i][j] = inf;
            }
        }
    }
    for (int u = 1; u <= n; u++)
    {
        memset(vis, 0, sizeof vis);
        for (int i = 0; i <= n; i++)
        {
            d[i] = inf;
            par[i] = i;
        }
        d[u] = 0;
        par[u] = u;
        int ans = inf;
        while (1)
        {
            int cur = 0;
            for (int i = 1; i <= n; i++)
            {
                if (!vis[i] and d[i] < d[cur])
                {
                    cur = i;
                }
            }
            if (cur == 0)
                break;
            if (vis[cur])
                break;
            vis[cur] = 1;
            if (par[cur] != cur)
            {
                ans = min(ans, d[cur] + g[cur][u]);
            }
            for (int i = 1; i <= n; i++)
            {
                if (i != u)
                {
                    if (vis[i])
                    {
                        if (par[i] != par[cur])
                        {
                            ans = min(ans, d[cur] + d[i] + g[cur][i]);
                        }
                    }
                    else if (d[cur] + g[cur][i] < d[i])
                    {
                        d[i] = d[cur] + g[cur][i];
                        if (cur == u)
                        {
                            par[i] = i;
                        }
                        else
                        {
                            par[i] = par[cur];
                        }
                    }
                }
            }
        }
        if (ans == inf)
            ans = -1;
        cout << ans << '\n';
    }
    return 0;
}
// https://codeforces.com/gym/100917/problem/F