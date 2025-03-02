// Complexity: O(n)
https://codeforces.com/contest/816/problem/B

    cin >> n >> k >> q;
    vector<int64_t> ar(N);
    for (i = 0; i < n; ++i) {
        cin >> a >> b; ar[a]++; ar[++b]--;
    }
    int64_t cnt[N]{};
    for (i = 1; i < N; ++i) {
        ar[i] += ar[i - 1];
        cnt[i] += cnt[i - 1] + (ar[i] >= k);
    }
    while (q--) {
        cin >> a >> b;
        cout << cnt[b] - cnt[--a] << '\n';
    }

// OR, https://codeforces.com/contest/295/problem/A

    cin >> n >> m >> k;
    vector<int64_t> ar(n + 2), val(m + 2); vector<pair<int64_t, int64_t>> rng(m + 2);
    for (i = 1; i <= n; ++i) cin >> ar[i];
    for (i = 1; i <= m; ++i) cin >> rng[i].first >> rng[i].second >> val[i];
    vector<int64_t> cnt(m + 2), dif(n + 2);
    while (k--) {
        cin >> a >> b; cnt[a]++; cnt[++b]--;
    }
    for (i = 1; i <= m; ++i) {
        cnt[i] += cnt[i - 1];
        if (cnt[i]) {
            dif[rng[i].first] += cnt[i] * val[i];
            dif[rng[i].second + 1] -= cnt[i] * val[i];
        }
    }
    for (i = 1; i <= n; ++i) {
        dif[i] += dif[i - 1]; cout << ar[i] + dif[i] << ' ';
    }
