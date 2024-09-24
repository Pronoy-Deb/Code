// Complexity: O(n)
// Application: Used to determine the maximum xor subarray using trie.
// const long long N = 6e6 + 5;  // n * 30

long long trie[N][2], c = 0;
void insert(auto x) {
    long long nd = 0;
    for (int i = 30; i >= 0; --i) {
        long long y = x >> i & 1;
        if (!trie[nd][y]) trie[nd][y] = ++c;
        nd = trie[nd][y];
    }
}
long long search(auto x) {
    long long ans = 0, nd = 0;
    for (int i = 30; i >= 0; --i) {
        long long y = x >> i & 1;
        if (trie[nd][y ^ 1]) {
            nd = trie[nd][y ^ 1]; ans += (1 << i);
        }
        else nd = trie[nd][y];
    }
    return ans;
}

// Operation:
    cin >> n;
    long long xr = 0, mx = 0; insert(xr);
    for (i = 0; i < n; ++i) {
        long long x; cin >> x; xr ^= x; insert(xr);
        mx = max(search(xr), mx);
    }
    cout << mx << '\n';
    for (i = 0; i <= n; ++i) trie[i][0] = trie[i][1] = 0;