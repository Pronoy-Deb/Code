// Complexity: O(log(n))

long double rt(auto n) {
    long double l = 1, h = n;
    while (h - l > 1e-6) {
        long double mid = (l + h) / 2;
        if (mid * mid < n) l = mid;
        else h = mid;
    }
    return l;
}