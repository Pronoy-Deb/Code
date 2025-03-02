// Complexity: O(n*log(n))
https://cses.fi/problemset/task/1629

pair<int64_t, int64_t> aa[N];
bool cmp(const pair<int64_t, int64_t> &a, const pair<int64_t, int64_t> &b) {
    return a.second < b.second;
}
int as() {
    sort(ar, ar + N, cmp);
    int ans = 0, cur = 0;
    for (int i = 0; i < n; ++i) {
        if (aa[i].first  >= cur) {
            cur = aa[i].second; ++ans;
        }
    }
    return ans;
}

// Operation:
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> aa[i].first >> aa[i].second;
    }
    cout << as();
