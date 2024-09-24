// Complexity: O(n^2)
// Iterative approach:

void bsrt(auto &v, auto n) {
    for (int i = 0; i < n - 1; ++i) {
        bool ck = true;
        for (int j = 0; j < n - i - 1; ++j) {
            if (v[j] > v[j+1]) {
                swap(v[j], v[j+1]); ck = false;
            }
        }
        if(ck) break;
    }
}

// Recursive approach:

void bsrt(auto &v, auto n) {
    if (n < 2) return;
    for (int i = 0; i < n - 1; ++i) {
        if (v[i] > v[i + 1]) swap(v[i], v[i + 1]);
    }
    bsrt(v, n - 1);
}