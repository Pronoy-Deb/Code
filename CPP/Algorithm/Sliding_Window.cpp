// Complexity: O(n)

long long ar[N], n, k, mx_sum = 0;
long long sum() {
    long long winsum = mx_sum;
    for (int i = k; i < n; ++i) {
        winsum += ar[i] - ar[i - k];
        mx_sum = max(mx_sum, winsum);
    }
    return mx_sum;
}

// Operation:
    cin >> n >> k;
    for (i = 0; i < n; ++i) { cin >> ar[i]; mx_sum += ar[i]; }
    cout << sum();
