// Complexity: O(n)
// ASCII: 48 = '0', 55 = 'A', 97 = 'a'
// Built-in: cout << hex << n;  // In Lowercase

auto hex(auto n) {
    string s;
    while(n) {
        int tmp = n % 16;
        s += (tmp + (tmp < 10 ? 48 : 55));
        n >>= 4;
    }
    reverse(s.begin(), s.end()); return s;
}