// Permutation Generation:
// Complexity: O(n!)
// Printing all permutations of a sorted sequence in ascending order:

vector<long long> v = {1, 2, 3};
sort(v.begin(), v.end());
do
{
    for (auto &i : v)
        cout << i << ' ';
    cout << '\n';
} while (next_permutation(v.begin(), v.end()));

// Printing all permutations of a sorted sequence in descending order:

vector<long long> v = {3, 2, 1};
sort(v.begin(), v.end(), greater());
do
{
    for (auto &i : v)
        cout << i << ' ';
    cout << '\n';
} while (prev_permutation(v.begin(), v.end()));

// Comparing whether permutation or not:

vector<long long> v = {5, 2, 4, 3, 1}, v1 = {4, 3, 2, 5, 1};
cout << is_permutation(v.begin(), v.end(), begin(v1));

// Permutation Tree:
const int N = 1e5 + 9, inf = 1e9 + 7, LG = 19;

struct ST
{
#define lc (n << 1)
#define rc ((n << 1) | 1)
    int tre[N << 2], lz[N << 2];
    ST() {}
    inline void push(int n, int b, int e)
    {
        if (lz[n] == 0)
            return;
        tre[n] = tre[n] + lz[n];
        if (b != e)
        {
            lz[lc] = lz[lc] + lz[n];
            lz[rc] = lz[rc] + lz[n];
        }
        lz[n] = 0;
    }
    inline int combine(int a, int b) { return min(a, b); }
    inline void pull(int n) { tre[n] = min(tre[lc], tre[rc]); }
    void make(int n, int b, int e)
    {
        lz[n] = 0;
        if (b == e)
        {
            tre[n] = 0;
            return;
        }
        int mid = (b + e) >> 1;
        make(lc, b, mid);
        make(rc, mid + 1, e);
        pull(n);
    }
    void up(int n, int b, int e, int i, int j, int v)
    {
        push(n, b, e);
        if (j < b || e < i)
            return;
        if (i <= b && e <= j)
        {
            lz[n] = v;
            push(n, b, e);
            return;
        }
        int mid = (b + e) >> 1;
        up(lc, b, mid, i, j, v);
        up(rc, mid + 1, e, i, j, v);
        pull(n);
    }
    int query(int n, int b, int e, int i, int j)
    {
        push(n, b, e);
        if (i > e || b > j)
            return inf;
        if (i <= b && e <= j)
            return tre[n];
        int mid = (b + e) >> 1;
        return combine(query(lc, b, mid, i, j), query(rc, mid + 1, e, i, j));
    }
} t;
// id of span {i, i} is i
int p[N];
pair<int, int> range[N << 1]; // range of permutation values
pair<int, int> span[N << 1];  // range of permutation indices
vector<int> ptre[N << 1];     // directed permutation tree
int par[N << 1], ty[N << 1];  // 0 if cut node and 1 if increasing join node, 2 if decreasing join node
int id;                       // new index to assign to nodes
pair<int, int> get_range(pair<int, int> x, pair<int, int> y)
{
    return pair<int, int>(min(x.first, y.first), max(x.second, y.second));
}
void add(int u, int v)
{ // u is parent of v
    par[v] = u;
    ptre[u].push_back(v);
}
bool adjacent(int i, int j)
{
    return range[i].second == range[j].first - 1;
}
int length(int i)
{
    return range[i].second - range[i].first + 1;
}
// leaf node is a cut node
int make(int n)
{ // returns root of the tree
    for (int i = 1; i <= (n << 1); ++i)
    {
        ptre[i].clear();
        ty[i] = 0;
        par[i] = -1;
    }
    id = n + 1;
    t.make(1, 1, n);
    vector<int> mx = {0}, mn = {0};
    vector<int> nodes; // stack of cut and join nodes
    for (int i = 1; i <= n; ++i)
    {
        while (mx.back() != 0 && p[mx.back()] < p[i])
        {
            int r = mx.back();
            mx.pop_back();
            t.up(1, 1, n, mx.back() + 1, r, p[i] - p[r]);
        }
        mx.push_back(i);
        while (mn.back() != 0 && p[mn.back()] > p[i])
        {
            int r = mn.back();
            mn.pop_back();
            t.up(1, 1, n, mn.back() + 1, r, p[r] - p[i]);
        }
        // handle stack updates
        mn.push_back(i);
        range[i] = {p[i], p[i]};
        span[i] = {i, i};
        int cur = i;
        while (true)
        {
            if (!nodes.empty() && (adjacent(nodes.back(), cur) || adjacent(cur, nodes.back())))
            {
                if ((adjacent(nodes.back(), cur) && ty[nodes.back()] == 1) ||
                    (adjacent(cur, nodes.back()) && ty[nodes.back()] == 2))
                {
                    add(nodes.back(), cur);
                    range[nodes.back()] = get_range(range[nodes.back()], range[cur]);
                    span[nodes.back()] = get_range(span[nodes.back()], span[cur]);
                    cur = nodes.back();
                    nodes.pop_back();
                }
                else
                { // make a new join node
                    ty[id] = (adjacent(nodes.back(), cur) ? 1 : 2);
                    add(id, nodes.back());
                    add(id, cur);
                    range[id] = get_range(range[nodes.back()], range[cur]);
                    span[id] = get_range(span[nodes.back()], span[cur]);
                    nodes.pop_back();
                    cur = id++;
                }
            }
            else if (i - (length(cur) - 1) && t.query(1, 1, n, 1, i - length(cur)) == 0)
            {
                int len = length(cur);
                pair<int, int> r = range[cur], s = span[cur];
                add(id, cur);
                do
                {
                    len += length(nodes.back());
                    r = get_range(r, range[nodes.back()]);
                    s = get_range(s, span[nodes.back()]);
                    add(id, nodes.back());
                    nodes.pop_back();
                } while (r.second - r.first + 1 != len);
                reverse(ptre[id].begin(), ptre[id].end());
                range[id] = r;
                span[id] = s;
                cur = id++;
            }
            else
                break;
        }
        nodes.push_back(cur);
        t.up(1, 1, n, 1, i, -1);
    }
    id--;
    assert(id <= (n << 1));
    int r = 0;
    for (int i = 1; i <= id; ++i)
    {
        if (par[i] == -1)
            r = i;
    }
    assert(r);
    return r;
}
int P[N << 1][LG];
void dfs(int u, int p = 0)
{
    P[u][0] = p;
    for (int k = 1; k < LG; ++k)
        P[u][k] = P[P[u][k - 1]][k - 1];
    for (auto &v : ptre[u])
    {
        if (v == p)
            continue;
        dfs(v, u);
    }
}

