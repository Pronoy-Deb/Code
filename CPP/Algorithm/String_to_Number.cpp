// Complexity: O(l)  // l = Length of the string
// Built-in: stoi(s) or, stol(s) or, stoll(s) or, atoi(s.c_str())  // not always error free

int64_t num(auto &s) {
    int64_t n = 0;
    for (auto &e : s) {
        n *= 10; n += (e - 48);
    }
    return n;
}