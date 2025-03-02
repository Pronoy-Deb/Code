// Complexity: O(1)

auto ed(int64_t x1, int64_t y1, int64_t x2, int64_t y2) {
    long double a = (x2 - x1) * (x2 - x1);
    long double b = (y2 - y1) * (y2 - y1);
    return (long double)sqrtl(a + b);
}