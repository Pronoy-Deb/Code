// Complexity: O(n * log(n))
// Application: Used to determine the Number of Divisors and Sum of Divisors from number 1 to n.

long long nd[N];
void pre() {
    for (int i = 1; i < N; ++i)
        for (int j = i; j < N; j += i) ++nd[j];
}

long long sd[N];
void pre() {
    for (int i = 1; i < N; ++i)
        for (int j = i; j < N; j += i) sd[j] += i;
}