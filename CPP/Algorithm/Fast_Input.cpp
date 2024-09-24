// Complexity: O()

void in(auto &n) {
    bool neg = false; register long long c; n = 0; c = getchar();
    if (c=='-') { neg = true; c = getchar(); }
    for (; (c > 47 && c < 58); c = getchar()) n = n * 10 + c - 48;
    if (neg) n *= -1;
}

// Operation:
    long long n; in(n);