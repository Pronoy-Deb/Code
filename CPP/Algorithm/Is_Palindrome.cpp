// Complexity: O(|s|)
// General Approach:

bool pal(auto &s) {
    for (int i = 0, j = s.size() - 1; i < j; ++i, --j) {
        if (s[i] != s[j]) return false;
    }
    return true;
}

// Hashing Approach:

bool pal(auto &s, int base = 29) {
    long long sz = s.size(), tmp = s[0] - 96, temp = s[sz - 1] - 96;
    for (int i = 1; i < sz; ++i) tmp = ((tmp * base) + (s[i] - 96)) % M;
    for (int i = sz - 2; i >= 0; --i) temp = ((temp * base) + (s[i] - 96)) % M;
    return (tmp == temp);
}