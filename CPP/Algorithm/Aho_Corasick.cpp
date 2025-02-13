// Aho Corasick:

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9;

// credit: Alpha_Q
struct AC
{
    int N, P;
    const int A = 26;
    vector<vector<int>> next;
    vector<int> link, out_link;
    vector<vector<int>> out;
    AC() : N(0), P(0) { node(); }
    int node()
    {
        next.emplace_back(A, 0);
        link.emplace_back(0);
        out_link.emplace_back(0);
        out.emplace_back(0);
        return N++;
    }
    inline int get(char c)
    {
        return c - 'a';
    }
    int add_pattern(const string T)
    {
        int u = 0;
        for (auto c : T)
        {
            if (!next[u][get(c)])
                next[u][get(c)] = node();
            u = next[u][get(c)];
        }
        out[u].push_back(P);
        return P++;
    }
    void compute()
    {
        queue<int> q;
        for (q.push(0); !q.empty();)
        {
            int u = q.front();
            q.pop();
            for (int c = 0; c < A; ++c)
            {
                int v = next[u][c];
                if (!v)
                    next[u][c] = next[link[u]][c];
                else
                {
                    link[v] = u ? next[link[u]][c] : 0;
                    out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];
                    q.push(v);
                }
            }
        }
    }
    int advance(int u, char c)
    {
        while (u && !next[u][get(c)])
            u = link[u];
        u = next[u][get(c)];
        return u;
    }
};

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    auto st = clock();
    int t, cs = 0;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<string> v;
        for (int i = 0; i < n; i++)
        {
            string s;
            cin >> s;
            v.push_back(s);
        }
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        AC aho;
        vector<int> len(n + 3, 0);
        for (auto s : v)
        {
            len[aho.add_pattern(s)] = s.size();
        }
        aho.compute();
        string s; cin >> s;
        n = s.size();
        vector<int> dp(n, n + 10);
        int u = 0;
        for (int i = 0; i < n; i++)
        {
            char c = s[i];
            u = aho.advance(u, c);
            for (int v = u; v; v = aho.out_link[v])
            {
                for (auto p : aho.out[v])
                {
                    dp[i] = min(dp[i], (i - len[p] >= 0 ? dp[i - len[p]] : 0) + 1);
                }
            }
        }
        cout << "Case " << ++cs << ": ";
        if (dp[n - 1] == n + 10)
        {
            cout << "impossible\n";
        }
        else
        {
            cout << dp[n - 1] << '\n';
        }
    }
    cout << 1.0 * (clock() - st) / 1000 << '\n';
    return 0;
}

// Aho Corasick Dynamic:
https://codeforces.com/contest/710/problem/F

struct aho_corasick_static {
    int ct[N], link[N], psz = 0; map<char, int> to[N];
    void clear() {
        for (int i = 0; i < psz; ++i) {
            ct[i] = 0; link[i] = -1; to[i].clear();
        }
        psz = 1; link[0] = -1; ct[0] = 0;
    }
    aho_corasick_static() { psz = N - 2; clear(); }
    void add(string &s) {
        int u = 0;
        for (char c : s) {
            if (!to[u].count(c)) to[u][c] = psz++; u = to[u][c];
        }
        ++ct[u];
    }
    void push_links() {
        queue<int> Q; Q.push(0); link[0] = -1;
        while (!Q.empty()) {
            int u = Q.front(); Q.pop();
            for (auto it : to[u]) {
                int v = it.second, j = link[u]; char c = it.first;
                while (j != -1 && !to[j].count(c)) j = link[j];
                link[v] = (~j ? to[j][c] : 0);
                ct[v] += ct[link[v]]; Q.push(v);
            }
        }
    }
    int cnt(string &p) {
        int u = 0, ans = 0;
        for (char c : p) {
            while (u != -1 && !to[u].count(c)) u = link[u];
            u = (~u ? to[u][c] : 0); ans += ct[u];
        }
        return ans;
    }
};

struct aho {
    vector<string> li[20]; aho_corasick_static ac[20];
    void clear() {
        for (int i = 0; i < 20; ++i) {
            li[i].clear(); ac[i].clear();
        }
    }
    aho() { clear(); }
    void add(string &s) {
        int pos = 0;
        for (int l = 0; l < 20; ++l) {
            if (li[l].empty()) { pos = l; break; }
        }
        li[pos].push_back(s); ac[pos].add(s);
        for (int bef = 0; bef < pos; ++bef) {
            ac[bef].clear();
            for (string &s2 : li[bef]) {
                li[pos].push_back(s2); ac[pos].add(s2);
            }
            li[bef].clear();
        }
        ac[pos].push_links();
    }
    // sum of occurrences of all patterns in this string s
    int cnt(string &s) {
        int ans = 0;
        for (int l = 0; l < 20; ++l) ans += ac[l].cnt(s);
        return ans;
    }
};
aho ins, rem;

