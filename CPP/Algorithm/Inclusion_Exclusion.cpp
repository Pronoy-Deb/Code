// Complexity: O(n)
https://cses.fi/problemset/task/2185

    cin >> n >> k;
    long long ar[k]; for (i = 0; i < k; ++i) { cin >> ar[i]; }
    for (i = 1; i < (1 << k); ++i) {
        a = n;
        for (j = 0; j < k; ++j) {
            if (i >> j & 1) a /= ar[j];
        }
        if (__builtin_popcount(i) & 1) c += a;
        else c -= a;
    }
    cout << c;
