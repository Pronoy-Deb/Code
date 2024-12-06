// Complexity: O(V + E)

vector<long long> gp[N];
bool vis[N];
void dfs(auto root) {
    vis[root] = true;
    for (auto &child : gp[root]) {
        if (vis[child]) continue;
        dfs(child);
    }
}

// Operation:
    long long vr, eg; cin >> vr >> eg;
    for (i = 0; i < eg; ++i) {
        long long v1, v2; cin >> v1 >> v2;
        gp[v1].push_back(v2); gp[v2].push_back(v1);
    }
    long long ct = 0;
    for (i = 1; i <= vr; ++i) {
        if (vis[i]) continue;
        dfs(i); ++ct;
    }
    cout << ct;

// To store the connected components:

vector<long long> gp[N], cur;
bool vis[N];
void dfs(auto root) {
    vis[root] = true;
    cur.push_back(root);
    for (auto &child : gp[root]) {
        if (vis[child]) continue;
        dfs(child);
    }
}

// Operation:
    long long vr, eg; cin >> vr >> eg;
    for (i = 0; i < eg; ++i) {
        long long v1, v2; cin >> v1 >> v2;
        gp[v1].push_back(v2); gp[v2].push_back(v1);
    }
    vector<vector<long long>> cc;
    for (i = 1; i <= vr; ++i) {
        if (vis[i]) continue;
        cur.clear(); dfs(i);
        cc.push_back(cur);
    }
    cout << cc.size() << '\n';
    for (auto &r : cc) {
        for (auto &e : r) cout << e << ' ';
        cout << '\n';
    }

// Connected Components DP:

const int N = 105;
int n, k, a[N], dp[N][N][1005][3];
int yo(int i, int c, int sum, int ends) { //(id, components, sum, borders)
    if (ends > 2 || sum > k) return 0;
    if (c == 0 && i > 1) return 0;
    if (i == n + 1) return ends == 2 && c == 1;
    int &ret = dp[i][c][sum][ends];
    if (ret != -1) return ret;
    int nsum = sum + (a[i] - a[i - 1]) * (2 * c - ends);
    long long ans = 0;
    if (c >= 2) ans += 1LL * (c - 1) * yo(i + 1, c - 1, nsum, ends); // merge two components
    if (c >= 1) ans += 1LL * (2 * c - ends) * yo(i + 1, c, nsum, ends); // add to a component's end
    ans += 1LL * (c + 1 - ends) * yo(i + 1, c + 1, nsum, ends); // create a new component
    if (ends < 2) ans += 1LL * (2 - ends) * yo(i + 1, c + 1, nsum, ends + 1); // create a new end
    if (ends < 2) ans += 1LL * (2 - ends) * yo(i + 1, c, nsum, ends + 1); // extend a component to make it a border
    ans %= M;
    return ret = ans;
}

// Opearation:
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1);
    if (n == 1) return cout << 1 << '\n', 0;
    memset(dp, -1, sizeof dp);
    cout << yo(1, 0, 0, 0) << '\n';

// https://oj.uz/problem/view/JOI16_skyscraper