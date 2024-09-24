// Complexity: O(1)

auto ed(long long x1, long long y1, long long x2, long long y2) {
    long double a = (x2 - x1) * (x2 - x1);
    long double b = (y2 - y1) * (y2 - y1);
    return (long double)sqrtl(a + b);
}