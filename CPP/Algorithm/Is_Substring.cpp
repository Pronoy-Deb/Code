// Complexity: O(|main| * |sub|)
// STL Approach:

bool sstr(auto &main, auto &sub) {
    return (main.find(sub) != -1);
}

// Iterative Approach:

bool sstr(auto &main, auto &sub) {
    int m = main.size(), n = sub.size();
    for (int i = 0, j; i <= m - n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (main[i + j] != sub[j]) break;
		}
        if (j == n) return true;
    }
    return false;
}