// Input is a Binary String: O(n)

int64_t bin(auto &s) {
    int64_t n = 0;
    for (auto &c : s) {
        n <<= 1; n |= (c - '0');
    }
    return n;
}

// Input is a Decimal Number: O(log n)

int64_t bin(auto n) {
    int64_t b = 0;
    while (n) {
        b <<= 1; b |= (n & 1); n >>= 1;
    }
    return b;
}

// Built-in Method: Complexity: O(1)
    string s = "1011";
    int64_t n = stoi(s, 0, 2);
    cout << n; // 11

// OR,
    int64_t a = 0b1011;
    cout << a; // 11