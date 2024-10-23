// Complexity: O(n*log(n))
https://cses.fi/problemset/task/1629

pair<long long, long long> ar[N];
bool cmp(const pair<long long, long long> &a, const pair<long long, long long> &b) {
    return a.second < b.second;
}
int as() {
    sort(ar, ar + N, cmp);
    int ans = 0, cur = 0;
    for (int i = 0; i < n; ++i) {
        if (ar[i].first  >= cur) {
            cur = ar[i].second; ++ans;
        }
    }
    return ans;
}

// Operation:
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> ar[i].first >> ar[i].second;
    }
    cout << as();
