// Summaiton of Digits:
// Complexity: O(log(n))

int dsum(long long n) {
    int sum = 0;
    while (n) {
        sum += (n % 10); n /= 10;
    }
    return sum;
}

// Recursive Approach:

int dsum(long long n) {
    if(n < 10) return n;
    return dsum(n / 10) + (n % 10);
}

// Count of Digits:

int dc(long long n) {
    int c = 0;
    while (n) {
        n /= 10; ++c;
    }
    return c;
}

OR, (int)log10(n) + 1;

// Recursive Approach:

int dc(long long n) {
    if (!n) return 0;
    return 1 + dc(n / 10);
}