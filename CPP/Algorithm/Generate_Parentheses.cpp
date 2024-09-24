// Complexity: O(2^n)

void gen(auto &s, auto open, auto close, auto &v) {
    if (!open and !close) {
        v.emplace_back(s); return;
    }
    if (open) {
        s += '('; gen(s, open - 1, close, v);
        s.pop_back();  // Back_tracking
    }
    if (close) {
        if (open < close) {
            s += ')'; gen(s, open, close - 1, v);
            s.pop_back();  // Back_tracking
        }
    }
}

// Calling: gen(empty_str, n, n, empty_vec)