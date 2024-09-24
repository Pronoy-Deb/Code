// Complexity: O(l)  // l = Length of the string
// Built-in: stoi(s) or, stol(s) or, stoll(s) or, atoi(s.c_str())  // not always error free

long long num(auto &s) {
    long long n = 0;
    for (auto &e : s) {
        n *= 10; n += (e - 48);
    }
    return n;
}