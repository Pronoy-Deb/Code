// Input is a Binary String:
// Complexity: O(n)

long long bin(auto &s) {
    long long n = 0;
    for (auto &c : s) {
        n <<= 1; n |= (c - '0');
    }
    return n;
}

// Input is a Decimal Number:
// Complexity: O(log n)

long long bin(auto n) {
    long long b = 0;
    while (n) {
        b <<= 1; b |= (n & 1); n >>= 1;
    }
    return b;
}

// Built-in Method: Complexity: O(1)
    string s = "1011";
    long long n = stoi(s, 0, 2);
    cout << n; // 11

// OR,
    long long a = 0b1011;
    cout << a; // 11