// Complexity: O(n)
// Alternate: cout << oct << n;

auto oct(auto n) {
    string s;
    while (n) {
        s += (n % 8 + 48); n >>= 3;
    }
    reverse(s.begin(), s.end()); return s;
}