// Operation:
cin >> n;
for (i = 1; i <= n; ++i)
    cin >> p[i];
int r = make(n);
dfs(r);
cin >> q;
while (q--)
{
    int l, r;
    cin >> l >> r;
    if (l == r)
    {
        cout << l << ' ' << r << '\n';
        continue;
    }
    int u = l;
    for (k = LG - 1; k >= 0; --k)
    {
        if (P[u][k] && span[P[u][k]].second < r)
            u = P[u][k];
    }
    u = P[u][0];
    if (ty[u] == 0)
    {
        cout << span[u].first << ' ' << span[u].second << '\n';
        continue;
    }
    int curl = -1, curr = ptre[u].size();
    for (k = LG - 1; k >= 0; --k)
    {
        if (curl + (1 << k) < ptre[u].size() && span[ptre[u][curl + (1 << k)]].second < l)
            curl += 1 << k;
        if (curr - (1 << k) >= 0 && r < span[ptre[u][curr - (1 << k)]].first)
            curr -= 1 << k;
    }
    cout << span[ptre[u][curl + 1]].first << ' ' << span[ptre[u][curr - 1]].second << '\n';
}

// https://codeforces.com/gym/101620, Problem I
// https://codeforces.com/blog/entry/78898

// Permutation Cycles:

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

// 0-indexed, values are also from 0 to n-1

// decompose into cycles
vector<vector<int>> decompose(vector<int> &p)
{
    int n = p.size();
    vector<vector<int>> cycles;
    vector<bool> vis(n, 0);
    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
        {
            vector<int> v;
            while (!vis[i])
            {
                v.push_back(i);
                vis[i] = 1;
                i = p[i];
            }
            cycles.push_back(v);
        }
    }
    return cycles;
}

// restore the permutation from the cycles
vector<int> restore(int n, vector<vector<int>> &cycles)
{
    vector<int> p(n);
    for (auto v : cycles)
    {
        int m = v.size();
        for (int i = 0; i < m; i++)
            p[v[i]] = v[(i + 1) % m];
    }
    return p;
}

// cycle decomposition of the k-th power of p
vector<vector<int>> power(vector<int> &p, int k)
{
    int n = p.size();
    auto cycles = decompose(p);
    vector<vector<int>> ans;
    for (auto v : cycles)
    {
        int len = v.size(), g = __gcd(k, len); // g cycles of len / g length
        for (int i = 0; i < g; i++)
        {
            vector<int> w;
            for (int j = i, cnt = 0; cnt < len / g; cnt++, j = (j + k) % len)
            {
                w.push_back(v[j]);
            }
            ans.push_back(w);
        }
    }
    return ans;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++)
    {
        cin >> p[i];
        --p[i];
    }
    auto cycles = decompose(p);
    int ans = 1;
    for (auto v : cycles)
    {
        int sz = v.size();
        ans = 1LL * ans * sz / __gcd(ans, sz);
    }
    cout << ans << '\n';
    return 0;
}
// https://acm.timus.ru/problem.aspx?space=1&num=1024