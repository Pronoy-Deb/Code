// Complexity: O(n)
https://cses.fi/problemset/task/2185

    cin >> n >> k;
    int64_t aa[k]; for (int i = 0; i < k; ++i) { cin >> aa[i]; }
    for (int i = 1; i < (1 << k); ++i) {
        a = n;
        for (j = 0; j < k; ++j) {
            if (i >> j & 1) a /= aa[j];
        }
        if (__builtin_popcount(i) & 1) c += a;
        else c -= a;
    }
    cout << c;
