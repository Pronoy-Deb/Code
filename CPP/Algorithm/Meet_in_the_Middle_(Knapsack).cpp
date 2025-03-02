// Complexity: O(2^(n/2) * log(2^(n/2)))
// const int64_t N = 40 + 5;

int64_t aa[N];
auto ssum(auto s, auto e) {
    int64_t n = (1ll << (e - s)); vector<int64_t> res(n);
    for (int i = 0; i < n; ++i) {
        int64_t sum = 0, hi = __builtin_popcount(i);
        for (j = 0; hi && j < e - s; ++j) {
            if (i & (1ll << j)) { sum += aa[j + s]; --hi; }
        }
        res[i] = sum;
    }
    return res;
}

// Operation:
    int64_t sum; cin >> n >> sum;
    for (i = 0; i < n; ++i) { cin >> aa[i]; }
    auto h1 = ssum(0, n >> 1), h2 = ssum(n >> 1, n);
    sort(begin(h2), end(h2));
    int64_t c = 0, sz = h1.size();
    for (i = 0; i < sz; ++i) {
        if (sum >= h1[i])
            c += upper_bound(begin(h2), end(h2), sum - h1[i]) - lower_bound(begin(h2), end(h2), sum - h1[i]);
    }
    cout << c;

// Problems:
// https://cses.fi/problemset/task/1628/
// https://atcoder.jp/contests/abc184/tasks/abc184_f