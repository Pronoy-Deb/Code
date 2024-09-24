// Complexity: O(n^2)
// Substring:

auto sstr(auto &s) {
    long long n = s.size(), k = 0;
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
    long long n = v.size(), k = 0;
    vector<vector<long long>> sub((n * (n + 1)) >> 1);
    for (int i = 0; i < n; ++i) {
        vector<long long> tmp;
        for (int j = i; j < n; ++j) {
            tmp.emplace_back(v[j]); sub[k++] = tmp;
        }
    }
    return sub;
}