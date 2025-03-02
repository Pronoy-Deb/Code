// Complexity: O(n)
// Built-in: string s = bitset<8>(n).to_string();

auto bin(int64_t n) {
    string s;
    while (n) {
        s += ((n & 1) + 48); n >>= 1;
    }
    reverse(s.begin(), s.end());
    if (s.empty()) s += '0';
    return s;
}

// To return the value as integer:

int64_t bin(int64_t n) {
    int64_t ans = 0;
    for (int i = 18; i >= 0; --i) ans = (ans * 10) + ((n >> i) & 1);
    return ans;
}

// OR,

int64_t bin(int64_t n) {
    string s;
    while (n) {
        s += ((n & 1) + 48); n >>= 1;
    }
    int64_t ans = 0;
    for (int i = s.size() - 1; i >= 0; --i) ans = ans * 10 + (s[i] == '1');
    return ans;
}