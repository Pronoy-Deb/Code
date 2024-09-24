// Complexity: O(d)  // d = Number of digits in the number
// Built-in: to_string(n);

auto str(auto n) {
    if (!n) return "0"; string s;
    while (n) {
        s += ((n % 10) + 48); n /= 10;
    }
    reverse(s.begin(), s.end()); return s;
}