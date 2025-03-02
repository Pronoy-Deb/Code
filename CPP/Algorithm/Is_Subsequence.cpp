// Complexity: O(main.size())
// For String:
// Iterative Approach:

bool sseq(auto &main, auto &sub) {
    int m = main.size(), n = sub.size(), i = 0, j = 0;
    while (i < m && j < n) {
        if (main[i] == sub[j]) ++j;
        ++i;
    }
    return (j == n);
}

// Recursive Approach:

bool sseq(auto &main, auto &sub, int64_t m_sz, int64_t s_sz) {
    if (!s_sz) return true;
    if (!m_sz) return false;
    if (main[m_sz - 1] == sub[s_sz - 1]) return sseq(main, sub, m_sz - 1, s_sz - 1);
    return sseq(main, sub, m_sz - 1, s_sz);
}

// For Vector:
// Iterative Approach:

bool sseq(auto &main, auto &sub) {
    int m = main.size(), n = sub.size(), i = 0, j = 0;
    while (i < m && j < n) {
        if (main[i] == sub[j]) ++j;
        ++i;
    }
    return (j == n);
}

// Recursive Approach:

auto sseq(auto &main, auto &sub, int64_t m_sz, int64_t s_sz) {
    if (!s_sz) return true;
    if (!m_sz) return false;
    if (main[m_sz - 1] == sub[s_sz - 1]) return sseq(main, sub, m_sz - 1, s_sz - 1);
    return sseq(main, sub, m_sz - 1, s_sz);
}