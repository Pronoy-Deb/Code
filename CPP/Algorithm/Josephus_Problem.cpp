// n = total person
// will kill every kth person, if k = 2, 2,4,6,...
// returns the mth killed person
// O(k log n)

int64_t josephus(int64_t n, int64_t k, int64_t m) {
    m = n - m;
    if (k <= 1) return n - m;
    int64_t i = m;
    while (i < n) {
        int64_t r = (i - m + k - 2) / (k - 1);
        if ((i + r) > n) r = n - i;
        else if (!r) r = 1;
        i += r; m = (m + (r * k)) % i;
    }
    return m + 1;
}