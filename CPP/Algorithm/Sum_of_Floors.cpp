// Complexity: O(sqrt(n))

long long floor_sum(ll n) {
    long long sum = 0;
    for (long long i = 1, lst; i <= n; i = lst + 1) {
        lst = n / (n / i); sum += (n / i) * (lst - i + 1);
    }
    return sum;
}