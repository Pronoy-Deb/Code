// Complexity: O()

void in(auto &n) {
    bool neg = false; register int64_t c; n = 0; c = getchar();
    if (c=='-') { neg = true; c = getchar(); }
    for (; (c > 47 && c < 58); c = getchar()) n = n * 10 + c - 48;
    if (neg) n *= -1;
}

// Operation:
    int64_t n; in(n);