// Operation:
    int64_t n; cin >> n;
    while (n--) {
        int ty; string s; cin >> ty >> s;
        if (ty == 1) ins.add(s);
        else if (ty == 2) rem.add(s);
        else cout << ins.cnt(s) - rem.cnt(s) << endl;
    }

// Aho Corasick All Pair Occurrence Relation:

#include <bits/stdc++.h>
using namespace std;

const int N = 755, L = 1e7 + 9;
bool reach[N][N];
struct AhoCorasick
{
    // caution: change 2 to 26 for normal strings
    int link[L], sz, to[L][2], dp[L][2], term[L], last[L]; // each string contains 'a' and 'b'
    AhoCorasick()
    {
        memset(link, 0, sizeof link);
        memset(to, 0, sizeof to);
        memset(dp, -1, sizeof dp);
        memset(term, 0, sizeof term);
        memset(last, 0, sizeof last);
        sz = 1;
    }
    void insert(string &s, int id)
    {
        int u = 0;
        for (char c : s)
        {
            if (!to[u][c - 'a'])
                to[u][c - 'a'] = sz++;
            u = to[u][c - 'a'];
        }
        term[u] = id;
    }
    void push_links()
    {
        queue<int> q;
        q.push(0);
        link[0] = -1;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            // caution: change 2 to 26 for normal strings
            for (int c = 0; c < 2; c++)
            {
                int v = to[u][c];
                if (!v)
                    continue;
                int j = link[u];
                while (j != -1 && !to[j][c])
                    j = link[j];
                if (j != -1)
                    link[v] = to[j][c];
                else
                    link[v] = 0;
                if (!term[link[v]])
                    last[v] = last[link[v]];
                else
                    last[v] = link[v];
                q.push(v);
            }
        }
    }
    int go(int v, char ch)
    {
        int c = ch - 'a';
        if (dp[v][c] == -1)
        {
            if (to[v][c])
                return dp[v][c] = to[v][c];
            return dp[v][c] = (v == 0 ? 0 : go(link[v], ch));
        }
        return dp[v][c];
    }
    void traverse(string &s, int id)
    {
        int n = s.size(), cur = 0;
        for (int i = 0; i < n; i++)
        {
            cur = go(cur, s[i]);
            if (term[cur] && term[cur] != id)
                reach[term[cur]][id] = 1;
            else
                reach[term[last[cur]]][id] = 1;
        }
    }
} t;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct Kuhn
{
    int n;
    vector<vector<int>> g;
    vector<int> l, r;
    vector<bool> vis;
    Kuhn() {}
    Kuhn(int _n, int _m)
    {
        n = _n;
        g.resize(n + 1);
        vis.resize(n + 1, false);
        l.resize(n + 1, -1);
        r.resize(_m + 1, -1);
    }
    void add_edge(int a, int b)
    {
        g[a].push_back(b);
    }
    bool yo(int u)
    {
        if (vis[u])
            return false;
        vis[u] = true;
        for (auto v : g[u])
        {
            if (r[v] == -1 || yo(r[v]))
            {
                l[u] = v;
                r[v] = u;
                return true;
            }
        }
        return false;
    }
    int maximum_matching()
    {
        for (int i = 1; i <= n; i++)
            shuffle(g[i].begin(), g[i].end(), rnd);
        vector<int> p(n);
        iota(p.begin(), p.end(), 1);
        shuffle(p.begin(), p.end(), rnd);
        bool ok = true;
        while (ok)
        {
            ok = false;
            vis.assign(n + 1, false);
            for (auto &i : p)
                if (l[i] == -1)
                    ok |= yo(i);
        }
        int ans = 0;
        for (int i = 1; i <= n; i++)
            ans += l[i] != -1;
        return ans;
    }
} M;
bool vis[N][2];
vector<int> g[N];
bool vc[N];
void dfs(int u, int side)
{
    if (vis[u][side])
        return;
    vis[u][side] = 1;
    if (side == 0)
    {
        for (auto v : g[u])
        {
            dfs(v, 1);
        }
    }
    else
        dfs(M.r[u], 0);
}
string s[N]; // it assumes all strings are distinct
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        t.insert(s[i], i);
    }
    t.push_links();
    for (int i = 1; i <= n; i++)
        t.traverse(s[i], i);
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                reach[i][j] |= reach[i][k] & reach[k][j];
            }
        }
    }
    M = Kuhn(n, n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (reach[i][j])
            {
                M.add_edge(i, j);
                g[i].push_back(j);
            }
        }
    }
    int p = M.maximum_matching();
    for (int i = 1; i <= n; i++)
        if (M.l[i] == -1)
            dfs(i, 0);
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i][0] || vis[i][1])
            vc[i] = 1;
    }
    cout << n - p << '\n';
    for (int i = 1; i <= n; i++)
    {
        if (!vc[i])
            cout << i << ' ';
    }
    cout << '\n';
    return 0;
}
// https://codeforces.com/contest/590/problem/E
