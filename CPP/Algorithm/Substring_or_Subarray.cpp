// Complexity: O(n^2)
// Substring:

auto sstr(auto &s) {
    int64_t n = s.size(), k = 0;
    vector<string> sub((n * (n + 1)) >> 1);
    for (int i = 0; i < n; ++i) {
        string tmp;
        for (int j = i; j < n; ++j) {
            tmp += s[j]; sub[k++] = tmp;
        }
    }
    return sub;
}

// Subarray:

auto sar(auto &v) {
    int64_t n = v.size(), k = 0;
    vector<vector<int64_t>> sub((n * (n + 1)) >> 1);
    for (int i = 0; i < n; ++i) {
        vector<int64_t> tmp;
        for (int j = i; j < n; ++j) {
            tmp.emplace_back(v[j]); sub[k++] = tmp;
        }
    }
    return sub;
}