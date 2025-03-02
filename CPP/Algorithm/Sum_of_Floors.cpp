// Complexity: O(sqrt(n))

int64_t floor_sum(ll n) {
    int64_t sum = 0;
    for (int64_t i = 1, lst; i <= n; i = lst + 1) {
        lst = n / (n / i); sum += (n / i) * (lst - i + 1);
    }
    return sum;
}