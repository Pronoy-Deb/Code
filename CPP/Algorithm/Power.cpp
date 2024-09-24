// Complexity: O(n^2)
// Built-in: (long long) pow(base, power);  // not always accurate
// For the values that can be stored in long long integer:
// Results till: 2^40, 3^39, 4^31, 5^32, 6^24, 7^24, 8^20, 9^19, 10^18, 11^21, 12^19, 13^22, 14^16, 15^18, 16^15, 17^15, 18^15, 19^14, 20^14, 21^14, 22^18, 23^13, 24^15, 25^17, 26^14, 27^13, 28^13, 29^12, 30^12, 31^15, 32^12, 33^12, 34^13, 35^16, 36^13, 37^13, 38^12, 39^11, 40^11
// const long long N = 40 + 5;

long long pw[N][N];
void pre() {
    for (int i = 1; i < N; ++i) {
        pw[i][0] = 1;
        for (int j = 1; j < N; ++j) {
            pw[i][j] = pw[i][j - 1] * i;
            if (pw[i][j] <= 0) break;
        }
    }
}

// For the values that can be stored in integer :
// Results till: 2^20, 3^19, 4^15, 5^15, 6^11, 7^12, 8^10, 9^9, 10^11, 11^8, 12^10, 13^11, 14^8, 15^7, 16^7, 17^7, 18^7, 19^7, 20^7
// const long long N = 20 + 5;

long long pw[N][N];
void pre() {
    for (int i = 1; i < N; ++i) {
        pw[i][0] = 1;
        for (int j = 1; j < N; ++j) pw[i][j] = (pw[i][j - 1] * i) % M;
    }
}