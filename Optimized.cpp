#include<bits/stdc++.h>
// Function to check if a number is prime
bool isPrime(long long n) {
    if (n < 2) return false;
    if (n % 2 == 0 && n != 2) return false;
    for (long long i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    long long limit = LLONG_MAX; // 2^32
    long long largestPrime = 0;

    for (long long n = limit; n >= 2; --n) {
        if (isPrime(n)) {
            largestPrime = n;
            break;
        }
    }

    std::cout << "Largest prime whose square is less than 2^64: " << largestPrime << std::endl;
    return 0;
}
