// Complexity: O(n)

int64_t aa[N], n, k, mx_sum = 0;
int64_t sum() {
    int64_t winsum = mx_sum;
    for (int i = k; i < n; ++i) {
        winsum += aa[i] - aa[i - k];
        mx_sum = max(mx_sum, winsum);
    }
    return mx_sum;
}

// Operation:
cin >> n >> k;
for (int i = 0; i < n; ++i) {
    cin >> aa[i];
    mx_sum += aa[i];
}
cout << sum();

// Sliding Minimum or Maximum :

void sli(auto &v) {
    cin >> n >> k;
    for (int i = 0; i < k; ++i) {
        int val = v[i];
        while (!q.empty() && q.front().first <= val) q.pop_front();
        while (!q.empty() && q.back().first <= val) q.pop_back();
        q.push_back({val, i});
    }
    cout << q.front().first << " ";
    for (int i = k; i < n; i++) {
        val = v[i];
        if (q.front().second == (i - k))
            q.pop_front();
        while (!q.empty() && q.front().first <= val)
            q.pop_front();
        while (!q.empty() && q.back().first <= val)
            q.pop_back();
        q.push_back({val, i});
        cout << q.front().first << " ";
    }
    cout << endl;
}
