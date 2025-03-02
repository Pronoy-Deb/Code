//

struct atm { int64_t d, p, r, g; };

int64_t n, c, d, dp[N]; vector<atm> at;
inline int64_t eval(auto &p, int64_t v) { return p.first * v + p.second; }
bool check(auto &a, auto &b, auto &c) {
    return (__int128)(b.second - a.second) * (b.first - c.first) <= (__int128)(c.second - b.second) * (a.first - b.first);
}
void add(auto &v, auto l) {
    while ((int)v.size() >= 2 && check(l, v[v.size() - 1], v[v.size() - 2])) v.pop_back();
    v.push_back(l);
}
vector<pair<int64_t, int64_t> > cdq(int l, int r) {
    if (l + 1 == r) {
        if (dp[l] >= 0) return ; else return {};
    }
    int m = (l + r) >> 1;
    vector<pair<int64_t, int64_t> > l1 = cdq(l, m);
    for (int i = m, j = 0 ; l1.size() && i < r ; ++i) {
        while (j + 1 < (int)l1.size() && eval(l1[j], at[i].d) < eval(l1[j + 1], at[i].d)) ++j;
        dp[i] = max(dp[i], eval(l1[j], at[i].d) - at[i].p);
    }
    vector<pair<int64_t, int64_t > > l2 = cdq(m, r);
    vector<pair<int64_t, int64_t > > l3;
    int a = 0, b = 0;
    while (a < (int)l1.size() && b < (int)l2.size()) {
        if (l1[a] < l2[b]) add(l3, l1[a++]);
        else add(l3, l2[b++]);
    }
    while (a < (int)l1.size()) add(l3, l1[a++]);
    while (b < (int)l2.size()) add(l3, l2[b++]);
    vector<pair<int64_t, int64_t> > ().swap(l1);
    vector<pair<int64_t, int64_t> > ().swap(l2);
    return l3;
}
void init() {
    cin >> n >> c >> d; at.resize(n + 2);
    at[0] = {0, 0, c, 0};
    for (int i = 1 ; i <= n ; ++i) {
        cin >> at[i].d >> at[i].p >> at[i].r >> at[i].g;
    }
    at[n + 1] = {d + 1, 0, 0, 0};
    sort(at.begin(), at.end(), [&](auto a, auto b) { return a.d < b.d; });
}
void solve() {
    fill(dp, dp + n + 2, -LLONG_MAX);
    dp[0] = 0;
    cdq(0, n + 2);
    cout << dp[n + 1] << '\n';
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}