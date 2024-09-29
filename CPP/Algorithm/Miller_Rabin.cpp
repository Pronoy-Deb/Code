#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 9;


int primes[N], spf[N];
void pre() {
    for (int i = 2, c = 0; i < N; ++i) {
        if (!spf[i]) primes[c++] = spf[i] = i;
        for (int j = 0, k; (k = i * primes[j]) < N; ++j) {
            spf[k] = primes[j];
            if (spf[i] == spf[k]) break;
        }
    }
}

long long modmul(long long x, long long y, long long m) {
    long long res = __int128(x) * y % m; return res;
    // long long res = x * y - (long long)((long double)x * y / m + 0.5) * m;
    // return res < 0 ? res + m : res;
}
long long bex(long long x, long long n, long long m) {
    long long res = 1 % m;
    while (n) {
        if (n & 1) res = modmul(res, x, m);
        x = modmul(x, x, m); n >>= 1;
    }
    return res;
}
bool pri(long long n) {
    if (n <= 2 || (n & 1 ^ 1)) return (n == 2);
    if (n < N) return spf[n] == n;
    long long s = 0, r = n - 1;
    while (~r & 1) { r >>= 1; ++s; }
    for (int i = 0; primes[i] < n && primes[i] < 32; ++i) {
        long long c = bex(primes[i], r, n);
        for (int j = 0; j < s; ++j) {
            long long d = modmul(c, c, n);
            if (d == 1 && c != 1 && c != (n - 1)) return false;
            c = d;
        }
        if (c != 1) return false;
    }
    return true;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // Milong longerRabin::pre();
    pre();
    int t;
    cin >> t;
    while (t--)
    {
        long long n;
        cin >> n;
        if (pri(n))
        {
            cout << "Yes\n";
        }
        else
        {
            cout << "No\n";
        }
    }
    return 0;
}
// https://judge.yosupo.jp/problem/primality_test