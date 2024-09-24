// Complexity: O(n*log(num*(10^d))); for n-th root of number num with d decimal accuracy
// Returns: n-th root of a number with 5 decimal accuracy
// Built-in: pow(num, 1.0/n)

auto mul(auto mid, auto n) {
    long double ans = 1;
    for (int i = 0; i < n; ++i) ans *= mid;
    return ans;
}
auto rt(auto n, auto num) {
    long double l = 1, h = num;
    while (h - l > 1e-6) {  // 1e-6 means accuracy till 5 decimal places
        long double mid = (h + l) / 2;
        if (mul(mid, n) < num) l = mid;
        else h = mid;
    }
    return l;
}